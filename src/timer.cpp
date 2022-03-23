#include "../include/timer.h"
#include <chrono>
#include <iostream>

using namespace std;

typedef chrono::high_resolution_clock Clock;

void Timer::start() { start_time = Clock::now(); }
void Timer::end() {
  chrono::duration duration =
      chrono::duration_cast<chrono::nanoseconds>(Clock::now() - start_time);
  double ms = duration.count() / 1e6;

  if (ms >= 1000) {
    cout << "Done in " << ms / 1e3 << " s" << endl;
  } else {
    cout << "Done in " << ms << " ms" << endl;
  }
}
