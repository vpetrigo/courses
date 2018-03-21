#include <cassert>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <vector>

constexpr std::size_t ALIGNMENT = 4096;
constexpr std::size_t MAX_SLAB_ELEMS = 32;

constexpr std::size_t alloc_size(int order) { return ALIGNMENT * (1 << order); }

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
void free_slab(void *slab) {
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
        free_slab(reinterpret_cast<void *>(reinterpret_cast<std::size_t>(mem_block_start) & ~(alloc_size(0) - 1)));
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
        slab *sl = nullptr;

        if (!has_partial) {
            if (!has_free) {
                // allocate a new free slab
                void *new_mem = alloc_slab(slab_order);
                slab *new_slab =
                    new (static_cast<char *>(new_mem) + alloc_size(slab_order) -
                         sizeof(slab)) slab{new_mem, slab_order, object_size};
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
        if (!list_empty(&slabs_full))
        {
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

    void shrink()
    {
        release_slabs_list(&slabs_free);
    }

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
        if (!list_empty(list))
        {
            slab *it = list_head(list, slab, slabs);

            while (&it->slabs != list)
            {
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

    for (int i = 0; i < MAX_ORDER; ++i) {
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
void cache_release(struct cache *cache) { /* Реализуйте эту функцию. */}

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
    return nullptr;
}

/**
 * Функция освобождения памяти назад в кеширующий аллокатор.
 * Гарантируется, что ptr - указатель ранее возвращенный из
 * cache_alloc.
 **/
void cache_free(struct cache *cache, void *ptr)
{
    /* Реализуйте эту функцию. */
}

/**
 * Функция должна освободить все SLAB, которые не содержат
 * занятых объектов. Если SLAB не использовался для аллокации
 * объектов (например, если вы выделяли с помощью alloc_slab
 * память для внутренних нужд вашего алгоритма), то освбождать
 * его не обязательно.
 **/
void cache_shrink(struct cache *cache) { /* Реализуйте эту функцию. */}

int main()
{
    void *ptr = alloc_slab(4);
    std::cout << ptr << std::endl;
    slab s{ptr, 4, 32};

    void *data1 = s.get_memory();
    void *data2 = s.get_memory();

    std::cout << ptr << ' ' << data1 << ' ' << data2 << std::endl;
    s.traverse_mem_blocks();
    std::cout << s.get_free_slots() << std::endl;
    s.free_memory(data2);
    s.traverse_mem_blocks();
    std::cout << s.get_free_slots() << std::endl;
    s.free_memory(data1);
    s.traverse_mem_blocks();
    free_slab(ptr);
    std::cout << "End execution" << std::endl;

    return 0;
}
