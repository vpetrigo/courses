#include <cassert>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <memory>
#include <vector>
#include <algorithm>

constexpr std::size_t ALIGNMENT = 4096; /**< Memory allocation minimal alignment */
constexpr std::size_t MAX_SLAB_ELEMS = 32; /**< Maximum number of elements in a slab */

/**
 * \brief Get allocation size
 * \param[in] order Number of bytes in SLAB with given order (#ALIGNMENT * 2 ^ order) allocated memory
 */
constexpr std::size_t alloc_size(int order) { return ALIGNMENT * (1 << order); }

/**
 * \brief Return pointer to SLAB's memory start
 * \param[in] ptr Pointer that belongs to a SLAB
 * \param[in] order Memory order of a given SLAB
 */
void *get_slab_start(void *ptr, int order)
{
    return reinterpret_cast<void *>(reinterpret_cast<std::size_t>(ptr) & ~(alloc_size(order) - 1));
}

/**
 * Эти две функции вы должны использовать для аллокации
 * и освобождения памяти в этом задании. Считайте, что
 * внутри они используют buddy аллокатор с размером
 * страницы равным 4096 байтам.
 **/

/**
 * Аллоцирует участок размером 4096 * 2^order байт,
 * выровненный на границу 4096 * 2^order байт. order
 * должен быть в интервале [0; 10] (обе границы
 * включительно), т. е. вы не можете аллоцировать больше
 * 4Mb за раз.
 **/
void *alloc_slab(int order)
{
#ifdef _WIN32
    return _aligned_malloc(alloc_size(order), alloc_size(order));
#elif __linux__
    return aligned_alloc(alloc_size(order), alloc_size(order));
#endif
}
/**
 * Освобождает участок ранее аллоцированный с помощью
 * функции alloc_slab.
 **/
void free_slab(void *slab)
{
#ifdef _WIN32
    _aligned_free(slab);
#elif __linux__
    free(slab);
#endif
}

struct list {
    struct list *next, *prev;
};

#define LIST_HEAD_INIT(name)                                                   \
    {                                                                          \
        &(name), &(name)                                                       \
    }

#define LIST_HEAD(name) struct list name = LIST_HEAD_INIT(name)

static inline void list_init(struct list *list)
{
    list->next = list;
    list->prev = list;
}

static inline int list_empty(struct list *list) { return list->next == list; }

static inline void list_insert(struct list *link, struct list *new_link)
{
    new_link->prev = link->prev;
    new_link->next = link;
    new_link->prev->next = new_link;
    new_link->next->prev = new_link;
}

static inline void list_append(struct list *list, struct list *new_link)
{
    list_insert(list, new_link);
}

static inline void list_prepend(struct list *list, struct list *new_link)
{
    list_insert(list->next, new_link);
}

static inline void list_remove(struct list *link)
{
    link->prev->next = link->next;
    link->next->prev = link->prev;
}

#define list_entry(link, type, member)                                         \
    (reinterpret_cast<type *>(                                                 \
        (reinterpret_cast<char *>(link) -                                      \
         reinterpret_cast<char *>(&(static_cast<type *>(nullptr))->member))))

#define list_head(list, type, member) list_entry((list)->next, type, member)

#define list_tail(list, type, member) list_entry((list)->prev, type, member)

#define list_next(elm, member)                                                 \
    list_entry((elm)->member.next, __typeof__(*elm), member)

#define list_for_each_entry(pos, list, member)                                 \
    for (pos = list_head(list, __typeof__(*pos), member);                      \
         &pos->member != (list); pos = list_next(pos, member))

struct mem_block {
    mem_block(void *d, bool free) : data{d}, free{free} { list_init(&blocks); }

    void *data;
    bool free;
    list blocks;
};

unsigned long get_free_slots_mask(int max_elems)
{
    return (1ULL << max_elems) - 1;
}

struct Slab {
    virtual void *get_memory() = 0;
    virtual void free_memory(void *ptr) = 0;
    virtual bool is_empty() const = 0;
    virtual bool is_full() const = 0;
    virtual int get_free_slots() const = 0;
    virtual void release() = 0;
    virtual void set_list(const list *list) = 0;
    virtual const list *get_list() const = 0;
};

struct array_slab {
  public:
    array_slab(void *mem, int slab_order, std::size_t object_size, std::size_t slab_elems = MAX_SLAB_ELEMS)
        : slab_order{slab_order}, object_size{object_size}, slab_elems{slab_elems}
    {
        free_slots = get_free_slots_mask(slab_elems);
        list_init(&slabs);
        allocate_mem_blocks(mem);
    }

