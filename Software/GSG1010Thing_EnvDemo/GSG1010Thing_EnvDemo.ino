/*
  Sketch generated by the Arduino IoT Cloud Thing

  Arduino IoT Cloud Properties description

  The following variables are automatically generated and updated when changes are made to the Thing properties

  float illuminance;
  float humidity;
  bool ledOn;
  float temperature;

  Properties which are marked as READ/WRITE in the Cloud Thing will also have functions
  which are called when their values are changed from the Dashboard.
  These functions are generated with the Thing and added at the end of this sketch.
*/
#include <SPI.h>
#include <SD.h>
#include <WiFiNINA.h>
#include <utility/wifi_drv.h>
#include "thingProperties.h"
#include <Arduino_MKRENV.h>
#include <ArduinoLowPower.h>


#define LEDPIN 26
#define CSPIN 4


const char* FILENAME = "telemetr.csv";  // filename has MAXIMUM length of 8 characters, file extension has MAXIMUM length of three characters!

unsigned long lastWriteTime = 0;
unsigned long writeDelay = 60000;

File myFile;

void setup()
{
  Serial.begin(9600);
  while(!Serial) {
    ;
  }

  WiFiDrv::pinMode(LEDPIN, OUTPUT);
  WiFiDrv::digitalWrite(LEDPIN, LOW);


  Serial.print("Initializing SD card...");
  if (!SD.begin(CSPIN))
  {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");




  Serial.print("Initializing sensors...");
  if (!ENV.begin())
  {
    Serial.println("Failed to initialize MKR ENV shield!");
    while (1);
  }
  Serial.println("initialization done.");


  initProperties();
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
}

void loop()
{
  ArduinoCloud.update();
  Serial.print("T: ");
  Serial.println(temperature = ENV.readTemperature(FAHRENHEIT));
  Serial.print("H: ");
  Serial.println(humidity = ENV.readHumidity());
  //float pressure    = ENV.readPressure(PSI);
  Serial.print("I: ");
  Serial.println(illuminance = ENV.readIlluminance(FOOTCANDLE));


  noInterrupts();
  if ((millis() - lastWriteTime) > writeDelay) {
    myFile = SD.open(FILENAME, FILE_WRITE);
    if (myFile)
    {
      myFile.print(temperature);
      myFile.print(",");
      myFile.print(humidity);
      myFile.print(",");
      myFile.println(illuminance);
      myFile.close();
    }
    else {
      Serial.print("WARNING: Error opening file: ");
      Serial.println(FILENAME);
    }
    
    lastWriteTime = millis();
  }
  interrupts();
  
  
  LowPower.idle(5000);
}

void onLedOnChange()
{
  if (ledOn == true)
  {
    WiFiDrv::digitalWrite(LEDPIN, HIGH);
  }
  else
  {
    WiFiDrv::digitalWrite(LEDPIN, LOW);
  }
}
