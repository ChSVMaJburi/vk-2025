#include <chrono>
#include <thread>

#include "metrics/Counter.h"
#include "metrics/Gauge.h"
#include "metrics/MetricsManager.h"

int main() {
  metrics::MetricsManager manager("metrics_output.txt");
  manager.RegisterMetric("requests", std::make_unique<metrics::Counter>());
  manager.RegisterMetric("cpu_usage", std::make_unique<metrics::Gauge>());

  manager.StartBackgroundFlush(std::chrono::seconds(1));

  for (int phase = 0; phase < 3; ++phase) {
    for (int i = 0; i < 5; ++i) {
      manager.Record("requests", 1);
      manager.Record("cpu_usage", phase * 0.1 + i * 0.05);
      std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
  }

  manager.StopBackgroundFlush();
  return 0;
}