    void *get_memory()
    {
        if (free_slots != 0) {
            int slot = get_first_free_slot(free_slots);

            assert(slot >= 0);
            return allocate_slot(slot);
        }

        return nullptr;
    }

    void free_memory(void *ptr)
    {
        std::size_t mem_pos =
            std::distance(static_cast<char *>(get_slab_start(ptr, slab_order)),
                          static_cast<char *>(ptr)) / object_size;
        free_slot(mem_pos);
    }

    bool is_empty() const { return free_slots == get_free_slots_mask(slab_elems); }

    bool is_full() const { return free_slots == 0; }

    void print_mask(void)
    {
        for (std::size_t i = slab_elems - 1; i < slab_elems; --i) {
            std::cout << (free_slots & (1UL << i));
        }

        std::cout << std::endl;
    }

    int get_free_slots(void)
    {
        int counter = 0;

        for (std::size_t i = slab_elems - 1; i < slab_elems; --i) {
            if ((free_slots & (1UL << i)) != 0) {
                ++counter;
            }
        }

        return counter;
    }

    void release() {
        free_slots = 0;
        free_slab(*mem_array_ptr);
    }

    void set_list(const list *list) {
        cache_list = list;
    }

    const list *get_list(void) const {
        return cache_list;
    }
  private:
    int get_first_free_slot(unsigned long mask)
    {
        //return MAX_SLAB_ELEMS - __builtin_clz(free_slots) - 1;
        for (int i = slab_elems - 1; i < slab_elems; --i) {
            if (free_slots & (1UL << i)) {
                return i;
            }
        }

        return -1;
    }

    void *allocate_slot(int slot)
    {
        free_slots &= ~(1UL << slot);
        return mem_array_ptr[slab_elems - slot - 1];
    }

    void free_slot(int slot)
    {
        free_slots |= (1UL << (slab_elems - slot - 1));
    }

    void allocate_mem_blocks(void *mem)
    {
        for (std::size_t i = 0; i < slab_elems; ++i) {
            mem_array_ptr[i] = static_cast<char *>(mem) + i * object_size;
        }
    }

  public:
    int slab_order;
    std::size_t object_size;
    std::size_t slab_elems;
    unsigned long free_slots;
    void *mem_array_ptr[MAX_SLAB_ELEMS];
    const list *cache_list;
    list slabs;
};

struct slab {
  public:
    slab(void *mem, int slab_order, std::size_t object_size)
        : object_size{object_size}, mem{mem}, slab_order{slab_order}
    {
        free_slots = MAX_SLAB_ELEMS;
        list_init(&mem_blocks);
        list_init(&slabs);
        allocate_mem_blocks(mem);
    }

    void *get_memory(void)
    {
        if (free_slots > 0) {
            --free_slots;

            mem_block *ptr = nullptr;

            list_for_each_entry(ptr, &mem_blocks, blocks)
            {
                if (ptr->free) {
                    ptr->free = false;
                    return ptr->data;
                }
            }
        }

        return nullptr;
    }

    void free_memory(void *data)
    {
        mem_block *ptr = nullptr;

        list_for_each_entry(ptr, &mem_blocks, blocks)
        {
            if (ptr->data == data) {
                ptr->free = true;
                ++free_slots;
                break;
            }
        }
    }

    void release()
    {
        void *mem_block_start = list_head(&mem_blocks, mem_block, blocks);
        free_slab(get_slab_start(mem_block_start, 0));
    }

    bool is_full() const { return free_slots == 0; }

    bool is_empty() const { return free_slots == MAX_SLAB_ELEMS; }

    std::size_t get_free_slots() const { return free_slots; }

    void traverse_mem_blocks()
    {
        std::size_t i = 1;
        mem_block *ptr = nullptr;
        list_for_each_entry(ptr, &mem_blocks, blocks)
        {
            std::cout << i++ << std::endl;
            std::cout << "Is free: " << ptr->free << std::endl;
            std::cout << "Ptr: " << ptr->data << std::endl;
        }
    }

  private:
    void allocate_mem_blocks(void *slab_mem)
    {
        constexpr std::size_t MEMBLOCK_ORDER = 0;
        void *mem = alloc_slab(MEMBLOCK_ORDER);

        for (std::size_t i = 0; i < MAX_SLAB_ELEMS; ++i) {
            void *mem_block_ptr =
                static_cast<char *>(mem) + i * sizeof(mem_block);
            mem_block *tmp = new (mem_block_ptr) mem_block{
                static_cast<char *>(slab_mem) + i * object_size, true};
            list_append(&mem_blocks, &tmp->blocks);
        }
    }

