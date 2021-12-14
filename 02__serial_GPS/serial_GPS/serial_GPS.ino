#include <HardwareSerial.h>
#include <TinyGPS.h>

//hot start around 2 min

HardwareSerial tty(2); 
TinyGPS gps;

void setup(void) {
  Serial.begin(115200);  
  tty.begin(9600, SERIAL_8N1, 16, 17);
  Serial.println("Fun begins:");
}
  

    
void loop(void) {
float flat, flon;
unsigned long age, _date, _time, _age;  
  //if (tty.available()) Serial.write(tty.read());
   // while (tty.available() >0) {
   if (tty.available()){
       gps.encode(tty.read());
    }
    
    gps.f_get_position(&flat, &flon, &age);
    gps.get_datetime(&_date, &_time, &_age);
    Serial.print(flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, 6);Serial.print("N, ");  
    Serial.print(flon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon, 6);Serial.print("E, "); 
    Serial.print(gps.altitude()/100.0f);Serial.print(" meters"); // in cm originally 
    Serial.print(",  Date:"); Serial.print(_date);
    Serial.print(",  Time:"); Serial.print(_time);
    Serial.print(",  N of sats:");  Serial.println(gps.satellites() == TinyGPS::GPS_INVALID_SATELLITES ? 0 : gps.satellites());
    delay(1000);
}
