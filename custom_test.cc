#include <algorithm>
#include <queue>
#include <string>
#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <time.h>

#include "fiboqueue.h"

using std::string;

double GetMonotonicTime() {
  timespec ts;
  clock_gettime(CLOCK_MONOTONIC, &ts);
  const double time =
    static_cast<double>(ts.tv_sec) + static_cast<double>(ts.tv_nsec)*(1.0E-9);
  return time;
}

struct NonTrivialType {
  float data;
  NonTrivialType() = default;
  NonTrivialType(const float data) : data(data) {}
  bool operator<(const NonTrivialType& other) const {
    return data < other.data;
  }
};

struct STLQueueDataHolder{
  float key;
  int index;

  STLQueueDataHolder() = delete;
  STLQueueDataHolder(const float key, const int index) : key(key), index(index) {}

  bool operator<(const STLQueueDataHolder& other) const {
    return key < other.key;
  }
};

int main() {
  srand(time(nullptr));
  FibQueue<float> queue;
  std::priority_queue<STLQueueDataHolder, std::vector<STLQueueDataHolder>> stl_queue;

  // Generate random numbers.
  std::vector<float> random_numbers;
  size_t num_rands = rand() % 1000000 + 1000000;
  for (size_t i = 0; i < num_rands; ++i) {
    const float rand_f = static_cast<float>(rand()) / 100;
    random_numbers.push_back(rand_f);
  }

  // Create associated "data array"
  std::vector<NonTrivialType> non_trivial_types(random_numbers.size());
  for (size_t i = 0; i < random_numbers.size(); ++i) {
    non_trivial_types[i] = NonTrivialType(random_numbers[i]);
  }

  const auto fib_push_start = GetMonotonicTime();
  for (size_t i = 0; i < random_numbers.size(); ++i) {
    queue.push(random_numbers[i], static_cast<int>(i));
  }
  const auto fib_push_end = GetMonotonicTime();
  std::cout << "Fib push time delta: " << (fib_push_end - fib_push_start) << '\n';

  const auto stl_push_start = GetMonotonicTime();
  for (size_t i = 0; i < random_numbers.size(); ++i) {
    stl_queue.push({random_numbers[i], static_cast<int>(i)});
  }
  const auto stl_push_end = GetMonotonicTime();
  std::cout << "STL push time delta: " << (stl_push_end - stl_push_start) << '\n';

  std::vector<NonTrivialType> sorted_non_trivial_types = non_trivial_types;
  std::sort(sorted_non_trivial_types.begin(), sorted_non_trivial_types.end());

  const auto fib_read_start = GetMonotonicTime();
  std::vector<NonTrivialType> queue_non_trivial_types(non_trivial_types.size());
  for (size_t i = 0; !queue.empty(); ++i) {
    const int index = queue.pop();
    queue_non_trivial_types[i] = non_trivial_types[index];
  }
  const auto fib_read_end = GetMonotonicTime();
    std::cout << "Fib read time delta: " << (fib_read_end - fib_read_start) << '\n';

  std::vector<NonTrivialType> stl_queue_non_trivial_types(non_trivial_types.size());
  const auto stl_read_start = GetMonotonicTime();
  for (size_t i = 0; !queue.empty(); ++i) {
    const int index = stl_queue.top().index;
    stl_queue.pop();
    stl_queue_non_trivial_types[i] = non_trivial_types[index];
  }
  const auto stl_read_end = GetMonotonicTime();
  std::cout << "STL read time delta: " << (stl_read_end - stl_read_start) << '\n';

  for (size_t i = 0; i < sorted_non_trivial_types.size(); ++i) {
    const auto& queue = queue_non_trivial_types[i];
    const auto& sorted = sorted_non_trivial_types[i];
    if (queue.data != sorted.data) {
      std::cerr << "Not equal: "  << queue.data << " vs "  << sorted.data << " \n";
    }
  }

  return 0;
}
