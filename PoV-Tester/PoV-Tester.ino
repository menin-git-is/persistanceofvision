#include "motor.h"
#include "led.h"

void setup() {
  // put your setup code here, to run once:
  delay(2000);
  motor_setup();
  initLEDs();
}

int counter = 0;

void loop() {
  // put your main code here, to run repeatedly:
  delay(400);

  //showLEDs(0xff);
  //showLEDs(0xff ^ (1 << counter));
  showLEDs((1 << counter));
  // showLEDs((1 ));
  if(++counter >= 8)
    counter = 0;
  //change_step(true);
}



