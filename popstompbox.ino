 /*
  PopStompbox
  created July 2020
  by St4ckben

  Distributed under MIT License

*/

#include <pcmConfig.h>
#include <pcmRF.h>
#include <TMRpcm.h>
#include <SPI.h>
#include <SD.h>
#include <EEPROM.h>

#define EEADDR 166

const int PIEZO_PIN = A0; 

int currentSound = 1;
File soundFile;

TMRpcm audio;
int piezoADC = 0;
int threshold = 20;
int previousPiezoADC = 0;
int led = 8; 
int button = 7; 
int tapValidator = 0;

void setup() {
  // Led 
  pinMode(led, OUTPUT); 
  digitalWrite(led, LOW);

  // Button 
  pinMode(button,INPUT_PULLUP);
  
  /*// Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  Serial.print("Initializing SD card...");*/

  if (!SD.begin(4)) {
    //Serial.println("initialization failed!");
    while (1);
  }
  //Serial.println("initialization done.");

  initSoundFile();  
 
  audio.speakerPin = 10;
  audio.setVolume(2);

}

void loop() {

  piezoADC = analogRead(PIEZO_PIN);
  //Serial.println(piezoADC); 
  if (piezoADC >= (previousPiezoADC + threshold)) {
    tapValidator++;
    if (tapValidator >= 3) {
      tapValidator = 0;
      audio.play(soundFile.name());
      //Serial.print("TAP !"); 
      //Serial.println(piezoADC); 
      delay(80);
      previousPiezoADC = analogRead(PIEZO_PIN);
    }
  } else {
    tapValidator = 0;
    previousPiezoADC = piezoADC;
  }

  // If button is pressed
  if (digitalRead(button)==LOW) {
     changeSound();
     delay(500);
  } 
}

void changeSound() {
  audio.disable(); 
  soundFile.close();
  String filename;
  while (!soundFile) {
    currentSound++;
    filename = generateFilename();
    if (!SD.exists(filename)) {
      currentSound = 1;
      filename = generateFilename();
    }
    soundFile = SD.open(filename, FILE_READ);
  }
  blinkLed();
  EEPROM.put(EEADDR,currentSound);
  //Serial.print("Now using sound ");
  //Serial.println(soundFile.name());
}

void blinkLed() {
  digitalWrite(led, HIGH); // Eteinte
  delay(80);
  digitalWrite(led, LOW); // Allumée
  delay(80);
  digitalWrite(led, HIGH); // Eteinte
  delay(80);
  digitalWrite(led, LOW); // Allumée
}

void initSoundFile() {
  // Read EEPROM for stored sound value
   EEPROM.get(EEADDR,currentSound);
   
  String filename = generateFilename();
  if (!SD.exists(filename)) {
    currentSound = 1;
    filename = generateFilename();
  }
  soundFile = SD.open(filename, FILE_READ);
  //Serial.print("Now using sound ");
  //Serial.println(soundFile.name());
}

String generateFilename() {
  String filename = "SOUND";
  if (currentSound<100) filename += "0";
  if (currentSound<10) filename += "0";
  filename += currentSound;
  filename += ".wav"; 
  return filename;
}
