/*
 * Проблема: Обработка сетевых пакетов
 * Реализовать обработчик сетевых пакетов.
 *
 * Вход: Размер буфера size и число пакетов n, а также две
 * последовательности arrival(1), ... , arrival(n) и
 * duration(1), ... , duration(n), обозначающих время поступления и
 * длительность обработки n пакетов.
 * Выход: для каждого из данных n пакетов необходимо вывести
 * время начала его обработки или -1, ели пакет не был обработан
 * (это происходит в случае, когда пакет поступает в момент,
 * когда в буфере компьютера уже находится size пакетов)
 *
 * Пример:
 *  Вход:
 *  1 0
 *  Выход:
 *
 *  Вход:
 *  1 1
 *  0 0
 *  Выход:
 *  0
 *
 *  Вход:
 *  1 2
 *  0 1
 *  0 1
 *  Выход:
 *  0
 *  -1
 *
 */
#include "network_queue.h"

#include <iostream>

using NetworkPacket = std::pair<std::size_t, std::size_t>;
using NumNetworkQueue = NetworkQueue<std::size_t>;

int main()
{
  std::size_t queue_size, packet_number;
  constexpr int QUEUE_IS_FULL = -1;

  std::cin >> queue_size >> packet_number;

  NumNetworkQueue n_queue{queue_size};
  NetworkPacket packet{0, 0};

  for (std::size_t i = 0; i < packet_number; ++i) {
    std::cin >> packet.first >> packet.second;

    while (!n_queue.Empty() && packet.first >= n_queue.Top()) {
      // process packets that can be processed before a new packet
      n_queue.Pop();
    }

    if (!n_queue.Full()) {
      std::size_t process_start =
          (n_queue.Empty()) ? packet.first : n_queue.Back();
      std::size_t process_end = process_start + packet.second;

      n_queue.Push(process_end);
      std::cout << process_start << std::endl;
    }
    else {
      std::cout << QUEUE_IS_FULL << std::endl;
    }
  }

  return 0;
}
