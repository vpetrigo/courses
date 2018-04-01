#include <cassert>
#include <cstddef>
#include <memory>
#include <utility>

char *to_char(void *ptr)
{
    return static_cast<char *>(ptr);
}

class Allocator
{
  public:
    Allocator() : head_(NULL), start_(NULL), end_(NULL)
    {
    }

    Allocator(void *buf, std::size_t size)
        : head_(buf), start_(head_), end_(to_char(head_) + size)
    {
        new (head_) BorderMarker(NULL, NULL, size - 2 * sizeof(BorderMarker));
        new (get_offset_to_bm(end_)) BorderMarker(*get_bm_by_ptr(head_));
        assert(get_bm_by_ptr(head_)->size_ == size - 2 * sizeof(BorderMarker));
        assert(get_bm_by_user_ptr(end_)->size_ ==
               size - 2 * sizeof(BorderMarker));
    }

    void set_buf(void *buf, std::size_t size)
    {
        head_ = buf;
        end_ = to_char(head_) + size;
        new (head_) BorderMarker(NULL, NULL, size - 2 * sizeof(BorderMarker));
        new (get_offset_to_bm(end_)) BorderMarker(*get_bm_by_ptr(head_));
        assert(get_bm_by_ptr(head_)->size_ == size - 2 * sizeof(BorderMarker));
        assert(get_bm_by_user_ptr(end_)->size_ ==
               size - 2 * sizeof(BorderMarker));
    }

    void *alloc(std::size_t size)
    {
        std::pair<BorderMarker *, bool> alloc_place = check_free_mem(size);

        if (!alloc_place.second)
        {
            return NULL;
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
                BorderMarker(alloc_place.first->prev_, alloc_place.first->next_,
                             get_new_size(alloc_place.first->size_, size));
            new (new_end_free) BorderMarker(*new_head_free);
            alloc_place.first->size_ = size;
            *new_end = *alloc_place.first;
        }

        return alloc_place.first + 1;
    }

    void free(void *ptr)
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

        user_block_start->is_free_ = BLOCK_FREE;
        user_block_end->is_free_ = BLOCK_FREE;

        if (!user_block_start->next_ && !user_block_start->prev_ &&
            user_block_start != head_)
        {
            add_mem_block_to_list(user_block_start);
        }
    }

    static std::size_t get_allocation_overhead()
    {
        return 2 * sizeof(BorderMarker);
    }

  private:
    enum MemOccupation
    {
        BLOCK_FREE,
        BLOCK_OCCUPIED
    };

    struct BorderMarker
    {
        // BorderMarker() = default;

        BorderMarker(BorderMarker *prev, BorderMarker *next, std::size_t size,
                     enum MemOccupation is_free = BLOCK_FREE)
            : prev_(prev), next_(next), size_(size), is_free_(is_free)
        {
        }

        BorderMarker *prev_;
        BorderMarker *next_;
        std::size_t size_;
        enum MemOccupation is_free_;
    };

    BorderMarker *get_bm_by_ptr(void *ptr) const
    {
        return static_cast<BorderMarker *>(ptr);
    }

    BorderMarker *get_bm_by_user_ptr(void *ptr) const
    {
        return static_cast<BorderMarker *>(get_offset_to_bm(ptr));
    }

    BorderMarker *get_bm_by_ptr_with_offset(void *ptr,
                                            std::ptrdiff_t offset) const
    {
        return reinterpret_cast<BorderMarker *>(to_char(ptr) + offset);
    }

    void *get_offset_to_bm(void *ptr) const
    {
        return to_char(ptr) - sizeof(BorderMarker);
    }

    std::size_t get_new_size(std::size_t cur_size, std::size_t req_size) const
    {
        return cur_size - req_size - Allocator::get_allocation_overhead();
    }

    void occupy_block(BorderMarker *bm) const
    {
        bm->is_free_ = BLOCK_OCCUPIED;

        delete_from_list(bm);
        bm->prev_ = NULL;
        bm->next_ = NULL;
    }

    std::pair<BorderMarker *, bool> check_free_mem(std::size_t size) const
    {
        if (size == 0 || head_ == end_)
        {
            return std::make_pair(static_cast<BorderMarker *>(NULL), false);
        }

        BorderMarker *it = get_bm_by_ptr(head_);

        while (it)
        {
            if (it->size_ >= size)
            {
                return std::make_pair(it, true);
            }

            it = it->next_;
        }

        return std::make_pair(static_cast<BorderMarker *>(NULL), false);
    }

    bool check_is_splittable(const BorderMarker *bm, std::size_t to_alloc) const
    {
        return bm->size_ - to_alloc > Allocator::get_allocation_overhead();
    }

    bool is_left_block_exists(void *ptr) const
    {
        return ptr != start_;
    }

    bool is_right_block_exists(void *ptr) const
    {
        return ptr != end_;
    }

    bool is_left_block_free(const BorderMarker *bm) const
    {
        return (bm - 1)->is_free_ == BLOCK_FREE;
    }

    bool is_right_block_free(const BorderMarker *bm) const
    {
        return (bm + 1)->is_free_ == BLOCK_FREE;
    }

    BorderMarker *defrag_left(BorderMarker *start_bm,
                              BorderMarker *end_bm) const
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
                               BorderMarker *end_bm) const
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

    void add_mem_block_to_list(BorderMarker *bm)
    {
        BorderMarker *it = get_bm_by_ptr(head_);

        while (it->next_)
        {
            it = it->next_;
        }

        it->next_ = bm;
        bm->next_ = NULL;
        bm->prev_ = it;
    }

    void delete_from_list(BorderMarker *bm) const
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

static Allocator allocator;
// Эта функция будет вызвана перед тем как вызывать myalloc и myfree
// используйте ее чтобы инициализировать ваш аллокатор перед началом
// работы.
//
// buf - указатель на участок логической памяти, который ваш аллокатор
//       должен распределять, все возвращаемые указатели должны быть
//       либо равны NULL, либо быть из этого участка памяти
// size - размер участка памяти, на который указывает buf
void mysetup(void *buf, std::size_t size)
{
    allocator.set_buf(buf, size);
}

// Функция аллокации
void *myalloc(std::size_t size)
{
    return allocator.alloc(size);
}

// Функция освобождения
void myfree(void *p)
{
    allocator.free(p);
}

int main()
{
    return 0;
}