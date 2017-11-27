#ifndef LED_H
#define LED_H

#define LED_DATA   D8
#define LED_CLK    D6
#define LED_ENABLE D7
#define LED_LATCH  D0

void initLEDs() {
  pinMode(LED_DATA, OUTPUT);
  pinMode(LED_CLK, OUTPUT);
  pinMode(LED_ENABLE, OUTPUT);
  pinMode(LED_LATCH, OUTPUT);
  
  digitalWrite(LED_ENABLE, LOW);
}

void showLEDs(uint8_t data) {
  digitalWrite(LED_CLK, LOW);
  shiftOut(LED_DATA, LED_CLK, MSBFIRST, data);
  digitalWrite(LED_LATCH, HIGH);
  digitalWrite(LED_LATCH, LOW);
}

void setLEDIntensity(uint8_t intensity) {
  if(intensity){
    digitalWrite(LED_ENABLE, LOW);
  } else {
    digitalWrite(LED_ENABLE, HIGH);
  }
}

#endif
