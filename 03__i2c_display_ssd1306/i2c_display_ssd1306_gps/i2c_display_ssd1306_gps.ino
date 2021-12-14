#include <Wire.h>
#include <ACROBOTIC_SSD1306.h>
#include <HardwareSerial.h>
#include <TinyGPS.h>

//16chars x8 lines

HardwareSerial tty(2); 
TinyGPS gps;

void setup() {
  Wire.begin();  
  oled.init();                      // Initialze SSD1306 OLED display

  oled.clearDisplay();              // Clear screen
  pinMode(LED_BUILTIN, OUTPUT);  
  
  Serial.begin(115200);  
  tty.begin(9600, SERIAL_8N1, 16, 17);
}


int count=0;
int count_col=0;
float flat=0, flon=0;
float flat_old=0, flon_old=0;
unsigned long age, _date, _time, _age;  

void loop() {
/*            
  oled.putFloat(lNum,6);          
  oled.putString(" LED oN ");
  lNum++;
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  oled.putFloat(lNum,6);          
  oled.putString(" LED oFF");
  lNum++;
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000); 
  */
   
   if (tty.available()){
       gps.encode(tty.read());       
    }
    
    gps.f_get_position(&flat, &flon, &age);
    gps.get_datetime(&_date, &_time, &_age);

    if ((abs(flat-flat_old)>0.000001)|(abs(flon-flon_old)>0.000001)){
      
      flat_old=flat;
      flon_old=flon;

      oled.clearDisplay();
      oled.setTextXY(0,0);
      oled.putString("Sec: ");oled.putFloat(count,0); 
      oled.setTextXY(1,0);
      oled.putString("Sat: ");oled.putFloat(gps.satellites(),0); 
      oled.setTextXY(2,0);
      oled.putString("Lat: ");oled.putFloat(flat,6); 
      oled.setTextXY(3,0);
      oled.putString("Lon: ");oled.putFloat(flon,6); 
      oled.setTextXY(4,0);
      oled.putString("Alt: ");oled.putFloat(gps.altitude()/100.0f,0); // in cm originally 
      oled.setTextXY(5,0);
      oled.putString("Date: ");oled.putFloat(_date,0); 
      oled.setTextXY(6,0);
      oled.putString("Time: ");oled.putFloat(_time/100.f,0); //remove msec


      Serial.print(count);Serial.print("\t");
      Serial.print(flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, 6);Serial.print("N, ");  
      Serial.print(flon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon, 6);Serial.print("E, "); 
      Serial.print(gps.altitude()/100.0f);Serial.print(" meters"); // in cm originally 
      Serial.print(",  Date:"); Serial.print(_date);
      Serial.print(",  Time:"); Serial.print(_time/100.0f);//remove msec
      Serial.print(",  N of sats:");  Serial.print(gps.satellites() == TinyGPS::GPS_INVALID_SATELLITES ? 0 : gps.satellites());
      Serial.print(", age: "); Serial.print(age);
      Serial.print(", "); Serial.println(_age);
      count++;    
    } else {
      delay(100);
      if (count_col>=100){
        Serial.println('.');
        count_col = 0;
        } else {
        Serial.print('.');
      }
      count_col++;
    }   
}
