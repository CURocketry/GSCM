//volatile int enableState;
volatile int posState;
volatile int negState;
volatile int clawState;

const int interrupt = 2;
const int pauseRead = 3;
const int pauseLED = 13;
const int enableMotor = 4;
const int enableClaw = 8;
const int motorPos = 6;
const int motorNeg = 7;
const int claw = 10;

void setup()
{
  pinMode(pauseLED, OUTPUT);     // Pin 13 is output to which an LED is connected
  digitalWrite(pauseLED, LOW);   // Make pin 13 low, switch LED off
  pinMode(interrupt, INPUT);	   // Pin 2 is input to which a switch is connected = INT0
  pinMode(pauseRead, INPUT);	   // Pin 3 is input to which a switch is connected = INT1
  pinMode(motorNeg, OUTPUT);
  pinMode(motorPos, OUTPUT);
  pinMode(enableMotor, OUTPUT);
  pinMode(enableClaw, OUTPUT);
  pinMode(claw,  OUTPUT);
  pinMode(9, OUTPUT);
  digitalWrite(9, LOW);
  digitalWrite(enableMotor, HIGH); //Enable the H-bridge
  digitalWrite(enableClaw, HIGH);
  attachInterrupt(0, pause, RISING);
}

void loop() {
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
}  


void pause(){  // Interrupt service routine
  halt();
  while(digitalRead(pauseRead) == HIGH){
    digitalWrite(pauseLED, HIGH);
    //Can't use delay in an ISR. Must use delayMircoseconds
    //but that can only take a number up to 16383, so iterate.
    for(int i = 0; i < 100; i++){
      delayMicroseconds(10000);
    }
    digitalWrite(pauseLED, LOW);
    for(int j = 0; j<100; j++){
      delayMicroseconds(10000);
    }
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
