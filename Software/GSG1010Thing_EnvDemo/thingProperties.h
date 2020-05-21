#include <ArduinoIoTCloud.h>
#include <Arduino_ConnectionHandler.h>


const char THING_ID[] = MY_THING_ID;
const char SSID[]     = SECRET_SSID;    // Network SSID (name)
const char PASS[]     = SECRET_PASS;    // Network password (use for WPA, or use as key for WEP)

void onLedOnChange();

float illuminance;
float humidity;
bool ledOn;
float temperature;

void initProperties(){

  ArduinoCloud.setThingId(THING_ID);
  ArduinoCloud.addProperty(illuminance, READ, 5 * SECONDS, NULL);
  ArduinoCloud.addProperty(humidity, READ, 5 * SECONDS, NULL);
  ArduinoCloud.addProperty(ledOn, READWRITE, ON_CHANGE, onLedOnChange);
  ArduinoCloud.addProperty(temperature, READ, 5 * SECONDS, NULL);

}

WiFiConnectionHandler ArduinoIoTPreferredConnection(SSID, PASS);
