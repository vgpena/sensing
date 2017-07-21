#include <TimeLib.h>
#include <Wire.h>
#include <DS1307RTC.h>

const int ledPin = 13;
//RTC_DS1307 rtc;

void setup() {
  Serial.begin(9600);
//  setSyncProvider(RTC.get);
  
  pinMode(ledPin, OUTPUT);

}
int START_TIME = 0;

unsigned long processSyncMessage() {
  unsigned long pctime = 0L;
//  const unsigned long DEFAULT_TIME = 1357041600; // Jan 1 2013 

//  if(Serial.find(TIME_HEADER)) {
//     pctime = Serial.parseInt();
//     return pctime;
////     if( pctime < DEFAULT_TIME) { // check the value is a valid time (greater than Jan 1 2013)
////       pctime = 0L; // return 0 to indicate that the time is not valid
////     }
//  }
  return pctime;
}


void loop() {
  if (Serial.available()) {
    light(5);
    START_TIME = int(Serial.read()) - '0';
    Serial.println(START_TIME);
    if (millis() % 1000 == 0) {
      START_TIME++;
    }
//    time_t time = data;
//    setTime(time);
//    Serial.println(now());
  }
//  
  delay(100);
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

