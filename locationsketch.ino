// libraries
#include <MKRGSM.h>

#include "arduino_secrets.h"
// Please enter your sensitive data in the Secret tab or arduino_secrets.h
// PIN Number
const char PINNUMBER[]     = SECRET_PINNUMBER;
// APN data
const char GPRS_APN[]      = SECRET_GPRS_APN;
const char GPRS_LOGIN[]    = SECRET_GPRS_LOGIN;
const char GPRS_PASSWORD[] = SECRET_GPRS_PASSWORD;

// initialize the library instance
GSMLocation location;
GPRS gprs;
GSM gsmAccess;
float gsmLati = 0;//holds first reading
float gsmLongi = 0;//holds first reading
float gsmLati2 = 0;//holds second more accurate reading
float gsmLongi2 = 0;//holds second more accurate reading
int key = 0;

void setup() {
  // initialize serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  Serial.println("Starting GSM location.");
  // connection state
  bool connected = false;

  // After starting the modem with GSM.begin()
  // connect to the GPRS network with the APN, login and password
  while (!connected) {
    if ((gsmAccess.begin(PINNUMBER) == GSM_READY) &&
        (gprs.attachGPRS(GPRS_APN, GPRS_LOGIN, GPRS_PASSWORD) == GPRS_READY)) {
      connected = true;
    } else {
      Serial.println("Not connected");
      delay(1000);
    }
  }

  location.begin();
}

void loop() {
  
  while(gsmLati == 0)
  {
  if(location.available())//get first innacurate reading, will leave after first reading
  {
    Serial.println("FIRST ITERATION, STILL GETTING COORDINATES");
    //Serial.print("Location: ");
    gsmLati = location.latitude();
    //Serial.print(location.latitude(), 7);
    //Serial.print(", ");
    gsmLongi = location.longitude();
    //Serial.println(location.longitude(), 7);
    //Serial.print("Accuracy: +/- ");
    //Serial.print(location.accuracy());
    //Serial.println("m");
      if((gsmLati == 0) && (gsmLongi == 0))
        {
        Serial.println("The coordinates are still 0");        
        }

        if((gsmLati != 0) && (gsmLongi != 0))
          {
          Serial.println("Yay! Coordinates are not 0. They are:");
          Serial.println(gsmLati);
          Serial.println(gsmLongi);
          Serial.println("END LOOP");
          key = 1;
          gsmLati2 = gsmLati;
          gsmLongi2 = gsmLongi;       
          }
    
  }
  }

  if(key == 1)
  {
    while(gsmLati2 == gsmLati)
  {
  if(location.available())//get a more accurate reading
  {
    Serial.println("SECOND ITERATION, STILL GETTING COORDINATES");
    //Serial.print("Location: ");
    gsmLati2 = location.latitude();
    //Serial.print(location.latitude(), 7);
    //Serial.print(", ");
    gsmLongi2 = location.longitude();
    //Serial.println(location.longitude(), 7);
    //Serial.print("Accuracy: +/- ");
    //Serial.print(location.accuracy());
    //Serial.println("m");


        if((gsmLati != gsmLati2) && (gsmLongi != gsmLongi2))
          {
          Serial.println("Yay! Coordinates are more accurate. They are:");
          Serial.println(gsmLati2);
          Serial.println(gsmLongi2);
          Serial.println("END LOOP");
          key = 2;
          }
    
  }
  }

    
  }

}
  
