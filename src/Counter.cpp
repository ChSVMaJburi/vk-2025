#include "../include/metrics/Counter.h"

#include <atomic>

namespace metrics {

void Counter::Record(double value) {
  counter_.fetch_add(static_cast<long>(value), std::memory_order_relaxed);
}

std::string Counter::SnapshotAndReset() {
  const long current_count = counter_.exchange(0, std::memory_order_relaxed);
  return std::to_string(current_count);
}

}  // namespace metrics