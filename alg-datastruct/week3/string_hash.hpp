#ifndef _STRING_HASH_HPP_
#define _STRING_HASH_HPP_

#include <algorithm>
#include <list>
#include <string>
#include <vector>

constexpr std::size_t prime = 1000000007;
constexpr std::size_t x = 263;

template <typename T> class HashFunction;

template <> class HashFunction<std::string> {
  public:
    std::size_t operator()(const std::string &s) const
    {
        auto pow_fast = [](std::size_t exp) {
            std::size_t result = 1;
            std::size_t base = x;

            while (exp > 0) {
                if (exp % 2 == 1) {
                    result = result * base % prime;
                }

                exp >>= 1;
                base = (base * base) % prime;
            }

            return result % prime;
        };

        std::size_t hash_val = 0;

        for (std::size_t i = 0; i < s.size(); ++i) {
            hash_val = (hash_val +
                        static_cast<std::size_t>(s[i]) * pow_fast(i) % prime) %
                       prime;
        }

        return hash_val;
    }
};

template <typename T, typename Hash = HashFunction<T>> class HashSet {
  public:
    using value_type = T;
    using iterator = typename std::list<T>::iterator;
    using const_iterator = typename std::list<T>::const_iterator;

    explicit HashSet(std::size_t bucket_size, Hash hash = Hash())
        : buckets_{bucket_size}, hash_{hash}
    {
        storage_.resize(buckets_);
    }

    const_iterator Find(const T &elem) const
    {
        const auto hash_val = hash_(elem) % buckets_;

        if (!storage_[hash_val].empty()) {
            auto elem_it = std::find_if(
                storage_[hash_val].cbegin(), storage_[hash_val].cend(),
                [&elem](const T &e) { return e == elem; });

            if (elem_it != storage_[hash_val].cend()) {
                return elem_it;
            }
        }

        return Cend();
    }

    iterator Find(const T &elem)
    {
        const auto hash_val = hash_(elem) % buckets_;

        if (!storage_[hash_val].empty()) {
            auto elem_it = std::find_if(
                storage_[hash_val].begin(), storage_[hash_val].end(),
                [&elem](const T &e) { return e == elem; });

            if (elem_it != storage_[hash_val].cend()) {
                return elem_it;
            }
        }

        return End();
    }

    iterator End() { return storage_.back().end(); }
    const_iterator Cend() const { return storage_.back().cend(); }
    void Add(const T &elem)
    {
        if (Find(elem) == Cend()) {
            const auto hash_val = hash_(elem) % buckets_;

            storage_[hash_val].push_front(elem);
        }
    }

    std::pair<const_iterator, const_iterator> Check(std::size_t bucket_id) const
    {
        return std::make_pair(storage_[bucket_id].cbegin(),
                              storage_[bucket_id].cend());
    }

    void Delete(const T &elem)
    {
        auto elem_it = Find(elem);

        if (elem_it != End()) {
            const auto hash_val = hash_(elem) % buckets_;

            storage_[hash_val].erase(elem_it);
        }
    }

  private:
    std::size_t buckets_;
    Hash hash_;
    std::vector<std::list<T>> storage_;
};

#endif // _STRING_HASH_HPP_
