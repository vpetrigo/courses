#include <cassert>
#include <iostream>
#include <stdexcept>

#ifdef DEBUG
#define log_debug(...) printf(__VA_ARGS__)
#else
#define log_debug(...)
#endif

class Allocator {
  public:
    struct BorderMarker {
        BorderMarker(BorderMarker *prev, BorderMarker *next, std::size_t size)
            : prev_{prev}, next_{next}, size_{size}, is_free_{BLOCK_FREE}
        {
        }

        BorderMarker *prev_;
        BorderMarker *next_;
        std::size_t size_;
        char is_free_;
    };

    Allocator() : head_{nullptr}, size_{0} {}
    Allocator(void *buf, std::size_t size)
        : head_{buf}, start_{head_}, size_{size}
    {
        size_ -= 2 * sizeof(BorderMarker);
        new (head_) BorderMarker{nullptr, nullptr, size_};
        new (get_ptr_to_end_bm(head_, size_))
            BorderMarker{nullptr, nullptr, size_};
    }

    ~Allocator() = default;

    Allocator(const Allocator &alloc) = delete;
    Allocator &operator=(const Allocator &alloc) = delete;

    void set_buffer(void *buf, std::size_t size) noexcept
    {
        head_ = start_ = buf;
        size_ = size - 2 * sizeof(BorderMarker);
        new (head_) BorderMarker{nullptr, nullptr, size_};
        new (get_ptr_to_end_bm(head_, size_))
            BorderMarker{nullptr, nullptr, size_};
    }

    void *alloc(std::size_t size) noexcept { return nullptr; }

    void free(void *ptr) noexcept
    {
        BorderMarker *bm = get_bm_by_ptr(ptr);
        BorderMarker *free_region = defrag(bm);

        log_debug("%s: free reg: %p, bm: %p\n", __func__, free_region, bm);
    }

    const BorderMarker &debug_get_borders(void *ptr) const
    {
        if (!ptr) {
            throw std::logic_error{""};
        }

        return *get_bm_by_ptr(ptr);
    }

  private:
    static constexpr char BLOCK_OCCUPIED = 0;
    static constexpr char BLOCK_FREE = 1;

    constexpr void *get_mem_end() const noexcept
    {
        return static_cast<void *>(static_cast<char *>(start_) + size_ -
                                   sizeof(BorderMarker));
    }

    BorderMarker *get_bm_by_ptr(void *ptr) const
    {
        return reinterpret_cast<BorderMarker *>(static_cast<char *>(ptr) -
                                                sizeof(BorderMarker));
    }

    char *get_ptr_to_end_bm(void *ptr, std::size_t size)
    {
        return static_cast<char *>(ptr) + sizeof(BorderMarker) + size;
    }

    char *get_ptr_to_start_bm(void *ptr, std::size_t size)
    {
        return static_cast<char *>(ptr) - sizeof(BorderMarker) - size;
    }

    BorderMarker *defrag(BorderMarker *bm) noexcept
    {
        BorderMarker *start1 = defrag_prev(bm);
        BorderMarker *start2 = defrag_next(bm);
        assert(start1 == start2);

        return start1;
    }

    BorderMarker *defrag_prev(BorderMarker *bm) noexcept
    {
        BorderMarker *prev = bm - 1;

        if (bm != start_ && prev->is_free_ == BLOCK_FREE) {
            log_debug("%s: Defragment previous\n", __func__);
            prev = reinterpret_cast<BorderMarker *>(
                get_ptr_to_start_bm(prev, prev->size_));
            prev->size_ += bm->size_ + 2 * sizeof(BorderMarker);

            BorderMarker *end_bm = reinterpret_cast<BorderMarker *>(
                get_ptr_to_end_bm(bm, bm->size_));

            *end_bm = *prev;
            bm = prev;
        }

        return bm;
    }

    BorderMarker *defrag_next(BorderMarker *bm) noexcept
    {
        BorderMarker *end_bm =
            reinterpret_cast<BorderMarker *>(get_ptr_to_end_bm(bm, bm->size_));
        BorderMarker *next = end_bm + 1;

        if (end_bm != get_mem_end() && next->is_free_ == BLOCK_FREE) {
            log_debug("%s: Defragment next\n", __func__);

            BorderMarker *next_end = reinterpret_cast<BorderMarker *>(
                get_ptr_to_end_bm(next, next->size_));

            next_end->size_ += end_bm->size_ + 2 * sizeof(BorderMarker);
            next_end->prev_ = next->prev_;
            next_end->next_ = next->next_;

            BorderMarker *region_start = reinterpret_cast<BorderMarker *>(
                get_ptr_to_start_bm(next_end + 1, next_end->size_));
            *region_start = *next_end;

            if (next->next_) {
                next->next_->prev_ = region_start;
            }

            if (next->prev_) {
                next->prev_->next_ = region_start;
            }

            if (next == head_) {
                head_ = region_start;
            }

            bm = region_start;
        }

        return bm;
    }

    // data members
    void *head_;
    void *start_;
    std::size_t size_;
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
void mysetup(void *buf, std::size_t size) { allocator.set_buffer(buf, size); }

// Функция аллокации
void *myalloc(std::size_t size) { return allocator.alloc(size); }

// Функция освобождения
void myfree(void *p) { allocator.free(p); }

int main()
{
    constexpr std::size_t mem_size = 102400;
    char *mem = new char[mem_size];

    mysetup(mem, mem_size);

    delete[] mem;
    return 0;
}
