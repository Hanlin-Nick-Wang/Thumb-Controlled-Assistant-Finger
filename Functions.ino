void Step(bool direction) { // Function to control motor turn direction
  if(direction) { // Anticlockwise
    if(step_num==0) {
      digitalWrite(STEPPER_PIN_1, HIGH);
      digitalWrite(STEPPER_PIN_2, LOW);
      digitalWrite(STEPPER_PIN_3, LOW);
      digitalWrite(STEPPER_PIN_4, LOW);
    } else if(step_num==1) {
      digitalWrite(STEPPER_PIN_1, LOW);
      digitalWrite(STEPPER_PIN_2, HIGH);
      digitalWrite(STEPPER_PIN_3, LOW);
      digitalWrite(STEPPER_PIN_4, LOW);
    } else if(step_num==2) {
      digitalWrite(STEPPER_PIN_1, LOW);
      digitalWrite(STEPPER_PIN_2, LOW);
      digitalWrite(STEPPER_PIN_3, HIGH);
      digitalWrite(STEPPER_PIN_4, LOW);
    } else if(step_num==3) {
      digitalWrite(STEPPER_PIN_1, LOW);
      digitalWrite(STEPPER_PIN_2, LOW);
      digitalWrite(STEPPER_PIN_3, LOW);
      digitalWrite(STEPPER_PIN_4, HIGH);
    }
  } else { // Clockwise
    if(step_num==0) {
      digitalWrite(STEPPER_PIN_1, LOW);
      digitalWrite(STEPPER_PIN_2, LOW);
      digitalWrite(STEPPER_PIN_3, LOW);
      digitalWrite(STEPPER_PIN_4, HIGH);
    } else if(step_num==1) {
      digitalWrite(STEPPER_PIN_1, LOW);
      digitalWrite(STEPPER_PIN_2, LOW);
      digitalWrite(STEPPER_PIN_3, HIGH);
      digitalWrite(STEPPER_PIN_4, LOW);
    } else if(step_num==2) {
      digitalWrite(STEPPER_PIN_1, LOW);
      digitalWrite(STEPPER_PIN_2, HIGH);
      digitalWrite(STEPPER_PIN_3, LOW);
      digitalWrite(STEPPER_PIN_4, LOW);
    } else if(step_num==3) {
      digitalWrite(STEPPER_PIN_1, HIGH);
      digitalWrite(STEPPER_PIN_2, LOW);
      digitalWrite(STEPPER_PIN_3, LOW);
      digitalWrite(STEPPER_PIN_4, LOW);
    }
  }

  // Increment step_num
  if(step_num==3) {
    step_num = 0;
  } else {
    step_num++;
  }
}

void rotationLogic() { // Deeterermines rotation logic
  direction = !direction;
  //counter = 0;
}

float tiltAngle(float ax, float ay, float az) {
  return atan2(ax, sqrt(sq(ay)+sq(az)));
}

float sweepAngle(float ax, float ay, float az) {
  return atan2(ay, sqrt(sq(ax)+sq(az)));
}

float cosineRule(float a, float b, float c) {
  return acos((sq(a)+sq(b)-sq(c))/(2*a*b));
}

float vectorLength(float x, float y, float z) {
  return sqrt(sq(x)+sq(y)+sq(z));
}
