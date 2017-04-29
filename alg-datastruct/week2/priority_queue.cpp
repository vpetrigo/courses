/*
 * Проблема: Параллельная обработка
 * По данным n процессорам и m задач определите, для каждой из задач,
 * каким процессором она будет обработана.
 * Вход: число процессоров n и последовательность чисел t(0), ..., t(m - 1),
 * где t(i) - время, необходимое на обработку i-й задачи
 * Выход: для каждой задачи определите, какой процессор и в какое
 * время начнет ее обрабатывать, предполагая, что каждая задача
 * поступает на обработку первому освободившемуся процессору
 *
 * Пример:
 *  Вход:
 *  2 5
 *  1 2 3 4 5
 *  Выход:
 *  0 0
 *  1 0
 *  0 1
 *  1 2
 *  0 4
 *
 */
#include "priority_queue.hpp"

#include <iostream>

int main()
{
  using TaskType = std::pair<std::size_t, std::size_t>;
  constexpr std::size_t INIT_TIME = 0;
  PriorityQueue<TaskType, std::greater<TaskType>> core_queue;
  std::size_t cores, tasks;
  std::size_t duration;

  std::cin >> cores >> tasks;

  // initialize core queue
  for (std::size_t i = 0; i < cores && i < tasks; ++i) {
    std::cin >> duration;
    std::cout << core_queue.Size() << ' ' << INIT_TIME << std::endl;
    core_queue.AddElement(std::make_pair(duration, core_queue.Size()));
  }

  tasks -= core_queue.Size();

  while (tasks-- > 0) {
    auto finished_task = core_queue.ExtractTop();

    std::cin >> duration;
    std::cout << finished_task.second << ' ' << finished_task.first
              << std::endl;
    core_queue.AddElement(
        std::make_pair(finished_task.first + duration, finished_task.second));
  }

  return 0;
}
