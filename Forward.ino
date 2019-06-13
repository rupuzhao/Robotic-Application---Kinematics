#include <Adafruit_RGBLCDShield.h>
#include "MyEncoders.h"
#include "MyServos.h"
#include "ForwardParams.h"

#define YELLOW 0x3

Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();
float realSpeed = PARAM_X / PARAM_Y;
float LSP = 6.0;
float RSP = 6.0;


#define WAIT_INPUT 0
#define WAIT_MOVE 1 
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
        if ((realSpeed <= LSP) && (realSpeed <= RSP)){
        setSpeedsIPS(LSP, RSP);
        }
        else{
        setSpeedsIPS(0, 0);  
        lcd.setCursor(1, 1);
        lcd.print("impossible");
        }
        state = WAIT_MOVE;
      }

      
      
      break;
    }
    case WAIT_MOVE: {
      getCounts(mcounts);
      lcd.setCursor(0, 0);
      lcd.print(mcounts[0]);
      lcd.print(" ");
      lcd.print(mcounts[1]);
      if (((((float)mcounts[0] / 32.0) * (2.61 * 3.14)) >= PARAM_X) || ((((float)mcounts[1] / 32.0) * (2.61 * 3.14)) >= PARAM_X)){
        setSpeedsIPS(0, 0);
        state = WAIT_INPUT;
      }
     
      break;
    }
 }

 delay(30);
}
  
  
  
  
  
//  lcd.setCursor(2,1);
//  uint8_t buttons = lcd.readButtons();
//  
//  if (buttons == BUTTON_SELECT){
//    getCounts(mcounts);
//    if ((realSpeed <= LSP) && (realSpeed <= RSP)){
//      
//      setSpeedsIPS(LSP, RSP);
//      
//      if ((((mcounts[0] / 32) * (2.61 * 3.14)) >= PARAM_X) || (((mcounts[1] / 32) * (2.61 * 3.14)) >= PARAM_X)){
//        setSpeeds(0, 0);
//        resetCounts();
//      }
//    }     
//    else{
//      setSpeeds(0, 0);
//      lcd.print("Sorry it is not working");
//      }
//  }
//}
