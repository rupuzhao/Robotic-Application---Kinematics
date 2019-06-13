
//float linearSpeed1 = (3.14 * PARAM_R1) / (PARAM_Y / 2);
//float linearSpeed2 = (3.14 * PARAM_R2) / (PARAM_Y / 2);
//float angularSpeed1 = mcounts[0] / 32 / (PARAM_Y / 2);          //angularSpeed=degree in radians/time
//float angularSpeed2 = mcounts[0] / 32 / (PARAM_Y / 2);          //degree in radius=rotation*2*3.14 

#include <Adafruit_RGBLCDShield.h>
#include "MyEncoders.h"
#include "MyServos.h"
#include "SShapeParams.h"

#define YELLOW 0x3
#define WAIT_INPUT 0
#define WAIT_MOVE1 1
#define WAIT_MOVE2 2
#define WAIT_SECOND 3
#define PAI 3.1415
 
Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();

float v = (PARAM_R1 * PAI + PARAM_R2 * PAI) / PARAM_Y;
float w1 = - v / PARAM_R1;
float w2 = v / PARAM_R2;


int state = WAIT_INPUT;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  lcd.begin(16, 2);
  lcd.setBacklight(0x3);
  lcd.setCursor(2,1);
  
  initEncoders();
  initServo();
//  calibrate();
  setSpeedsIPS(0,0);
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long mcounts[2];
  
  switch (state){
    case WAIT_INPUT: {
      uint8_t buttons = lcd.readButtons();
      
      if (buttons == BUTTON_SELECT){
        resetCounts();
        if (isPossibleVW(v, w1) && isPossibleVW(v, w2)){
       
        setSpeedsvw(v, w1);
        state = WAIT_MOVE1;
        }
        else{
         
        lcd.setCursor(1, 1);
        lcd.print("impossible");
        }
        //state = WAIT_MOVE1;
      }

      
      
      break;
    }
    case WAIT_MOVE1: {
      getCounts(mcounts);
      if (((((float)mcounts[0] / 32.0) * (2.61 * 3.14)) >= ((PARAM_R1 + 3.95/2) * PAI)) && ((((float)mcounts[1] / 32.0) * (2.61 * 3.14)) >= ((PARAM_R1 - 3.95/2) * PAI))){
        
        setSpeedsIPS(0, 0);
        state = WAIT_SECOND;
      }
     
      break;
    }

    case WAIT_SECOND: {
       uint8_t buttons = lcd.readButtons();
       
       if (buttons == BUTTON_SELECT){
           resetCounts();
           setSpeedsvw(v, w2);
           state = WAIT_MOVE2;
        }
    }

    case WAIT_MOVE2: {
      getCounts(mcounts);
      if (((((float)mcounts[0] / 32.0) * (2.61 * 3.14)) >= ((PARAM_R2 - 3.95/2) * PAI)) && ((((float)mcounts[1] / 32.0) * (2.61 * 3.14)) >= ((PARAM_R2 + 3.95/2) * PAI))) {
        setSpeedsIPS(0, 0);
        state = WAIT_INPUT;
    }
      
      break;
    }
 }

 delay(30);
}

//void loop() {
//  // put your main code here, to run repeatedly:
//  delay(1000);
//  lcd.setCursor(2,1);
//
//  if (buttons == BUTTON_SELECT){
//    getCounts(mcounts);
//    if ((linearSpeed1 <= (mcounts[0] / 32 * 3.14 * 2.61)) || (linearSpeed1 <= (mcounts[1] / 32 * 3.14 * 2.61))
//        || (linearSpeed2 <= (mcounts[0] / 32 * 3.14 * 2.61)) || (linearSpeed2 <= (mcounts[1] / 32 * 3.14 * 2.61))){         ////rotations = counts / 32
//          if ((((mcounts[0] / 32) * (2.61 * 3.14)) <= (3.14 * (PARAM_R1 + 3.95))) || (((mcounts[1] / 32) * (2.61 * 3.14)) <= (3.14 * (PARAM_R1 - 3.95)))){
//            setSpeedsvw(linearSpeed1, angularSpeed1);
//            }
//          else if (((((mcounts[0] / 32) * (2.61 * 3.14)) > (3.14 * (PARAM_R1 + 3.95))) || (((mcounts[1] / 32) * (2.61 * 3.14)) > (3.14 * (PARAM_R1 - 3.95))))){
//            setSpeeds(0, 0);
//            initEncoders();
//            if (((((mcounts[0] / 32) * (2.61 * 3.14)) <= (3.14 * (PARAM_R2 - 3.95))) || (((mcounts[1] / 32) * (2.61 * 3.14)) <= (3.14 * (PARAM_R2 + 3.95))))){
//              setSpeedsvw(linearSpeed1, angularSpeed2);
//              }
//            else {
//              setSpeeds(0, 0);
//              initEncoders();
//              }
//           }       
//       }
//     else {
//      lcd.print("Sorry I cannot working");
//      }
//   }
//}
