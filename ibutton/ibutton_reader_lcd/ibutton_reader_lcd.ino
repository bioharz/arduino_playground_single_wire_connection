#include <LiquidCrystal.h>
#include <OneWire.h>


OneWire  ds(12);
LiquidCrystal lcd(7,6,5,4,3,2);
byte addr[8];
String keyStatus="";


void setup(void) {
  Serial.begin(115200);
  lcd.begin(16,2);
}


void loop(void) {
  getKeyCode();
  lcd.clear();
  if(keyStatus=="ok"){
      byte i;
      for( i = 5; i >0; i--) {
           lcd.print(":");
           lcd.print(addr[i], HEX);           
      }
  }
  else if (keyStatus!="") { lcd.print(keyStatus);}
  
  delay(1000);
}


void getKeyCode(){
  byte present = 0;
  byte data[12];
  keyStatus="";
  
  if ( !ds.search(addr)) {
      ds.reset_search();
      return;
  }


  if ( OneWire::crc8( addr, 7) != addr[7]) {
      keyStatus="CRC invalid";
      return;
  }
  
  /*if ( addr[0] != 0x01) {
      keyStatus="not DS1990A";
      return;
  }*/
  keyStatus="ok";
  
  //ds.reset();
}
