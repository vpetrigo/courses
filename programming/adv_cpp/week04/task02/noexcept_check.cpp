#include <type_traits>
#include <utility>  // std::declval

// внутри do_math объекты типа T
// - копируются
// - присваиваются
// - складываются оператором +
template <class T>
void do_math() noexcept(
    std::is_nothrow_copy_constructible<T>::value &&
        std::is_nothrow_copy_assignable<T>::value &&noexcept(std::declval<T>() +
                                                             std::declval<T>()))
{
    // тело функции нужно оставить пустым
}