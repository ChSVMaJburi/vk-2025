#include "../include/metrics/MetricsManager.h"

#include <chrono>
#include <memory>
#include <sstream>
#include <thread>
#include <unordered_map>
#include <vector>

#include "metrics/CurrentTime.h"

namespace metrics {

MetricsManager::MetricsManager(const std::string& output_filename)
    : writer_(output_filename), running_(false) {}
MetricsManager::~MetricsManager() {
  StopBackgroundFlush();
  Flush();
}

void MetricsManager::RegisterMetric(const std::string& name,
                                    std::unique_ptr<IMetric> new_metric) {
  std::lock_guard<std::mutex> lock(mtx_);
  if (metrics_.count(name)) {
    throw std::runtime_error("This metric already registered: " + name);
  }
  metrics_.emplace(name, std::move(new_metric));
}

void MetricsManager::Record(const std::string& name, double value) {
  IMetric* metric_ptr = nullptr;
  {
    std::lock_guard lock(mtx_);
    const auto it = metrics_.find(name);
    if (it == metrics_.end()) {
      throw std::runtime_error("Unknown metric: " + name);
    }
    metric_ptr = it->second.get();
  }
  metric_ptr->Record(value);
}

void MetricsManager::Flush() {
  std::vector<std::pair<std::string, IMetric*>> snapshot;
  {
    std::lock_guard<std::mutex> lock(mtx_);
    snapshot.reserve(metrics_.size());
    for (auto& [name_of_metric, ptr_of_metric] : metrics_) {
      snapshot.emplace_back(name_of_metric, ptr_of_metric.get());
    }
  }

  std::ostringstream oss;
  oss << CurrentTime();
  for (auto& [name_of_metric, metric] : snapshot) {
    oss << " \"" << name_of_metric << "\" " << metric->SnapshotAndReset();
  }

  writer_.WriteLine(oss.str());
}

void MetricsManager::StartBackgroundFlush(std::chrono::milliseconds interval) {
  bool expected = false;
  if (!running_.compare_exchange_strong(expected, true)) {
    return;
  }

  flusher_ = std::thread([this, interval]() {
    while (running_) {
      std::this_thread::sleep_for(interval);
      Flush();
    }
  });
}
void MetricsManager::StopBackgroundFlush() {
  bool expected = true;
  if (!running_.compare_exchange_strong(expected, false)) {
    return;
  }
  if (flusher_.joinable()) {
    flusher_.join();
  }
}

}  // namespace metrics