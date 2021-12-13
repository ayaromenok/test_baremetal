#include <HardwareSerial.h>
HardwareSerial nss(2);
   
void setup(void) {
  Serial.begin(115200);
  nss.begin(9600);
  Serial.println("Fun begins:");
}
void loop(void) {
  if (nss.available()) Serial.write(nss.read());
}
