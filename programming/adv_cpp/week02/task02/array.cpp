#include <cstddef>
#include <utility>
#include <algorithm>

template<class T>
struct Array
{
    // все объявленные ниже методы уже реализованы
    explicit Array(std::size_t size = 0);
    Array(Array const& a) : size_{a.size_} {
        data_ = new T[size_];
        std::copy(a.data_, a.data_ + size_, data_);
    }
    Array & operator=(Array const& a) {
        if (this != &a) {
            Array(a).swap(*this);
        }
    }

    ~Array() {
        delete[] data_;
        data_ = nullptr;
        size_ = 0;
    }

    std::size_t size() const;
    T &         operator[](std::size_t i);
    T const&    operator[](std::size_t i) const;

    // реализуйте перемещающий конструктор
    Array(Array&& a) : data_{a.data_}, size_{a.size_} {
        a.data_ = nullptr;
        a.size_ = 0;
    }

    // реализуйте перемещающий оператор присваивания
    Array& operator=(Array&& a) {
        if (this != &a) {
            swap(a);
        }

        return *this;
    }

    void swap(Array& a) {
        std::swap(size_, a.size_);
        std::swap(data_, a.data_);
    }

private:    
    std::size_t  size_;
    T *     data_;    
};