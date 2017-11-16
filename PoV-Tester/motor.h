#ifndef MOTOR_H
#define MOTOR_H

#include "Arduino.h"
extern "C" {
#include "user_interface.h"
}

#define A1 D1
#define A2 D2
#define B1 D3
#define B2 D4

uint32_t step_state = 0;
os_timer_t myTimer;
uint16_t step_pos = 0;
boolean step_dir = true;
uint16_t steps_per_turn = 360;//64 * 5.625
uint32_t ms_per_turn = 30000;
uint32_t ms_per_step = 0;

void set_speed(uint32_t period) {
  period / steps_per_turn;
}

void timerCallback(void *pArg) {
  if (step_dir) {
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


void user_init(void) {
  //http://www.switchdoc.com/2015/10/iot-esp8266-timer-tutorial-arduino-ide/
  os_timer_setfn(&myTimer, timerCallback, NULL);
  //min value 4ms
  os_timer_arm(&myTimer, 7, true);
}

void motor_setup() {
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(B1, OUTPUT);
  pinMode(B2, OUTPUT);
  user_init();
}

#endif

