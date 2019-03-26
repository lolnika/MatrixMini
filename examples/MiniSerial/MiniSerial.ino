#include "MatrixMini.h"
#include "utility/MiniSerial.h"
MatrixMini Mini;

#define RATE 10
unsigned long int myTimer = 0;
byte incomingByte;

void setup() {
  Mini.begin(); 
  Serial.begin(9600);
}

void loop() {
  if(millis() - myTimer > RATE){
    myTimer = millis();
    Send();
    Receive();    
  }
}

// Write Data to Serial
void Send(){
  // Mini onboard values
  sendMessage(BTN1, Mini.BTN1.get());
  sendMessage(BTN2, Mini.BTN2.get());
  sendMessage(D1_STATUS, Mini.D1.get());
  sendMessage(D2_STATUS, Mini.D2.get());
  sendMessage(D3_STATUS, Mini.D3.get());
  sendMessage(D4_STATUS, Mini.D4.get());
  sendMessage(A1_STATUS, map(Mini.ANG1.get(), 0, 1023, 0, 254));
  sendMessage(A2_STATUS, map(Mini.ANG2.get(), 0, 1023, 0, 254));
  sendMessage(A3_STATUS, map(Mini.ANG3.get(), 0, 1023, 0, 254));
  }

// Read data from Serial
void Receive(){
  while(Serial.available()>0){
        incomingByte = Serial.read();
        if(incomingByte!=START_SYSEX) continue;
        while(Serial.available()<2);
        byte field = Serial.read();
        byte value = Serial.read();

        // Compare field and apply value
       if(field== SYSTEM_RST);
        else if(field== M1_CONFIG) Mini.M1.set((int8_t)value);
        else if(field== M2_CONFIG) Mini.M2.set((int8_t)value);
        else if(field== RC1_ANGLE) Mini.RC1.set(value);
        else if(field== RC2_ANGLE) Mini.RC2.set(value);
        else if(field== RC3_ANGLE) Mini.RC3.set(value);
        else if(field== RC4_ANGLE) Mini.RC4.set(value);
        else if(field== LED1_HSV) Mini.LED1.setHSV(map(value, 0, 254, 0, 360), 1.0, 1.0);
        else if(field== LED2_HSV) Mini.LED2.setHSV(map(value, 0, 254, 0, 360), 1.0, 1.0);
        else if(field== BTN1) ;
        else if(field== BTN2) ;
        else if(field== D1_CONFIG) Mini.D1.set(value);
        else if(field== D2_STATUS) Mini.D2.set(value);
        else if(field== D3_CONFIG) Mini.D3.set(value);
        else if(field== D4_CONFIG) Mini.D4.set(value);
        else if(field== A1_STATUS) Mini.ANG1.set(map(value, 0, 254, 0, 1023));
        else if(field== A2_STATUS) Mini.ANG2.set(map(value, 0, 254, 0, 1023));
        else if(field== A3_STATUS) Mini.ANG3.set(map(value, 0, 254, 0, 1023));
        else ;
   }
}