  public:
    std::size_t free_slots;
    std::size_t object_size;
    void *mem;
    int slab_order;
    list mem_blocks;
    list slabs;
};
/**
 * Эта структура представляет аллокатор, вы можете менять
 * ее как вам удобно. Приведенные в ней поля и комментарии
 * просто дают общую идею того, что вам может понадобится
 * сохранить в этой структуре.
 **/
struct cache {
  public:
    void *allocate()
    {
        bool has_partial = !list_empty(&slabs_partial);
        bool has_free = !list_empty(&slabs_free);
        array_slab *sl = nullptr;

        if (!has_partial) {
            if (!has_free) {
                // allocate a new free slab
                void *new_mem = alloc_slab(slab_order);
                array_slab *new_slab =
                    new (static_cast<char *>(new_mem) + alloc_size(slab_order) -
                         sizeof(array_slab)) array_slab{new_mem, slab_order, object_size, slab_max_elems};
                list_append(&slabs_partial, &new_slab->slabs);
                sl = new_slab;
            }
            else {
                // start using free slab
                sl = list_head(&slabs_free, slab, slabs);
                list_remove(&sl->slabs);
                list_append(&slabs_partial, &sl->slabs);
            }
        }
        else {
            // use partial
            sl = list_entry(slabs_partial.next, slab, slabs);
        }

        void *mem = sl->get_memory();

        if (sl->is_full()) {
            list_remove(&sl->slabs);
            list_append(&slabs_full, &sl->slabs);
        }

        return mem;
    }

    void free(void *ptr)
    {
        slab *slab_to_free = get_slab(ptr);

        slab_to_free->free_memory(ptr);
        slab *it = nullptr;
        if (!list_empty(&slabs_full)) {
            list_for_each_entry(it, &slabs_full, slabs)
            {
                if (it == slab_to_free) {
                    // remove SLAB from fully occupied SLAB list
                    list_remove(&slab_to_free->slabs);
                    // append this SLAB to partial free SLAB list
                    list_append(&slabs_partial, &slab_to_free->slabs);
                    return;
                }
            }
        }

        if (slab_to_free->is_empty() && !list_empty(&slabs_partial)) {
            it = nullptr;
            list_for_each_entry(it, &slabs_partial, slabs)
            {
                if (it == slab_to_free) {
                    list_remove(&slab_to_free->slabs);
                    list_append(&slabs_free, &slab_to_free->slabs);
                    return;
                }
            }
        }
    }

    void shrink() { release_slabs_list(&slabs_free); }

    void release()
    {
        release_slabs_list(&slabs_free);
        release_slabs_list(&slabs_full);
        release_slabs_list(&slabs_partial);
    }

  private:
    slab *get_slab(void *ptr) const
    {
        return reinterpret_cast<slab *>(
            reinterpret_cast<char *>(reinterpret_cast<std::size_t>(ptr) &
                                     ~(alloc_size(slab_order) - 1)) +
            alloc_size(slab_order) - sizeof(slab));
    }

    void release_slabs_list(list *list)
    {
        if (!list_empty(list)) {
            slab *it = list_head(list, slab, slabs);

            while (&it->slabs != list) {
                slab *tmp = list_next(it, slabs);
                list_remove(&it->slabs);
                it->release();
                free_slab(it->mem);
                it = tmp;
            }
        }
    }

  public:
    /* список пустых SLAB-ов для поддержки cache_shrink */
    list slabs_free;
    /* список частично занятых SLAB-ов */
    list slabs_partial;
    /* список заполненых SLAB-ов */
    list slabs_full;

    size_t object_size; /* размер аллоцируемого объекта */
    int slab_order;     /* используемый размер SLAB-а */
    size_t slab_objects; /* количество объектов в одном SLAB-е */
};

int determine_slab_order(std::size_t object_size, std::size_t num_of_elems)
{
    constexpr std::size_t MAX_ORDER = 10;

    for (int i = 0; i < MAX_ORDER + 1; ++i) {
        if (alloc_size(i) - sizeof(slab) >= num_of_elems * object_size) {
            return i;
        }
    }

    return -1;
}

/**
 * Функция инициализации будет вызвана перед тем, как
 * использовать это кеширующий аллокатор для аллокации.
 * Параметры:
 *  - cache - структура, которую вы должны инициализировать
 *  - object_size - размер объектов, которые должен
 *    аллоцировать этот кеширующий аллокатор
 **/
void cache_setup(struct cache *cache, size_t object_size)
{
    /* Реализуйте эту функцию. */
    cache->object_size = object_size;
    list_init(&cache->slabs_free);
    list_init(&cache->slabs_partial);
    list_init(&cache->slabs_full);
    cache->slab_order =
        determine_slab_order(cache->object_size, MAX_SLAB_ELEMS);
    assert(cache->slab_order >= 0);
    cache->slab_objects = MAX_SLAB_ELEMS;
}

