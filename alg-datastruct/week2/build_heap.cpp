/*
 * Проблема: Построение кучи
 * Переставить элементы заданного массива чисел так, чтобы
 * он удовлетворял свойству мин-кучи.
 * Вход: массив чисел A[0 ... n - 1]
 * Выход: переставить элементы массива так, чтобы выполнялись
 * неравенства A[i] <= A[2i + 1] и A[i] <= A[2i + 2] для всех i
 *
 * Пример:
 *  Вход:
 *  5
 *  5 4 3 2 1
 *  Выход:
 *  3
 *  1 4
 *  0 1
 *  1 3
 *
 */
#include "build_heap.hpp"

#include <iostream>
#include <vector>

int main() {
  std::size_t input_size;
  HeapBuilder<std::size_t> hp;

  std::cin >> input_size;

  std::vector<std::size_t> numbers(input_size);

  for (auto& elem : numbers) {
    std::cin >> elem;
  }

  hp.BuildHeap(numbers.begin(), numbers.end());
  const auto& rearrange = hp.Rearrange();
  std::cout << rearrange.size() << std::endl;

  for (const auto& elem : rearrange) {
    std::cout << elem.first << ' ' << elem.second << std::endl;
  }

  return 0;
}
