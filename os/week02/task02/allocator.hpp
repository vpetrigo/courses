#pragma once

#include <cassert>
#include <cstddef>
#include <iostream>
#include <memory>
#include <utility>
#include <vector>

constexpr char *to_char(void *ptr)
{
    return static_cast<char *>(ptr);
}

class Allocator
{
  public:
    Allocator() noexcept : head_{nullptr}, start_{nullptr}, end_{nullptr}
    {
    }

    Allocator(void *buf, std::size_t size) noexcept
        : head_{buf}, start_{head_}, end_{to_char(head_) + size}
    {
        new (head_)
            BorderMarker{nullptr, nullptr, size - 2 * sizeof(BorderMarker)};
        new (get_offset_to_bm(end_)) BorderMarker{*get_bm_by_ptr(head_)};
        assert(get_bm_by_ptr(head_)->size_ == size - 2 * sizeof(BorderMarker));
        assert(get_bm_by_user_ptr(end_)->size_ ==
               size - 2 * sizeof(BorderMarker));
    }

    void set_buf(void *buf, std::size_t size) noexcept
    {
        head_ = buf;
        end_ = to_char(head_) + size;
        new (head_)
            BorderMarker{nullptr, nullptr, size - 2 * sizeof(BorderMarker)};
        new (get_offset_to_bm(end_)) BorderMarker{*get_bm_by_ptr(head_)};
        assert(get_bm_by_ptr(head_)->size_ == size - 2 * sizeof(BorderMarker));
        assert(get_bm_by_user_ptr(end_)->size_ ==
               size - 2 * sizeof(BorderMarker));
    }

    void *alloc(std::size_t size) noexcept
    {
        auto alloc_place = check_free_mem(size);

        if (!alloc_place.second)
        {
            return nullptr;
        }

        if (!check_is_splittable(alloc_place.first, size))
        {
            BorderMarker *new_end =
                get_bm_by_ptr_with_offset(alloc_place.first + 1, size);

            if (head_ == alloc_place.first)
            {
                head_ = (alloc_place.first->next_) ? alloc_place.first->next_
                                                   : end_;
            }

            occupy_block(alloc_place.first);
            *new_end = *alloc_place.first;
        }
        else
        {
            BorderMarker *new_end =
                get_bm_by_ptr_with_offset(alloc_place.first + 1, size);
            BorderMarker *new_head_free = new_end + 1;
            BorderMarker *new_end_free = get_bm_by_ptr_with_offset(
                alloc_place.first + 1, alloc_place.first->size_);

            if (head_ == alloc_place.first)
            {
                head_ = new_head_free;
            }

            occupy_block(alloc_place.first);
            new (new_head_free)
                BorderMarker{alloc_place.first->prev_, alloc_place.first->next_,
                             get_new_size(alloc_place.first->size_, size)};
            new (new_end_free) BorderMarker{*new_head_free};
            alloc_place.first->size_ = size;
            *new_end = *alloc_place.first;
        }

        return alloc_place.first + 1;
    }

    void free(void *ptr) noexcept
    {
        if (!ptr)
        {
            return;
        }

        BorderMarker *user_block_start = get_bm_by_user_ptr(ptr);
        BorderMarker *user_block_end = get_bm_by_ptr_with_offset(
            user_block_start + 1, user_block_start->size_);

        if (is_left_block_exists(user_block_start) &&
            is_left_block_free(user_block_start))
        {
            // defrag left
            user_block_start = defrag_left(user_block_start, user_block_end);
        }

        if (is_right_block_exists(user_block_end + 1) &&
            is_right_block_free(user_block_end))
        {
            // defrag right
            if (user_block_end + 1 == head_)
            {
                head_ = user_block_start;
            }

            user_block_end = defrag_right(user_block_start, user_block_end);
        }

        if (head_ == end_)
        {
            head_ = user_block_start;
        }

        user_block_start->is_free_ = MemOccupation::BLOCK_FREE;
        user_block_end->is_free_ = MemOccupation::BLOCK_FREE;

        if (user_block_start->prev_ == nullptr &&
            user_block_start->next_ == nullptr && user_block_start != head_)
        {
            add_mem_block_to_list(user_block_start);
        }
    }

    static constexpr std::size_t get_allocation_overhead() noexcept
    {
        return 2 * sizeof(BorderMarker);
    }

    std::vector<std::size_t> get_free_places() const noexcept
    {
        if (head_ == end_)
        {
            return {0};
        }

        std::vector<std::size_t> free_places;
        const BorderMarker *it = get_bm_by_ptr(head_);

        while (it)
        {
            free_places.emplace_back(it->size_);
            it = it->next_;
        }

        return free_places;
    }

