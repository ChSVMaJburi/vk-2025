#include "../include/metrics/Writer.h"

#include <fstream>
#include <string>
namespace metrics {

Writer::Writer(const std::string& filename) : output_(filename, std::ios::app) {
  if (!output_) {
    throw std::runtime_error("Cannot open file");
  }
}
void Writer::WriteLine(const std::string& line) {
  output_ << line << std::endl;
}

}  // namespace metrics