const int enablePin = 4;
const int input1Pin = 3;
const int input2Pin = 2;
const int backward = 1;
const int pause = 0;

void setup(){
  pinMode(enablePin, OUTPUT);
  pinMode(input1Pin, OUTPUT);
  pinMode(input2Pin, OUTPUT);
  pinMode(backward, INPUT);
  pinMode(pause, INPUT);
}

void loop(){
  digitalWrite(enablePin, HIGH);
  if(digitalRead(pause) == LOW){
    if(digitalRead(backward) == HIGH){

      digitalWrite(input1Pin, HIGH);
      digitalWrite(input2Pin, LOW);
    }
    else{

      digitalWrite(input1Pin, LOW);
      digitalWrite(input2Pin, HIGH);

    }
  }
  else{
    digitalWrite(input1Pin, LOW);
    digitalWrite(input2Pin, LOW);
  }



}


