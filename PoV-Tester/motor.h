#ifndef MOTOR_H
#define MOTOR_H

typedef void (call_back)(int);

void startRotating();
void stopRotating();
void setCallback(call_back* callback);
void motor_setup();


#endif

