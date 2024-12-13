  //H-bridge
  const int controlPin1 = 2;
  const int controlPin2 = 3;
  const int enablePin = 9;

  //Pushbuttons
  const int directionSwitchPin = 4; //bottom button
  const int onOffSwitchStateSwitchPin = 5; //top button

  //Potentiometer
  const int potPin = A0;

  //State changes
  int onOffSwitchState = 0;
  int previousOnOffSwitchState = 0;
  int directionSwitchState = 0;
  int previousDirectionSwitchState = 0;

  //Motor state
  int motorEnabled = 0;
  int motorSpeed = 0;
  int motorDirection = 1;

void setup() {
  //Digital pins
  pinMode(directionSwitchPin, INPUT);
  pinMode(onOffSwitchStatePin, INPUT);

  pinMode(controlPin1, OUTPUT);
  pinMode(controlPin2, OUTPUT);
  pinMode(enablePin, OUTPUT);

  digitalWrite(enablePin, LOW); //motor speed set to low when starting

}

void loop() {
  // detect switch state
  onOffSswitchState = digitalRead(onOffSwitchStateSwitchPin);
  delay(1);
  directionSwitchState = digitalRead(directionSwitchPin);
  motorSpeed = analogRead(potPin)/4; //Control motor with potentiometer.
  //Maps 0-1023 range to 0-255 range required for PWM (Pulse Width Modulation) signal, allowing the range of the potentiometer to correspond with the motor's speed. 

  if(onOffSwitchState!=previousOnOffSwitchState){ //Checks if current state of the switch is different from last state (upper button pressed)
    if(onOffSwitchState==HIGH){
      motorEnabled = !motorEnabled; //updates state variable accordingly
    }
  }

  if (directionSwitchState!=previousDirectionSwitchState){ //lower button pressed
    if (directionSwitchState==HIGH){
      motorDirection = !motorDirection; //updates state variable accordingly
    }
  }

  if (motorDirection == 1){ //configures direction of the motor
    digitalWrite(controlPin1, HIGH);
    digitalWrite(controlPin2,LOW);
  } else {
    digitalWrite(controlPin1, LOW);
    digitalWrite(controlPin2, HIGH);
  }

  if (motorEnabled == 1){ //if motor is enabled, set speed of the motor
    analogWrite(enablePin, motorSpeed);
  } else {
    analogWrite(enablePin, 0);
  }
  //Save current state as previous before exiting loop
  previousDirectionSwitchState = directionSwitchState;
  previousOnOffSwitchState = onOffSwitchState;
}
