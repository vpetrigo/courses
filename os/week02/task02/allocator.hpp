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
    Allocator() noexcept : head_{nullptr}, end_{nullptr}
    {
    }

    Allocator(void *buf, std::size_t size) noexcept
        : head_{buf}, end_{to_char(head_) + size}
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
                get_bm_by_ptr_with_offset(alloc_place.first, size);

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
                get_bm_by_ptr_with_offset(alloc_place.first, size);
            BorderMarker *new_head_free = new_end + 1;
            BorderMarker *new_end_free = get_bm_by_ptr_with_offset(
                alloc_place.first, alloc_place.first->size_);

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

    BorderMarker *get_bm_by_ptr_with_offset(void *ptr, std::size_t offset) const
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

        if (bm->prev_)
        {
            bm->prev_->next_ = bm->next_;
        }

        if (bm->next_)
        {
            bm->next_->prev_ = bm->prev_;
        }
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

  private:
    void *head_;
    void *end_;
};
