#ifndef POVDISPLAY_H
#define POVDISPLAY_H

#include "motor.h"
#include "led.h"

class PovDisplay {
  private:
    uint8_t *display_buffer; // buffer with column-wise data to display
    int buffer_len;          // length of array
    int cycle_led_on;        // led stays on for x cycles
    int cycle_led_off;       // led stays off afterwards, until next column
    int cycle_wait_after;   // after the whole array was displayed wait for x cycles
    int tmp = 0; //ToDo remove

    int last_cb_pos = 0;         // position when the last callback occured
    uint8_t last_displayed;
    
    int last_pos_start = -1; // last position when display was called
    int second_col_start = 32000;
    int col_gap;
    int cur_arr_index = 0;       // current index in the display buffer
    int second_index = 0;
    bool running = false;        // display cycle is running; when it's false the 'display' function returns and the callback does nothing

  public:
    PovDisplay(int led_on = 5, int led_off = 10, int gap = 8);  // Constructor
    void display(int arr_len, int wait_after, uint8_t *arr);  // Initialize write cycle
    void next_step(int pos);  // callback for single steps from the stepper driver
};

PovDisplay::PovDisplay(int led_on, int led_off, int gap) {
  cycle_led_on  = led_on;
  cycle_led_off = led_off;
  col_gap= gap;
  Motor::set_callback(std::bind(&PovDisplay::next_step, this, _1));
}




void PovDisplay::display(int arr_len, int wait_after, uint8_t *arr) {
  display_buffer = arr;
  cycle_wait_after = wait_after;
  last_displayed = 0;
  last_pos_start = -1;
  buffer_len = arr_len;
  running = true;
  while (running) {
    yield();
    // loop until running is set to false
  } 
}

//void PovDisplay::next_step(int pos) {
//  ESP.wdtFeed();
//  if (!running) { return; };
//  if (pos<last_cb_pos) { last_col_start=-1000; }
//  last_cb_pos = pos;
//  //Serial.println(cur_arr_index); Serial.print(pos); Serial.print("+"); Serial.println(last_col_start);
//  if (pos > last_col_start + cycle_led_on + cycle_led_off) {  // one LED on/off cycle is over ... time to switch the LEDs back on
//    last_col_start = pos;
//    second_col_start= pos +col_gap;
//    uint8_t h= *(display_buffer + cur_arr_index);
//    Serial.print(h,BIN);Serial.print("=="); Serial.println(h,HEX);
//    h=h & 0xAA;
//    showLEDs(h);
//    if (cur_arr_index++ >= buffer_len) {
//        running = false;
//    }
//    
//  } else if (pos > last_col_start + cycle_led_on) { // time to switch the LEDs off
//    showLEDs(0x00);
//  }
//}

void PovDisplay::next_step(int pos) {
  ESP.wdtFeed();
  if (!running) { return; };
  if (last_pos_start == -1) {
    last_pos_start = pos;
  }
  if (last_pos_start > pos) {  // wrap around
    last_pos_start -= 2048; 
  }
  int rel_pos = pos - last_pos_start;
  int columnwidth= cycle_led_on+ cycle_led_off;

  int array_index=  rel_pos / columnwidth;
  int sub_pos= rel_pos % columnwidth;
  uint8_t h=0;
  if ((sub_pos < cycle_led_on) && (array_index < buffer_len)) {
     h = *(display_buffer + array_index) & 0xAA;
  }
  //Serial.print("array_index: "); Serial.print(array_index); Serial.print(" / "); Serial.println(sub_pos);
  int array_index_2 = (rel_pos - col_gap) / columnwidth;
  int sub_pos_2 = (rel_pos - col_gap) % columnwidth;
  if ((sub_pos_2 < cycle_led_on) && (pos - col_gap >= 0) && (array_index_2 < buffer_len))  {
     h |= *(display_buffer + array_index_2) & 0x55;
  }

  if (last_displayed != h) {
    showLEDs(h);
    last_displayed = h;
    //Serial.print("h: "); Serial.print(h, BIN); Serial.print(" pos: "); Serial.println(pos);
  }
  if ((array_index >= buffer_len) && (array_index_2 >= buffer_len)) {
    running = false;
  }
}


#endif

