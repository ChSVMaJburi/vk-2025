#include "../include/metrics/Gauge.h"

#include <atomic>

namespace metrics {

void Gauge::Record(double value) {
  count_.fetch_add(1, std::memory_order_relaxed);
  sum_.fetch_add(value, std::memory_order_relaxed);
}
std::string Gauge::SnapshotAndReset() {
  const long current_count = count_.exchange(0, std::memory_order_relaxed);
  const double current_sum = sum_.exchange(0, std::memory_order_relaxed);
  return std::to_string(current_count == 0 ? 0 : current_sum / current_count);
}

}  // namespace metrics