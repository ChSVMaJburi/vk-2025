#pragma once
#include <fstream>
#include <string>

namespace metrics {

class Writer {
 public:
  explicit Writer(const std::string& filename);

  void WriteLine(const std::string& line);

 private:
  std::ofstream output_;
};

}  // namespace metrics
