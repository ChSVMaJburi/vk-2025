#pragma once

#include <atomic>

#include "IMetric.h"

namespace metrics {

class Counter : public IMetric {
public:
  void Record(double value) override;
  std::string SnapshotAndReset() override;

private:
  std::atomic<long> counter_{};
};

}  // namespace metrics

