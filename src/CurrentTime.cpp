#include "../include/metrics/CurrentTime.h"

namespace metrics {

std::string CurrentTime() {
  using namespace std::chrono;

  const auto time_point = system_clock::now();
  const auto cur_seconds = system_clock::to_time_t(time_point);
  const auto cur_milliseconds =
      duration_cast<milliseconds>(time_point.time_since_epoch()) % 1000;

  std::tm tm_snapshot{};
#if defined(_WIN32) || defined(_WIN64)
  localtime_s(&tm_snapshot, &cur_seconds);
#else
  localtime_r(&tm_snapshot, &cur_seconds);
#endif

  std::ostringstream output;
  output << std::put_time(&tm_snapshot, "%Y-%m-%d %H:%M:%S") << "."
         << std::setw(3) << std::setfill('0') << cur_milliseconds.count();
  return output.str();
}

}  // namespace metrics