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
//      Serial.println(String(Serial.read()).c_str());
//      Serial.println(5);
      light(5);
      String data = Serial.readString();
//      char str[2];
//      str[0] = data;
//      str[1] = '\0';
      Serial.print(data);
//      Serial.println(Serial.read() - '0');
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

