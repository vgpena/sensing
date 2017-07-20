const int ledPin = 13;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  //digitalWrite(ledPin, HIGH);
}


void loop() {
  //Serial.println('a');
  // put your main code here, to run repeatedly:
  if (Serial.available()) {
      //Serial.println("hi");
      light(Serial.read() - '0');
  }
//  
  delay(500);
}

void light(int numFlashes) {
//  Serial.println(numFlashes);
  for (int i = 0; i < numFlashes; i++) {
    //Serial.println(i);
    digitalWrite(ledPin, HIGH);
    delay(100);
    digitalWrite(ledPin, LOW);
    delay(100);
  }
}

