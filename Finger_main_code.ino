/*
  MIT License

  Copyright (c) 2023 Hanlin Wang
  Copyright (c) 2023 Jason Wu Kai Chan

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.

  //////////////////////////////////////////////////////////////////////////////

  Copyright (c) 2013 seeed technology inc.

  The following code uses a library created for the MMA7660 accelerometer, which 
  is under the MIT License. This code therefore is also licensed under the terms
  of the MIT License
*/

#include <ezButton.h>
#include <Wire.h>
#include "MMA7660.h"
MMA7660 accelemeter;

// Stepper Motor pins
const int STEPPER_PIN_1 = 9;
const int STEPPER_PIN_2 = 10;
const int STEPPER_PIN_3 = 11;
const int STEPPER_PIN_4 = 12;
// Push Button pin
const int PUSH_PIN_1 = 3;
// Stepping Motor Variables
const int TURN_RATE = 600;
int step_num = 0;
int counter = 7000;
bool direction = true; // false = clockwise
bool turn = false;
// Push-button Variables
int pushState = 0;
// Accelerometer Variables
float angleRadT, angleDegT, anglePreT, angleRadS, angleDegS, anglePreS, angleMovR, angleMovD; // Rad for radian, Deg for degree, Pre to store the previously recorded angle, Mov for total angle of movement
float axPre, ayPre, azPre;

void setup() {
  // This delay fixes an issue where equipments won't initialise properly
  delay(1000);
  // put your setup code here, to run once:
  Serial.begin(9600);
  // Pin initialisation
  pinMode(STEPPER_PIN_1, OUTPUT);
  pinMode(STEPPER_PIN_2, OUTPUT);
  pinMode(STEPPER_PIN_3, OUTPUT);
  pinMode(STEPPER_PIN_4, OUTPUT);
  // Accelerometer initialisation
  accelemeter.init();
  // Push button pin initialisation
  pinMode(PUSH_PIN_1, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  pushState = digitalRead(PUSH_PIN_1);

  float ax, ay, az, a, b, c;
  accelemeter.getAcceleration(&ax, &ay, &az);

  a = vectorLength(ax,ay,az);
  b = vectorLength(axPre, ayPre, azPre);
  c = vectorLength(ax-axPre,ay-ayPre,az-azPre);
  
  angleRadT = tiltAngle(ax, ay, az);
  angleRadS = sweepAngle(ax, ay, az);
  angleDegT = angleRadT*180/PI;
  angleDegS = angleRadS*180/PI;
  angleMovR = cosineRule(a,b,c);
  angleMovD = angleMovR*180/PI;

  // Detect button push for ON/OFF
  if(pushState == HIGH) {
    turn = !turn;
    Serial.println("pushed!");
  }

  // Rotation logic, depending if the thumb opens or closes
  if(turn == true) {
    if(angleMovD != 0) {
      counter=0;
    }

    if(angleDegT-anglePreT > 0) {
      direction = false;
      while(counter<TURN_RATE) { // 1000 = roughly half rotation
        Step(direction);
        delay(2);
        counter++;
      }
    }

    if(angleDegT-anglePreT < 0) {
      direction = true;
      while(counter < TURN_RATE) { // 1000 = roughly half rotation
        Step(direction);
        delay(2);
        counter++;
      }
    }
  }

  Serial.print("Tilt angle is: ");
  Serial.print(angleDegT);
  Serial.print(", Tilt angle difference is: ");
  Serial.println(angleDegT-anglePreT);
  Serial.println("*******************************************");

  anglePreT = angleDegT;
  anglePreS = angleDegS;
  axPre = ax;
  ayPre = ay;
  azPre = az;
  delay(3000); // This delay ensures data is only read and processed every 3 seconds, making it easier to use
}
