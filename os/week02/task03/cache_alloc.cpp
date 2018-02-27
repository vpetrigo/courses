#include <cstdlib>
#include <iostream>
#include <cassert>

constexpr std::size_t ALIGNMENT = 4096;

constexpr std::size_t alloc_size(int order)
{
    return ALIGNMENT * (1 << order);
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
    return _aligned_malloc(alloc_size(order), alloc_size(order));
}
/**
 * Освобождает участок ранее аллоцированный с помощью
 * функции alloc_slab.
 **/
void free_slab(void *slab) { _aligned_free(slab); }

struct list {
    struct list *next, *prev;
};

#define LIST_HEAD_INIT(name) { &(name), &(name) }

#define LIST_HEAD(name) \
    struct list name = LIST_HEAD_INIT(name)

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
    list_insert((struct list *)list, new_link);
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
    ((type *)((char *)(link) - (unsigned long)(&((type *)0)->member)))

#define list_head(list, type, member) list_entry((list)->next, type, member)

#define list_tail(list, type, member) list_entry((list)->prev, type, member)

#define list_next(elm, member)                                                 \
    list_entry((elm)->member.next, typeof(*elm), member)

#define list_for_each_entry(pos, list, member)                                 \
    for (pos = list_head(list, typeof(*pos), member); &pos->member != (list);  \
         pos = list_next(pos, member))

struct mem_block {
    void *data;
    bool free;
    list blocks;
};

struct slab {
    std::size_t free_slots;
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
    void *allocate(void)
    {
        bool has_partial = !list_empty(slabs_partial);
        bool has_free = !list_empty(slabs_free);

        if (!has_partial)
        {
            if (!has_free)
            {
                // allocate a new free slab
            }
            else
            {
                // start using free slab
            }
        }
        else
        {
            // use partial
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

    for (int i = 0; i < MAX_ORDER; ++i)
    {
        if (alloc_size(i) - sizeof(slab) >= num_of_elems * object_size)
        {
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
    constexpr std::size_t MAX_SLAB_ELEMS = 64;

    cache->object_size = object_size;
    list_init(cache->slabs_free);
    list_init(cache->slabs_partial);
    list_init(cache->slabs_full);
    cache->slab_order = determine_slab_order(cache->object_size, MAX_SLAB_ELEMS);
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
void cache_release(struct cache *cache) { /* Реализуйте эту функцию. */ }

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
void cache_shrink(struct cache *cache) { /* Реализуйте эту функцию. */ }

int main()
{
    void *ptr = alloc_slab(10);
    void *ptr1 = alloc_slab(1);

    std::cout << ptr << std::endl;
    std::cout << ptr1 << std::endl;

    free_slab(ptr);
    free_slab(ptr1);

    return 0;
}
