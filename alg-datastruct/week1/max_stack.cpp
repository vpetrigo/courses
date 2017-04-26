/*
 * Проблема: Стек с поддержкой максимума
 * Реализовать стек с поддержкой операций push, pop и max
 *
 * Вход: последовательность запросов push, pop и max
 * Выход: для каждого запроса max вывести максимально число, находящееся на стеке
 *
 * Пример:
 *  Вход:
 *  3
 *  push 1
 *  push 7
 *  pop
 *  Выход:
 *
 *  Вход:
 *  5
 *  push 2
 *  push 1
 *  max
 *  pop
 *  max
 *  Выход:
 *  2
 *  2
 *
 */
#include "max_stack.hpp"

#include <iostream>

int main() {
  std::size_t cmd_query;
  std::string command;
  std::size_t num_to_push;
  MaxStack<std::size_t> stack;

  std::cin >> cmd_query;

  while (cmd_query-- > 0) {
    std::cin >> command;

    if (command.compare("push") == 0) {
      // read number to push
      std::cin >> num_to_push;
      stack.Push(num_to_push);
    }
    else if (command.compare("pop") == 0) {
      // pop from stack
      stack.Pop();
    }
    else {
      // in case there are no unusual commands provided
      // it would be "max" command -> get current maximum
      std::cout << stack.Max() << std::endl;
    }
  }

  return 0;
}
