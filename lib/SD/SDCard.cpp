#include "SDCard.h" 

SDCard::SDCard(unsigned long* pFlightTime, Vector3D* pGyro, Vector3D* pAccel, Vector3D* pOrient) {
    while (!SD.begin(chipSelect)) {
        Serial.println(F("Searching for SD..."));
        delay(1000); 
    }
    this->pFlightTime = pFlightTime; 
    this->pGyro = pGyro; 
    this->pAccel = pAccel; 
    this->pOrient = pOrient; 
    
    if (SD.exists("datalog.CSV")) {
        SD.remove("datalog.CSV"); 
    }
    File dataFile = SD.open("datalog.CSV", FILE_WRITE); 
    
    dataFile.println(F("flightTime, gyrosX, gyrosY, gyrosZ, accelX, accelY, accelZ, orientX, orientY, orientZ")); 
    dataFile.close(); 
    
    Serial.println(F("SD Card found")); 
}

void SDCard::logData() {
    File dataFile = SD.open("datalog.CSV", FILE_WRITE); 

    if (dataFile) {
        dataFile.print(*pFlightTime); dataFile.print(",");
        dataFile.print(pGyro->x); dataFile.print(","); dataFile.print(pGyro->y); dataFile.print(","); dataFile.print(pGyro->z); dataFile.print(",");
        dataFile.print(pAccel->x); dataFile.print(","); dataFile.print(pAccel->y); dataFile.print(","); dataFile.print(pAccel->z); dataFile.print(",");
        dataFile.print(pOrient->x); dataFile.print(","); dataFile.print(pOrient->y); dataFile.print(","); dataFile.println(pOrient->z); 

        dataFile.close(); 
    } else {
        Serial.print(F("Could not write to datalog.csv |"));
    }
}

