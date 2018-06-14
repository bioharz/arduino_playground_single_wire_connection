//--------------------------------------------
// iButton Reader realtime for Arduino Nano328
// Developer: Badlo Sergey Grigoryevich
// H-page: <a href="http://raxp.radioliga.com" class="bb-url">http://raxp.radioliga.com</a>
//--------------------------------------------
 
 
#include <OneWire.h>
 
// 
identifiers of two keys iButton
byte key1[8] = {0x01, 0x5D, 0x90, 0x29, 0x10, 0x00, 0x00, 0x47}; // 01 5D 90 29 10 00 00 47
byte key2[8] = {0x01, 0x70, 0xC1, 0x0F, 0x10, 0x00, 0x00, 0x9A}; // 01 70 C1 0F 10 00 00 9A 
 
int pinNumber = 2;      // tighten to Vcc through R = 2.2 kOhm
OneWire ds(pinNumber);
 
void setup() {
 pinMode(3, OUTPUT);    // the anode of the first LED 
 pinMode(4, OUTPUT);    // cathode
 digitalWrite(3, LOW);  // enable - HIGH
 digitalWrite(4, LOW);
 
 pinMode(12, OUTPUT);   // anode of the second LED 
 pinMode(9, OUTPUT);    // cathode
 digitalWrite(12, LOW); // enable - HIGH
 digitalWrite(9, LOW);
 
 // подтяжка к плюсу 2-пина
 pinMode(pinNumber, INPUT);
 digitalWrite(pinNumber, HIGH);
 
 Serial.begin(9600);
}
 
void loop() {
  byte addr[8];
  byte val1 = 0;
  byte val2 = 0;
 
  delay(100);
  if (ds.search(addr)) { // if detected, the helmet identifier to the upper level
   Serial.print("#"); // package start
   for (int i=0; i<8; i++) {
       Serial.print(" "); // space separator
       Serial.print(addr[i], HEX);
 
       // 1-key (hardware identification, for example a master key)
       if (addr[i] == key1[i]) val1++;
       // 2-ключ
       if (addr[i] == key2[i]) val2++;
   }
   Serial.print("@"); // stop package
   Serial.println("");   
   ds.reset_search();
  }
 
  // indication on the first LED
  if (val1 == 8) {
     digitalWrite(3, HIGH);
     delay(500);
     digitalWrite(3, LOW);
  }
  // indication on the second LED
  if (val2 == 8) {
     digitalWrite(12, HIGH);
     delay(500);
     digitalWrite(12, LOW);
  }   
}
