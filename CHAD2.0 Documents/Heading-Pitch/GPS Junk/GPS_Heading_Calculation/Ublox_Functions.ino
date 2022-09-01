//ublox setup function.
void ubloxSetup() {
  ubloxSerial.begin(UBLOX_BAUD);
  ublox.init();
  byte i = 0;
  while (i < 50) {
    i++;
    if (ublox.setAirborne()) {
      Serial.println("Air mode successfully set.");
      break;
    }
    if (i == 50) {
      Serial.println("Failed to set to air mode.");
      delay(3000);
    }
  }
  delay(1000);
}

//update the GPS so it has the most recent coordinates and save new values as the lat long coordinates
void updateUblox() {
  ublox.update();
  //Serial.println("Ublox Has Been Updates");
  //save the updated data
  ubloxLatitude = ublox.getLat();
  ubloxLongitude = ublox.getLon();
  ubloxAltitude = ublox.getAlt_feet();
}


void displayUbloxCoordinates() {
  Serial.println("Ublox Coordinates (LLA):\nLat:\tLon:\tAlt(f):");
  Serial.println(String(ubloxLatitude, 5) + "\t" + String(ubloxLongitude, 5) + "\t" + String(ubloxAltitude, 2));
}
