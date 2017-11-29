#include "motor.h"
#include "led.h"
#include "PovDisplay.h"
//#include <stdlib.h>

PovDisplay disp;

const int arr_size = 400;
uint8_t array[arr_size];

void setup() {
  delay(2000);
  Motor::init();
  initLEDs();
 // showLEDs(255);
 // for(int i = 0; i < test_arr_size; i++) {
 //   test_arr[i] = i % 255;
 // }
 // disp = PovDisplay();
 // disp.display(test_arr_size, 0, test_arr);
  Serial.begin(9600);
  while (!Serial) {}
}

int IntToBitColumn(int zahl);

void loop() {
  int an,aus,versatz,n;
  versatz=26;
  
  for( an=1; an<42; an++) {
    // Serial.print("an = "); Serial.println(an);
    Serial.println("next"); 
    n=IntToBitColumn(an); // n number of columns to display
    PovDisplay disp(3, 4, versatz);  // PovDisplay::PovDisplay(int led_on, int led_off)
    disp.display(n, 200, array);  // PovDisplay::display(int arr_len, int wait_after, uint8_t *arr) 
    // Display(n,200,an,aus,array);
  }
 
}

const uint8_t font [10] [8] = {
  { 0x3E, 0x7F, 0x71, 0x59, 0x4D, 0x7F, 0x3E, 0x00 }, // '0'
  { 0x40, 0x42, 0x7F, 0x7F, 0x40, 0x40, 0x00, 0x00 }, // '1'
  { 0x62, 0x73, 0x59, 0x49, 0x6F, 0x66, 0x00, 0x00 }, // '2'
  { 0x22, 0x63, 0x49, 0x49, 0x7F, 0x36, 0x00, 0x00 }, // '3'
  { 0x18, 0x1C, 0x16, 0x53, 0x7F, 0x7F, 0x50, 0x00 }, // '4'
  { 0x27, 0x67, 0x45, 0x45, 0x7D, 0x39, 0x00, 0x00 }, // '5'
  { 0x3C, 0x7E, 0x4B, 0x49, 0x79, 0x30, 0x00, 0x00 }, // '6'
  { 0x03, 0x03, 0x71, 0x79, 0x0F, 0x07, 0x00, 0x00 }, // '7'
  { 0x36, 0x7F, 0x49, 0x49, 0x7F, 0x36, 0x00, 0x00 }, // '8'
{ 0x06, 0x4F, 0x49, 0x69, 0x3F, 0x1E, 0x00, 0x00 } // '9'
};


int IntToBitColumn(int zahl) {
   int n;
   const int zwischenraum=3;
   int ziffern[5];
   int i=0;
   while (zahl>0) {
     ziffern[++i]= zahl % 10;
     zahl = zahl / 10;
   }
   n= (8+zwischenraum)*i;
   int ax=0; 
   for(int z=i; z>0; z--) {
    //Serial.print("ziffern "); Serial.print(z); Serial.print(" "); Serial.println(ziffern[z]);
    for(int col=0; col<8; col++ ) {
      array[ax++]= font [ziffern[z]][col];
    }
    //Serial.println(ax);
    for (int col=0; col<zwischenraum; col++) {
      array[ax++]= 0;
    }
   }
  
   return(n);
}


//


