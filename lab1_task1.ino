#include "MyServos.h"
#include "MyEncoders.h"

#define TIMES 10000

unsigned long startTime = millis();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  initEncoders();
  initServo();
  //calibrate();
  
  setSpeeds(0, 100);
  delay(1000);

  
  
  
  

//  for (int i = 0; i <= 333; i ++){
//    getSpeeds(speeds);
//    Serial.print(speeds[0]);
//    Serial.print("\t");
//    Serial.println(speeds[1]);
//    delay(30);
//    }
//
//    setSpeeds(0, 0);
}



void loop() {
  // put your main code here, to run repeatedly:

    
    if ( millis() - startTime < TIMES ){
  
    float speeds[2];
    getSpeeds(speeds);
    Serial.println(speeds[1]);
    delay(30);
    }

    else{
      setSpeeds(0, 0);
      }
    

   // setSpeeds(0, 0);
}
