#include "network_queue.h"

#include <iostream>

using NetworkPacket = std::pair<std::size_t, std::size_t>;
using NumNetworkQueue = NetworkQueue<NetworkPacket>;

static void handle_processed_packets(const NetworkPacket& packet, std::size_t& cur_time, NumNetworkQueue& queue) {
  auto& top_packet = queue.Top();

  while (!queue.Empty() && packet.first >= (top_packet.first + top_packet.second)) {
    cur_time += top_packet.first + top_packet.second;
    queue.Pop();
    std::cout << cur_time << std::endl;
    top_packet = queue.Top();
  }
}

int main() {
  std::size_t queue_size, packet_number;

  std::cin >> queue_size >> packet_number;

  NumNetworkQueue n_queue{queue_size};
  std::size_t cur_time = 0;
  NetworkPacket packet{0, 0};

  for (std::size_t i = 0; i < packet_number; ++i) {
    std::cin >> packet.first >> packet.second;

    if (!n_queue.Full()) {
      n_queue.Push(packet);
    }
    else {
      /*auto& top_packet = n_queue.Top();

      while (!n_queue.Empty() && packet.first >= (top_packet.first + top_packet.second)) {
        cur_time += top_packet.first + top_packet.second;
        n_queue.Pop();
        std::cout << cur_time << std::endl;
        top_packet = n_queue.Top();
      }*/
      handle_processed_packets(packet, cur_time, n_queue);

      if (n_queue.Full()) {
        std::cout << -1 << std::endl;
      }
      else {
        n_queue.Push(packet);
      }
    }
  }

  while (!n_queue.Empty()) {

  }

  return 0;
}
