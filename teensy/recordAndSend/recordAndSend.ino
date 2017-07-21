//#include <Time.h>
//#include <TimeLib.h>

// Record sound as raw data to a SD card, and play it back.
//
// Requires the audio shield:
//   http://www.pjrc.com/store/teensy3_audio.html
//
// Three pushbuttons need to be connected:
//   Record Button: pin 0 to GND
//   Stop Button:   pin 1 to GND
//   Play Button:   pin 2 to GND
//
// This example code is in the public domain.

#include <Bounce.h>
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <TimeLib.h>

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
// Use these with the Teensy Audio Shield
#define SDCARD_CS_PIN    10
#define SDCARD_MOSI_PIN  7
#define SDCARD_SCK_PIN   14

// The file where data is recorded
File frec;

void setup() {
  AudioMemory(60);
  Serial.begin(9600);
//  Serial.println("hi");
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
//  } else {
//    delay(1000);
  }
  startRecording();
//  recordFile();
}

File file;
//
//void recordFile() {
//  file = SD.open("test.txt", FILE_WRITE);
//  if (file) {
//    Serial.println("writing");
//    file.println("En un lugar en La Mancha, de cuyo nombre no quiero acordarme, no ha mucho tiempo que vivía un hidalgo de los que lanza en astrillero, adarga antigua, rocín flaco y galgo corredor.");
//    file.close();
//    Serial.println("done");
//  } else {
//    Serial.println("error");
//  }
//
//  sendFile();
//}

void sendFile() {
//  file = SD.open("test.txt");
  frec = SD.open("0.RAW");
//  Serial.println(frec);
  if (frec) {
//    Serial.println("open");

    while(frec.available()) {
      Serial.write(frec.read());
    }
    Serial.write("_");
    frec.close();
//    Serial.println("done");
  } else {
    Serial.println("error");
  }
}

#define TIME_HEADER "T"
int loopNumber = 0;

void loop() {
//  Serial.println(now());
//  unsigned long myTime = 0L;
//  const unsigned long DEFAULT_TIME = 1357041600;

//  if (Serial.find(TIME_HEADER)) {
//    myTime = Serial.parseInt();
//    Serial.println(myTime);
//  }
  if (!frec) {
   return;
  }
  
  int time = millis();
  int length = 10 * 1000;

  if (time % length == 0) {
    stopRecording();
//    loopNumber++;
//    startRecording();
  } else {
    continueRecording();
  }
  
//  if (time < 10000) {
//    continueRecording();
//  } else if (ended == false) {
//    ended = true;
//    stopRecording();
//  }
}

void startRecording() {
//  Serial.println('a');
  char myfilename[12];
  snprintf(myfilename, 13, "%s.RAW", String(loopNumber).c_str());

  if (SD.exists("0.RAW")) {
    // The SD library writes new data to the end of the
    // file, so to start a new recording, the old file
    // must be deleted before new data is written.
    SD.remove("0.RAW");
  }
//  int num = random();
//  int num = Teensy3Clock.get();
//  int num = now();
//  Serial.println(String(num) + ".RAW");
//  Serial.println(month());
//  randomSeed(analogRead(13));
//  Serial.println(year());
//  const char *truncated = String(random()).substring(0, 8).c_str();
//  Serial.println(myfilename);
  frec = SD.open("0.RAW", FILE_WRITE);
//  Serial.println(frec);
  if (frec) {
    queue1.begin();
//    TODO: log file name, begin/end time
  } else {
    Serial.println("File creation failed :(");
  }
}

void continueRecording() {
  if (queue1.available() >= 2) {
    byte buffer[512];
    // Fetch 2 blocks from the audio library and copy
    // into a 512 byte buffer.  The Arduino SD library
    // is most efficient when full 512 byte sector size
    // writes are used.
    memcpy(buffer, queue1.readBuffer(), 256);
    queue1.freeBuffer();
    memcpy(buffer+256, queue1.readBuffer(), 256);
    queue1.freeBuffer();
    // write all 512 bytes to the SD card
//    elapsedMicros usec = 0;
    frec.write(buffer, 512);
    // Uncomment these lines to see how long SD writes
    // are taking.  A pair of audio blocks arrives every
    // 5802 microseconds, so hopefully most of the writes
    // take well under 5802 us.  Some will take more, as
    // the SD library also must write to the FAT tables
    // and the SD card controller manages media erase and
    // wear leveling.  The queue1 object can buffer
    // approximately 301700 us of audio, to allow time
    // for occasional high SD card latency, as long as
    // the average write time is under 5802 us.
//    Serial.print("SD write, us=");
//    Serial.println(usec);
  }
}

void stopRecording() {
//  Serial.println(String(random()) + ".RAW");
  queue1.end();
//  if (mode == 1) {
    while (queue1.available() > 0) {
      frec.write((byte*)queue1.readBuffer(), 256);
      queue1.freeBuffer();
    }
    frec.close();
//    Serial.println("End recording");
    sendFile();
//  }
//  mode = 0;
}

void adjustMicLevel() {
  // TODO: read the peak1 object and adjust sgtl5000_1.micGain()
  // if anyone gets this working, please submit a github pull request :-)
}

