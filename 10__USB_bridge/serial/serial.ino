#include <HardwareSerial.h>

HardwareSerial tty(2); 

void setup(void) {
  Serial.begin(9600);  
  tty.begin(9600, SERIAL_8N1, 16, 17);
  Serial.println("Fun begins:");
}
  
    
void loop(void) {  
   if (tty.available()){
//       gps.encode(tty.read());
       Serial.write(tty.read());
    }
    
}
