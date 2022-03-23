#include <chrono>

class Timer {
public:
  void start();
  void end();

private:
  std::chrono::high_resolution_clock::time_point start_time;
};
