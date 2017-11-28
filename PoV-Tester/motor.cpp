#include "Arduino.h"
extern "C" {
#include "user_interface.h"
}
#include "motor.h"


#define A1 D1
#define A2 D2
#define B1 D4
#define B2 D3

static const float band_width = 125.5 * 3.14;
static uint32_t step_state = 0;
static os_timer_t myTimer;
static uint16_t step_pos = 0;
static boolean step_ccw = true;

static void do_step() {
  if (step_ccw) {
    step_state++;
    step_pos++;
  } else {
    step_state--;
    step_pos--;
  }
  step_state = step_state % 4;
 
  switch (step_state) {
    case 0:
      digitalWrite(A1, HIGH);
      digitalWrite(A2, LOW);
      digitalWrite(B1, HIGH);
      digitalWrite(B2, LOW);
      break;
    case 1:
      digitalWrite(A1, HIGH);
      digitalWrite(A2, LOW);
      digitalWrite(B1, LOW);
      digitalWrite(B2, HIGH);
      break;
    case 2:
      digitalWrite(A1, LOW);
      digitalWrite(A2, HIGH);
      digitalWrite(B1, LOW);
      digitalWrite(B2, HIGH);
      break;
    case 3:
      digitalWrite(A1, LOW);
      digitalWrite(A2, HIGH);
      digitalWrite(B1, HIGH);
      digitalWrite(B2, LOW);
      break;
  }
}

void emptyCallbackFunction(int pos) { };

call_back* callback_function = &emptyCallbackFunction;

void setCallback(call_back* callback) {
  callback_function = callback;
}

void timerCallback(void *pArg) {
  do_step();
  callback_function(step_pos);
}

void motor_setup() {
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(B1, OUTPUT);
  pinMode(B2, OUTPUT);
  //http://www.switchdoc.com/2015/10/iot-esp8266-timer-tutorial-arduino-ide/
  os_timer_setfn(&myTimer, timerCallback, NULL);
  os_timer_arm(&myTimer, 7, true);
}
