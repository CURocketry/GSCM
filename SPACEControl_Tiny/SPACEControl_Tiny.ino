//volatile int enableState;
volatile int posState;
volatile int negState;
volatile int clawState;

const int interrupt = 8;
const int pauseLED = 0;
const int enableMotor = 10;
const int enableClaw = 5;
const int motorPos = 9;
const int motorNeg = 7;
const int claw = 3;
const int lowClaw = 4;

void setup()
{
  pinMode(pauseLED, OUTPUT);     // Pin 13 is output to which an LED is connected
  digitalWrite(pauseLED, LOW);   // Make pin 13 low, switch LED off
  pinMode(interrupt, INPUT);	   // Pin 2 is input to which a switch is connected = INT0
  pinMode(motorNeg, OUTPUT);
  pinMode(motorPos, OUTPUT);
  pinMode(enableMotor, OUTPUT);
  pinMode(enableClaw, OUTPUT);
  pinMode(claw,  OUTPUT);
  pinMode(lowClaw, OUTPUT);
  digitalWrite(lowClaw, LOW);
  digitalWrite(enableMotor, HIGH); //Enable the H-bridge
  digitalWrite(enableClaw, HIGH);
  digitalWrite(pauseLED, LOW);
  attachInterrupt(0, pause, RISING);
  delay(500); //Just a bit of startup time.
}

void loop() {
  if(digitalRead(interrupt) != HIGH){
    openClaw();
    still(5000);
    //Run forward
    forward(5000);
    closeClaw();
    still(5000);
    //Run backward
    backward(5000);
    openClaw();
    still(5000);
  }else{
    pause();
  }
}  


void pause(){  // Interrupt service routine
  halt();
  digitalWrite(pauseLED, HIGH);
  while(digitalRead(interrupt) == HIGH){
    
  }
  restart();
  digitalWrite(pauseLED, LOW);
}

void openClaw(){
  digitalWrite(claw, HIGH);
  clawState = HIGH;
}

void closeClaw(){
  digitalWrite(claw, LOW);
  clawState = LOW;
}

//Hold the motor still for "wait" milliseconds
void still(int wait){
  digitalWrite(motorPos, LOW);
  posState = LOW;
  digitalWrite(motorNeg, LOW);
  negState = LOW;
  delay(wait);
}

//Move motor forward for "wait" milliseconds
void forward(int wait){
  digitalWrite(motorPos, HIGH);
  posState = HIGH;
  digitalWrite(motorNeg, LOW);
  negState = LOW;
  delay(wait);
}

//Move motor backward for "wait" milliseconds
void backward(int wait){
  digitalWrite(motorPos, LOW);
  posState = LOW;
  digitalWrite(motorNeg, HIGH);
  negState = HIGH;
  delay(wait);
}

//Disable all motor functions
void halt(){
  digitalWrite(enableMotor, LOW);
  digitalWrite(motorPos, LOW);
  digitalWrite(motorNeg, LOW);
}

//Reenable motor functions, returning to previous state.
void restart(){
  digitalWrite(enableMotor, HIGH);
  digitalWrite(motorPos, posState);
  digitalWrite(motorNeg, negState);
}
