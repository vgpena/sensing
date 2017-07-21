#include <TimeLib.h>
#include <Wire.h>

#include <Bounce.h>
#include <Audio.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

const int ledPin = 13;

// GUItool: begin automatically generated code
AudioInputI2S            i2s2;           //xy=105,63
AudioAnalyzePeak         peak1;          //xy=278,108
AudioRecordQueue         queue1;         //xy=281,63
AudioPlaySdRaw           playRaw1;       //xy=302,157
AudioOutputI2S           i2s1;           //xy=470,120
AudioConnection          patchCord1(i2s2, 0, queue1, 0);
AudioConnection          patchCord2(i2s2, 0, peak1, 0);
AudioConnection          patchCord3(playRaw1, 0, i2s1, 0);
AudioConnection          patchCord4(playRaw1, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=265,212
// GUItool: end automatically generated code

const int myInput = AUDIO_INPUT_MIC;
bool ended = false;
int startTime = 0;
int recordingLengthSecs = 5 * 5;

// Use these with the Teensy Audio Shield
#define SDCARD_CS_PIN    10
#define SDCARD_MOSI_PIN  7
#define SDCARD_SCK_PIN   14

// The file where data is recorded
File frec;

void setup() {
  AudioMemory(60);
  Serial.begin(9600);
  
  pinMode(ledPin, OUTPUT);

  // Enable the audio shield, select input, and enable output
  sgtl5000_1.enable();
  sgtl5000_1.inputSelect(myInput);
  sgtl5000_1.volume(0.5);

  
  // Initialize the SD card
  SPI.setMOSI(SDCARD_MOSI_PIN);
  SPI.setSCK(SDCARD_SCK_PIN);
  if (!(SD.begin(SDCARD_CS_PIN))) {
    // stop here if no SD card, but print a message
    while (1) {
      Serial.println("Unable to access the SD card");
      delay(500);
    }
  }

  digitalWrite(ledPin, HIGH);

  startRecording();
}

void loop() {
  if (startTime == 0 && Serial.available()) {
    startTime = long(Serial.read()) - '0';
  }

  if (!frec) {
   return;
  }

  if (second() % recordingLengthSecs == 0) {
    stopRecording();
    startRecording();
  } else {
    continueRecording();
  }
}

void startRecording() {
  char fileName[12];
  snprintf(fileName, 13, "%s.RAW", String(startTime + second()).c_str());

  if (SD.exists(fileName)) {
    Serial.println(String(fileName) + " already exists. Deleting...");
    SD.remove(fileName);
  }

  Serial.println("creating file " + String(fileName));
  frec = SD.open(fileName, FILE_WRITE);

  if (frec) {
    queue1.begin();
  } else {
    Serial.println("File creation failed :(");
  }
}

void stopRecording() {
  queue1.end();
  while (queue1.available() > 0) {
    frec.write((byte*)queue1.readBuffer(), 256);
    queue1.freeBuffer();
  }
  frec.close();
  Serial.println("End recording");
}

void continueRecording() {
  if (queue1.available() >= 2) {
    byte buffer[512];
    memcpy(buffer, queue1.readBuffer(), 256);
    queue1.freeBuffer();
    memcpy(buffer+256, queue1.readBuffer(), 256);
    queue1.freeBuffer();
//    elapsedMicros usec = 0;
    frec.write(buffer, 512);
//    Serial.print("SD write, us=");
//    Serial.println(usec);
  }
}

