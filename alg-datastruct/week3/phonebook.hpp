#ifndef _PHONEBOOK_HPP_
#define _PHONEBOOK_HPP_

#include <algorithm>
#include <list>
#include <string>
#include <vector>

constexpr std::size_t default_table_size = 128;

class NumericHashTable {
 public:
  using value_type = std::pair<std::size_t, std::string>;
  using iterator = std::list<value_type>::iterator;

  explicit NumericHashTable(std::size_t table_size = default_table_size)
      : storage_{}, storage_size_{table_size}
  {
    storage_.resize(storage_size_);
  }

  iterator Find(std::size_t key)
  {
    const auto hash_val = Hash(key) % storage_size_;

    if (!storage_[hash_val].empty()) {
      auto elem_it = std::find_if(
          storage_[hash_val].begin(), storage_[hash_val].end(),
          [&key](const value_type& elem) { return elem.first == key; });

      if (elem_it != storage_[hash_val].end()) {
        return elem_it;
      }
    }

    return End();
  }

  iterator End() {
    return storage_.back().end();
  }

  void Add(const value_type& elem)
  {
    auto elem_it = Find(elem.first);

    if (elem_it != End()) {
      elem_it->second = elem.second;
    }
    else {
      const auto hash_val = Hash(elem.first) % storage_size_;

      storage_[hash_val].push_back(elem);
    }
  }

  std::string& Get(const std::size_t key)
  {
    auto elem_it = Find(key);

    if (elem_it != End()) {
      return elem_it->second;
    }

    const auto hash_val = Hash(key) % storage_size_;

    storage_[hash_val].emplace_back(std::make_pair(key, ""));

    return storage_[hash_val].back().second;
  }

  void Delete(const std::size_t key) {
    auto elem_it = Find(key);

    if (elem_it != End()) {
      const auto hash_val = Hash(key) % storage_size_;

      storage_[hash_val].erase(elem_it);
    }
  }

 protected:
  std::size_t Hash(std::size_t x)
  {
    constexpr std::size_t magic1 = 0xbf58476d1ce4e5b9;
    constexpr std::size_t magic2 = 0x94d049bb133111eb;

    x = (x ^ (x >> 30)) * magic1;
    x = (x ^ (x >> 27)) * magic2;
    x = x ^ (x >> 31);

    return x;
  }

 private:
  std::vector<std::list<value_type>> storage_;
  std::size_t storage_size_;
};

#endif  // _PHONEBOOK_HPP_
