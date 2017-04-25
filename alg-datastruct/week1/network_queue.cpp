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