/**
 * Функция освобождения будет вызвана когда работа с
 * аллокатором будет закончена. Она должна освободить
 * всю память занятую аллокатором. Проверяющая система
 * будет считать ошибкой, если не вся память будет
 * освбождена.
 **/
void cache_release(struct cache *cache)
{
    /* Реализуйте эту функцию. */
    cache->release();
}

/**
 * Функция аллокации памяти из кеширующего аллокатора.
 * Должна возвращать указатель на участок памяти размера
 * как минимум object_size байт (см cache_setup).
 * Гарантируется, что cache указывает на корректный
 * инициализированный аллокатор.
 **/
void *cache_alloc(struct cache *cache)
{
    /* Реализуйте эту функцию. */
    return cache->allocate();
}

/**
 * Функция освобождения памяти назад в кеширующий аллокатор.
 * Гарантируется, что ptr - указатель ранее возвращенный из
 * cache_alloc.
 **/
void cache_free(struct cache *cache, void *ptr)
{
    /* Реализуйте эту функцию. */
    cache->free(ptr);
}

/**
 * Функция должна освободить все SLAB, которые не содержат
 * занятых объектов. Если SLAB не использовался для аллокации
 * объектов (например, если вы выделяли с помощью alloc_slab
 * память для внутренних нужд вашего алгоритма), то освбождать
 * его не обязательно.
 **/
void cache_shrink(struct cache *cache)
{
    /* Реализуйте эту функцию. */
    cache->shrink();
}

void test1()
{
    void *ptr = alloc_slab(4);
    slab s{ptr, 4, 32};
    void *data1 = s.get_memory();
    void *data2 = s.get_memory();

    assert(data1 != nullptr);
    assert(data2 != nullptr);
    assert(s.get_free_slots() == (MAX_SLAB_ELEMS - 2));
    s.free_memory(data2);
    assert(s.get_free_slots() == (MAX_SLAB_ELEMS - 1));
    s.free_memory(data1);
    assert(s.get_free_slots() == (MAX_SLAB_ELEMS));
    s.release();
    free_slab(ptr);
    std::cout << __func__ << ": passed" << std::endl;
}

void test2()
{
    cache mem_cache;

    cache_setup(&mem_cache, 32);
    void *data1 = cache_alloc(&mem_cache);
    assert(data1 != nullptr);
    void *data2 = cache_alloc(&mem_cache);
    assert(data2 != nullptr);
    cache_free(&mem_cache, data1);
    cache_free(&mem_cache, data2);
    cache_shrink(&mem_cache);
    cache_release(&mem_cache);
    std::cout << __func__ << ": passed" << std::endl;
}

void test3()
{
    cache mem_cache;

    cache_setup(&mem_cache, 256);
    std::vector<void *> ptr_list;

    for (std::size_t i = 0; i < MAX_SLAB_ELEMS * 3; ++i) {
        void *tmp = cache_alloc(&mem_cache);
        assert(tmp != nullptr);
        ptr_list.emplace_back(tmp);
    }

    for (std::size_t i = 0; i < MAX_SLAB_ELEMS; ++i) {
        void *tmp = ptr_list.back();

        assert(tmp != nullptr);
        ptr_list.pop_back();
        cache_free(&mem_cache, tmp);
    }

    cache_shrink(&mem_cache);
    cache_release(&mem_cache);
    std::cout << __func__ << ": passed" << std::endl;
}

void test4()
{
    cache mem_cache;
    std::vector<void *> ptr_list;
    constexpr std::size_t ALLOC_MEM_SIZE = MAX_SLAB_ELEMS * 8192;

    cache_setup(&mem_cache, 130000);

    for (std::size_t i = 0; i < ALLOC_MEM_SIZE; ++i) {
        void *tmp = cache_alloc(&mem_cache);
        assert(tmp != nullptr);
        ptr_list.emplace_back(tmp);
    }

    for (std::size_t i = MAX_SLAB_ELEMS * 32; i < MAX_SLAB_ELEMS * 128; ++i) {
        cache_free(&mem_cache, ptr_list[i]);
    }

    cache_shrink(&mem_cache);
    cache_release(&mem_cache);
    ptr_list.clear();
    cache_setup(&mem_cache, 128);

    for (std::size_t i = 0; i < MAX_SLAB_ELEMS * 64; ++i) {
        void *tmp = cache_alloc(&mem_cache);
        assert(tmp != nullptr);
        ptr_list.emplace_back(tmp);
    }

    cache_release(&mem_cache);
    ptr_list.clear();
    std::cout << __func__ << ": passed" << std::endl;
}

int main()
{
    test1();
    test2();
    test3();
    test4();
    return 0;
}
