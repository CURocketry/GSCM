volatile int state1;
volatile int state2;
void setup()
{
  pinMode(13, OUTPUT);     // Pin 13 is output to which an LED is connected
  digitalWrite(13, LOW);   // Make pin 13 low, switch LED off
  pinMode(2, INPUT);	   // Pin 2 is input to which a switch is connected = INT0
  pinMode(3, INPUT);	   // Pin 3 is input to which a switch is connected = INT1
  pinMode(7, OUTPUT);
  pinMode(6, OUTPUT);
  attachInterrupt(0, blink1, RISING);
  //attachInterrupt(1, blink2, RISING);
}

void loop() {
  digitalWrite(7, HIGH);
  state1 = HIGH;
  digitalWrite(6, HIGH);
  state2 = HIGH;
  delay(5000);
  digitalWrite(6, LOW);
  state2 = LOW;
  delay(5000);
  digitalWrite(7, LOW);
  state1 = LOW;
  digitalWrite(6, HIGH);
  state2 = HIGH;
  delay(5000);
  digitalWrite(6, LOW);
  state2 = LOW;
  delay(5000);
}  


void blink1(){  // Interrupt service routine
  digitalWrite(7, LOW);
  digitalWrite(6, LOW);
  while(digitalRead(3) == HIGH){
    digitalWrite(13, HIGH);
  }
  digitalWrite(7, state1);
  digitalWrite(6, state2);
  digitalWrite(13, LOW);
}

void blink2(){              // Interrupt service routine
  digitalWrite(13, LOW);
}