  private:
    enum class MemOccupation : char
    {
        BLOCK_FREE,
        BLOCK_OCCUPIED
    };

    struct BorderMarker
    {
        BorderMarker() = default;

        BorderMarker(BorderMarker *prev, BorderMarker *next, std::size_t size,
                     MemOccupation is_free = MemOccupation::BLOCK_FREE)
            : prev_{prev}, next_{next}, size_{size}, is_free_{is_free}
        {
        }

        BorderMarker *prev_;
        BorderMarker *next_;
        std::size_t size_;
        MemOccupation is_free_;
    };

    BorderMarker *get_bm_by_ptr(void *ptr) const noexcept
    {
        return static_cast<BorderMarker *>(ptr);
    }

    BorderMarker *get_bm_by_user_ptr(void *ptr) const noexcept
    {
        return static_cast<BorderMarker *>(get_offset_to_bm(ptr));
    }

    BorderMarker *get_bm_by_ptr_with_offset(void *ptr,
                                            std::ptrdiff_t offset) const
        noexcept
    {
        return reinterpret_cast<BorderMarker *>(to_char(ptr) + offset);
    }

    void *get_offset_to_bm(void *ptr) const noexcept
    {
        return to_char(ptr) - sizeof(BorderMarker);
    }

    std::size_t get_new_size(std::size_t cur_size, std::size_t req_size) const
        noexcept
    {
        return cur_size - req_size - Allocator::get_allocation_overhead();
    }

    void occupy_block(BorderMarker *bm) const noexcept
    {
        bm->is_free_ = MemOccupation::BLOCK_OCCUPIED;
        delete_from_list(bm);
        bm->prev_ = nullptr;
        bm->next_ = nullptr;
    }

    std::pair<BorderMarker *, bool> check_free_mem(std::size_t size) const
        noexcept
    {
        if (size == 0 || head_ == end_)
        {
            return {nullptr, false};
        }

        BorderMarker *it = get_bm_by_ptr(head_);

        while (it)
        {
            if (it->size_ >= size)
            {
                return {it, true};
            }

            it = it->next_;
        }

        return {nullptr, false};
    }

    bool check_is_splittable(const BorderMarker *bm, std::size_t to_alloc) const
        noexcept
    {
        return bm->size_ - to_alloc > Allocator::get_allocation_overhead();
    }

    bool is_left_block_exists(void *ptr) const noexcept
    {
        return ptr != start_;
    }

    bool is_right_block_exists(void *ptr) const noexcept
    {
        return ptr != end_;
    }

    bool is_left_block_free(const BorderMarker *bm) const noexcept
    {
        return (bm - 1)->is_free_ == MemOccupation::BLOCK_FREE;
    }

    bool is_right_block_free(const BorderMarker *bm) const noexcept
    {
        return (bm + 1)->is_free_ == MemOccupation::BLOCK_FREE;
    }

    BorderMarker *defrag_left(BorderMarker *start_bm,
                              BorderMarker *end_bm) const noexcept
    {
        BorderMarker *left_end_bm = start_bm - 1;
        BorderMarker *left_bm =
            get_bm_by_ptr_with_offset(left_end_bm - 1, -left_end_bm->size_);

        left_bm->size_ +=
            start_bm->size_ + Allocator::get_allocation_overhead();
        *end_bm = *left_bm;

        return left_bm;
    }

    BorderMarker *defrag_right(BorderMarker *start_bm,
                               BorderMarker *end_bm) const noexcept
    {
        BorderMarker *right_bm = end_bm + 1;
        BorderMarker *right_end_bm =
            get_bm_by_ptr_with_offset(right_bm + 1, right_bm->size_);

        start_bm->size_ +=
            right_bm->size_ + Allocator::get_allocation_overhead();
        // remove start_bm from the list
        delete_from_list(start_bm);

        if (right_bm->next_)
        {
            right_bm->next_->prev_ = start_bm;
        }

        if (right_bm->prev_)
        {
            right_bm->prev_->next_ = start_bm;
        }

        start_bm->next_ = right_bm->next_;
        start_bm->prev_ = right_bm->prev_;
        *right_end_bm = *start_bm;

        return right_end_bm;
    }

    void add_mem_block_to_list(BorderMarker *bm) noexcept
    {
        BorderMarker *it = get_bm_by_ptr(head_);

        while (it->next_)
        {
            it = it->next_;
        }

        it->next_ = bm;
        bm->next_ = nullptr;
        bm->prev_ = it;
    }

    void delete_from_list(BorderMarker *bm) const noexcept
    {
        if (bm->next_)
        {
            bm->next_->prev_ = bm->prev_;
        }

        if (bm->prev_)
        {
            bm->prev_->next_ = bm->next_;
        }
    }

  private:
    void *head_;
    void *start_;
    void *end_;
};
