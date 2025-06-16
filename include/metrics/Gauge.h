#pragma once

#include <atomic>

#include "IMetric.h"

namespace metrics {
class Gauge : public IMetric {
 public:
  void Record(double value) override;
  std::string SnapshotAndReset() override;

 private:
  std::atomic<double> sum_{};
  std::atomic<long> count_{};
};
}  // namespace metrics
