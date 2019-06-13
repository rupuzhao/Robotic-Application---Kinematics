#include <MyEncoders.h>
#include <MyServos.h>

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(10, INPUT_PULLUP);
  pinMode(11, INPUT_PULLUP);
  initEncoders();
  setSpeeds(0, 0);

  for (int i = -200; i <= 200; i = i + 10){
    setSpeeds(i, i);
    delay(3000);
    Serial.print(wheelSpeed[0]);
    Serial.print(wheelSpeed[1]);
    }
}

void loop() {
  // put your main code here, to run repeatedly:

}
