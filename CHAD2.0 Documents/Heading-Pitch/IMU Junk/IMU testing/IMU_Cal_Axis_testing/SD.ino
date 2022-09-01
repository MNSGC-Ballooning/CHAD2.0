#include <SD.h>
#define chipSelect BUILTIN_SDCARD

//SD global variables
File datalog;
File datalogIMU;
File sender; ///NEWNEWNEW
char filename[] = "sdcard00.csv";
char senderName[] = "SDCARD00.csv"; /// NEWNEWNEW
bool sdActive = false;
 
void sdSetup() {
  pinMode(chipSelect, OUTPUT);
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
   
  }
  else {
    Serial.println("Card initialized.\nCreating File...");
    for (byte i = 0; i < 100; i++) {
      filename[6] = '0' + i / 10;
      filename[7] = '0' + i % 10;
      if (!SD.exists(filename)) {
        datalog = SD.open(filename, FILE_WRITE);
        sdActive = true;
        Serial.println("Logging to: " + String(filename));
       
        delay(1000);
        break;
      }
    }
    if (!sdActive) {
      Serial.println("No available file names; clear SD card to enable logging");

      delay(5000);
    }
  }
}//end sd setup

void logData(String Data) {
  Serial.println("Data written");
  datalog = SD.open(filename, FILE_WRITE);
  datalog.println(Data);
  datalog.close();
  Serial.println(Data);
  Serial.println("Data written");
}
