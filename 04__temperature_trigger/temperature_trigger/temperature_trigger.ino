//ESP8266 - Wemos D1 mini

int pinTemp   = 5;//D1
int value     = 0;

void setup() {
  Serial.begin(115200);
  pinMode(pinTemp, INPUT); 
}

void loop() {
  value = digitalRead(pinTemp);
  Serial.print("value: "); Serial.println(value);
  delay(1000);
}
