#pragma once
#include <string>

namespace metrics {

class IMetric {
 public:
  virtual ~IMetric() = default;
  virtual void Record(double value) = 0;
  virtual std::string SnapshotAndReset() = 0;
};

}  // namespace metrics
