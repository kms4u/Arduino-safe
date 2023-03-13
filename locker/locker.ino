#include <SPI.h>
#include <Servo.h>
#include <Wire.h>
#include <MFRC522.h> // библиотека "RFID".
#define SS_PIN 10
#define RST_PIN 9
#include <Servo.h> 
const int BUTTON_PIN = 7;
int servoPin = 3;
Servo Servo1;
int angle = 90;
int lastButtonState;
int currentButtonState;
MFRC522 mfrc522(SS_PIN, RST_PIN);
unsigned long uidDec, uidDecTemp;
void setup() {
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  Servo1.attach(servoPin);
  pinMode(2,OUTPUT);
  pinMode(4,OUTPUT);
  digitalWrite(2, HIGH);
  digitalWrite(4, LOW);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  Servo1.write(angle);
  currentButtonState = digitalRead(BUTTON_PIN);
  
}

void loop() {
    lastButtonState    = currentButtonState;
  currentButtonState = digitalRead(BUTTON_PIN);
  delay(10);
  if(lastButtonState == HIGH && currentButtonState == LOW) {
    Serial.println("The button is pressed");
    if(angle == 180)
      angle = 90;
    Servo1.write(angle);
       digitalWrite(2, HIGH);
  digitalWrite(4, LOW); 
  }
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;}
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;}
  uidDec = 0;
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    uidDecTemp = mfrc522.uid.uidByte[i];
    uidDec = uidDec * 256 + uidDecTemp;
  }
if (uidDec == 3809434634){
    Serial.print("OK");
    angle=180;
    Servo1.write(180);
    digitalWrite(4, HIGH);
  digitalWrite(2, LOW); 
  }
}

  
