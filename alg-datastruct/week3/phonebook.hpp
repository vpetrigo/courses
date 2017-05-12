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

  explicit NumericHashTable(std::size_t table_size = default_table_size)
      : storage_{}, storage_size_{table_size}
  {
    storage_.resize(storage_size_);
  }

  void Add(const value_type& elem)
  {
    const auto hash_val = Hash(elem.first) % storage_size_;

    if (!storage_[hash_val].empty()) {
      auto it = storage_[hash_val].begin();
      auto end = storage_[hash_val].end();

      while (it != end) {
        if (it->first == elem.first) {
          it->second = elem.second;
          break;
        }

        ++it;
      }

      if (it == end) {
        storage_[hash_val].push_back(elem);
      }
    }
    else {
      storage_[hash_val].push_back(elem);
    }
  }

  std::string& Get(const std::size_t key)
  {
    const auto hash_val = Hash(key) % storage_size_;

    if (!storage_[hash_val].empty()) {
      for (auto& e : storage_[hash_val]) {
        if (e.first == key) {
          return e.second;
        }
      }
    }

    storage_[hash_val].emplace_back(std::make_pair(key, ""));

    return storage_[hash_val].back().second;
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
