#include <Wire.h>
#include <ACROBOTIC_SSD1306.h>

//16chars x8 lines

void setup() {
  Wire.begin();  
  oled.init();                      // Initialze SSD1306 OLED display

  oled.clearDisplay();              // Clear screen
  pinMode(LED_BUILTIN, OUTPUT);  
}

int lNum=0;
void loop() {
            
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
}
