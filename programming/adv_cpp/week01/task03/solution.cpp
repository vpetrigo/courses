// возвращает true, если p и q указывают на один и тот же объект
template<class T>
bool isSameObject(T const * p, T const * q)
{
    return dynamic_cast<void *>(const_cast<T *>(p)) == dynamic_cast<void *>(const_cast<T *>(q));
}