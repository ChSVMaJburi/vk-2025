#pragma once

#include <atomic>
#include <chrono>
#include <memory>
#include <mutex>
#include <thread>
#include <unordered_map>

#include "IMetric.h"
#include "Writer.h"

namespace metrics {

class MetricsManager {
 public:
  explicit MetricsManager(const std::string& output_filename);
  ~MetricsManager();
  void RegisterMetric(const std::string& name,
                      std::unique_ptr<IMetric> new_metric);

  void Record(const std::string& name, double value = 1.0);

  void Flush();

  void StartBackgroundFlush(std::chrono::milliseconds interval);
  void StopBackgroundFlush();

 private:
  std::unordered_map<std::string, std::unique_ptr<IMetric>> metrics_;
  Writer writer_;
  std::atomic<bool> running_;
  std::mutex mtx_;
  std::thread flusher_;
};

}  // namespace metrics
