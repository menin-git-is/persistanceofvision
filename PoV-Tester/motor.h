#ifndef MOTOR_H
#define MOTOR_H
#include <functional>
using namespace std::placeholders;

namespace Motor {
  int get_steps_per_turn();
  void start_rotating();
  void stop_rotating();
  void set_speed(float rpm);
  void set_callback(std::function<void(int)> callback);
  void init();
}

#endif


