#include <iterator>
#include <list>
#include <numeric>
#include <vector>

#include <iostream>

template <class T>
class VectorList {
   private:
    using VectT = std::vector<T>;
    using ListT = std::list<VectT>;

   public:
    using value_type = T;

    VectorList() = default;
    VectorList(VectorList const &) = default;
    VectorList(VectorList &&) = default;

    VectorList &operator=(VectorList &&) = default;
    VectorList &operator=(VectorList const &) = default;

    // метод, который будет использоваться для заполнения VectorList
    // гарантирует, что в списке не будет пустых массивов
    // определена снаружи
    template <class It>
    void append(It p, It q)
    {
        if (p != q) data_.push_back(VectT(p, q));
    }

    bool empty() const { return size() == 0; }

    // определите метод size
    size_t size() const
    {
        return std::accumulate(
            data_.cbegin(), data_.cend(), 0,
            [](std::size_t init, const VectT &v) { return init + v.size(); });
    }

    // определите const_iterator
    struct const_iterator {
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = const T *;
        using reference = const T &;
        using iterator_category = typename std::iterator_traits<
            typename ListT::const_iterator>::iterator_category;

        explicit const_iterator(typename ListT::const_iterator lit)
            : list_it_{lit}, index_{0}, elem_index_{0}
        {
        }
        const_iterator(typename ListT::const_iterator lit, std::size_t index)
            : list_it_{lit}, index_{index}, elem_index_{0}
        {
        }

        const_iterator &operator++()
        {
            if (++elem_index_ == list_it_->size()) {
                ++list_it_;
                elem_index_ = 0;
            }

            ++index_;

            return *this;
        }

        const_iterator operator++(int)
        {
            const_iterator tmp{*this};

            ++(*this);

            return tmp;
        }

        const_iterator &operator--()
        {
            if (elem_index_ == 0) {
                elem_index_ = (--list_it_)->size();
            }

            --elem_index_;
            --index_;

            return *this;
        }

        const_iterator operator--(int)
        {
            const_iterator tmp{*this};

            --(*this);

            return tmp;
        }

        reference operator*() const
        {
            auto it = list_it_->cbegin();

            std::advance(it, elem_index_);

            return *it;
        }

        pointer operator->() const { return &(*(*this)); }

        bool operator==(const const_iterator &it) const
        {
            return (index_ == it.index_);
        }

        bool operator!=(const const_iterator &it) const
        {
            return !(*this == it);
        }

       private:
        typename ListT::const_iterator list_it_;
        std::size_t index_;
        std::size_t elem_index_;
    };

    // определите методы begin / end
    const_iterator begin() const { return const_iterator{data_.cbegin()}; }
    const_iterator end() const { return const_iterator{data_.cend(), size()}; }

    // определите const_reverse_iterator
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    // определите методы rbegin / rend
    const_reverse_iterator rbegin() const
    {
        return const_reverse_iterator{end()};
    }
    const_reverse_iterator rend() const
    {
        return const_reverse_iterator{begin()};
    }

   private:
    ListT data_;
};

int main()
{
    VectorList<int> vl;
    std::vector<int> v1{1, 2, 3, 4, 5};
    std::vector<int> v2{6, 7, 8};
    std::vector<int> v3{9, 10, 11, 12};

    vl.append(v1.cbegin(), v1.cend());
    vl.append(v2.cbegin(), v2.cend());
    vl.append(v3.cbegin(), v3.cend());

    std::cout << vl.size() << " " << v1.size() + v2.size() + v3.size()
              << std::endl;

    for (const auto &e : vl) {
        std::cout << e << ' ';
    }
    std::cout << std::endl;

    VectorList<std::string> vs;
    std::vector<std::string> vs1{"Hello", "World!"};

    vs.append(vs1.cbegin(), vs1.cend());
    auto it = vs.begin();

    std::cout << it->size() << std::endl;
    std::cout << (++it)->size() << std::endl;

    auto rit = vl.rbegin();
    while (rit != vl.rend()) {
        std::cout << *rit++ << ' ';
    }
    std::cout << std::endl;

    return 0;
}