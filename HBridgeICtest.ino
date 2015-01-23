const int enablePin = 2;
const int input1Pin = 3;
const int input2Pin = 4;

void setup(){
  pinMode(enablePin, OUTPUT);
  pinMode(input1Pin, OUTPUT);
  pinMode(input2Pin, OUTPUT);
}

void loop(){
  delay(2000);
  digitalWrite(enablePin, HIGH);
  digitalWrite(input1Pin, HIGH);
  digitalWrite(input2Pin, LOW);
  delay(2000);
  digitalWrite(input1Pin, LOW);
  digitalWrite(input2Pin, HIGH);
  delay(2000);
  digitalWrite(enablePin, LOW);
  digitalWrite(input1Pin, LOW);
  digitalWrite(input2Pin, LOW);
}

