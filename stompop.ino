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

#define DEBUG_ENABLED false
#define DEBUG_PRINT(a) //(Serial.print(a))
#define DEBUG_PRINTLN(a) //(Serial.println(a))

#define PIN_PIEZO A0
#define PIN_LED 8
#define PIN_BUTTON 7
#define PIN_SPEAKER 10

#define EEADDR 166
#define PIEZO_THRESHOLD 25
#define TAP_REQUIRED_COUNT 3 // How many times the threshold must be consecutivly reached ?
#define TAP_DELAY 80 // How much time should we wait until next tap ?
#define DEFAULT_VOLUME 2 // Must be 0 to 7
#define VOLUME_FILE "volumes.txt"

// Sound vars
int currentSound = 1;          // currently selected sound (the first one by default)
File soundFile;                // The current opened sound file

// Audio vars
TMRpcm audio;                  // Audio object

// Piezo sensor vars
int piezoValue = 0;            // Current piezo sensor value
int previousPiezoValue = 0;    // Previous piezo sensor value
int tapCounter = 0;            // Counter of continuous threshold detections
int* volumes = 0;
int volumesSize = 0;

void setup() {
  if (DEBUG_ENABLED) {
    setupSerial();
  }
  setupLed();
  setupButton();
  setupSDCardReader();
  setupAudioPlayer();
  loadVolumes();
  
  initSoundFile();  
}

void loop() {
  processPiezoSensor();
  checkButtonStatus();
}

// Setup methods
/////////////////////////////////

void setupSerial() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
}

void setupLed() {
  DEBUG_PRINT("Initializing LED...");
  pinMode(PIN_LED, OUTPUT); 
  digitalWrite(PIN_LED, LOW); // Led must be enlighted when power is on
  DEBUG_PRINTLN(" DONE.");
}

void setupButton() {
  DEBUG_PRINT("Initializing button...");
  pinMode(PIN_BUTTON,INPUT_PULLUP); // The internal pullup resistor is used to connect the button
  DEBUG_PRINTLN(" DONE.");
}

void setupSDCardReader() {
  DEBUG_PRINT("Initializing SD card...");
  if (!SD.begin(4)) {
    DEBUG_PRINTLN(" FAILED.");
    while (1);
  }
  DEBUG_PRINTLN(" DONE.");
}

void setupAudioPlayer() {
  DEBUG_PRINT("Initializing audio player...");
  audio.speakerPin = PIN_SPEAKER;
  DEBUG_PRINTLN(" DONE.");
}

void initSoundFile() {
  DEBUG_PRINT("Loading initial sound file...");
  EEPROM.get(EEADDR,currentSound); // Loading potentially existing sound number in EEPROM
   
  String filename = generateFilename();
  if (!SD.exists(filename)) {
    currentSound = 1;
    filename = generateFilename();
  }
  soundFile = SD.open(filename, FILE_READ);
  setVolume();
  DEBUG_PRINT(" DONE (now using sound '");
  DEBUG_PRINT(soundFile.name());
  DEBUG_PRINTLN("').");
}

void loadVolumes() {
  DEBUG_PRINT("Loading volumes...");
  String buffer;
  File volumeFile = SD.open(VOLUME_FILE, FILE_READ); // Opening the volume file
  if (volumeFile) {
    // First, calculate the number of lines to initialize the array later on
    volumesSize = 0;
    while (volumeFile.available()) {
      buffer = volumeFile.readStringUntil('\n');
      volumesSize++;      
    }
    volumeFile.close();
    
    // allocate size of volumes array
    volumes = (int*) malloc(volumesSize * sizeof(int));
    int counter = 0;
    volumeFile = SD.open(VOLUME_FILE, FILE_READ); // Opening the volume file
    if (volumeFile) {
      while (volumeFile.available() && counter < volumesSize) {
        buffer = volumeFile.readStringUntil('\n');
        volumes[counter] = buffer.toInt();
        if (volumes[counter] < 1 || volumes[counter] > 7) {
          volumes[counter] = DEFAULT_VOLUME;
        }
        counter++;      
      }
      volumeFile.close();
    }
  }
  DEBUG_PRINTLN(" DONE.");
  return volumes;
}

// Audio control methods
//////////////////////////

void processPiezoSensor() {
  // Reading current piezo value
  piezoValue = analogRead(PIN_PIEZO);

  // If the current value exceed the last value + threshold
  if (piezoValue >= (previousPiezoValue + PIEZO_THRESHOLD)) {
    // The counter of threshold exceeded must be incremented. To minimize false positives, the sound is played when the threshold value is consecutivly exceeded several times (defined by TAP_REQUIRED_COUNT) 
    tapCounter++;

    // If the threshold has been exceeded more than defined by TAP_REQUIRED_COUNT 
    if (tapCounter >= TAP_REQUIRED_COUNT) {
      audio.play(soundFile.name()); // Let's play the sound
      tapCounter = 0; // Set the counter back to 0
      DEBUG_PRINT("TAP ! "); 
      DEBUG_PRINTLN(piezoValue); 
      delay(TAP_DELAY); // Wait a bit for the signal to go down 
      previousPiezoValue = analogRead(PIN_PIEZO); // Get an actualized value of the piezo value for the next loop
    }
  } else {
    tapCounter = 0; // If the threshold is not reached, reset the counter
    previousPiezoValue = piezoValue; // Set the previous value for the next loop
  }
}

void changeSound() {
  audio.disable(); // First, let's disable the currently loaded sound file to prevent errors (sometimes it freezes).
  soundFile.close(); // Closing the file in order not to overload memory
  
  String filename;
  while (!soundFile) { // While the sound file is not successfully open (can be infinite loop if no valid SOUND001.wav file on SD card).
    currentSound++;
    filename = generateFilename();
    if (!SD.exists(filename)) {
      currentSound = 1;
      filename = generateFilename();
    }
    soundFile = SD.open(filename, FILE_READ);
  }
  setVolume();
  blinkLed();
  EEPROM.put(EEADDR,currentSound); // Save the current choice to EEPROM
  DEBUG_PRINT("Now using sound '");
  DEBUG_PRINT(soundFile.name());
  DEBUG_PRINTLN("'.");
}

void setVolume() {
  DEBUG_PRINT("Setting volume...");
  int volume = DEFAULT_VOLUME;
  if (currentSound <= volumesSize) {
    volume = volumes[currentSound-1];
  }
  audio.setVolume(volume);
  DEBUG_PRINT("Now using volume ");
  DEBUG_PRINT(volume);
  DEBUG_PRINTLN(" DONE.");
}


// IHM methods
//////////////////////////

void blinkLed() {
  digitalWrite(PIN_LED, HIGH); // Off
  delay(80);
  digitalWrite(PIN_LED, LOW); // On
  delay(80);
  digitalWrite(PIN_LED, HIGH); // Off
  delay(80);
  digitalWrite(PIN_LED, LOW); // On
}

void checkButtonStatus() {
  // If button is pressed
  if (digitalRead(PIN_BUTTON)==LOW) {
     changeSound();
     delay(500);
  } 
}

// Helpers
//////////////////////////

String generateFilename() {
  String filename = "SOUND";
  if (currentSound<100) filename += "0";
  if (currentSound<10) filename += "0";
  filename += currentSound;
  filename += ".wav"; 
  return filename;
}
