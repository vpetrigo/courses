#include "phonebook.hpp"

#include <iostream>
#include <string>

int main()
{
  std::size_t n_queries;
  std::string command;
  NumericHashTable ht{1024};
  std::pair<std::size_t, std::string> query_storage;

  std::cin >> n_queries;

  while (n_queries-- > 0) {
    std::cin >> command;

    if (command.compare("add") == 0) {
      std::cin >> query_storage.first >> query_storage.second;
      ht.Add(std::make_pair(query_storage.first, query_storage.second));
    }
    else if (command.compare("find") == 0) {
      std::cin >> query_storage.first;

      auto elem_it = ht.Find(query_storage.first);

      if (elem_it != ht.End()) {
        std::cout << elem_it->second;
      }
      else {
        std::cout << "not found";
      }

      std::cout << std::endl;
    }
    else {
      // delete request
      std::cin >> query_storage.first;
      ht.Delete(query_storage.first);
    }
  }

  return 0;
}
