#include "thingProperties.h"

// Heltec ESP32 Dev-Boards - Version: Latest
// #include "ArduinoIoTCloudLPWAN.h"
// #include "WiFiNINA.h"
#include "WiFi.h"

#include "heltec.h"
#include "images.h"

// refs
// https://bit.ly/3Rn71sE

int MYLED = 13;

void writeLine(String str, bool writeToSerial = true);

void setup()
{
  serialInit();

  setupDisplay();

  cloudInit();

  pinMode(MYLED, OUTPUT);
}

void loop()
{
  ArduinoCloud.update();
  // Your code here
  random_value = random(0, 500);
  // Serial.print("random_value: ", random_value);
  // Serial.println("random_value: ", random_value);
  delay(500);

  // writeLine("---> random_value = " + String(random_value)); // write to serial
}

void onLedSwitchChange()
{
  // Do something
  if (led_switch)
  {
    digitalWrite(MYLED, HIGH);
  }
  else
  {
    digitalWrite(MYLED, LOW);
  }

  writeLine("---> led_switch = " + String(led_switch));
}

void setupDisplay()
{
  Heltec.begin(true /*DisplayEnable Enable*/, false /*LoRa Enable*/, true /*Serial Enable*/);

  logo();
  delay(1000);

  Heltec.display->clear();
}

void logo()
{
  Heltec.display->clear();
  Heltec.display->drawXbm(0, 5, logo_width, logo_height, (const unsigned char *)logo_bits);
  Heltec.display->display();
}

// Write a line to both serial out and OLED display:
void writeLine(String str, bool writeToSerial)
{
  if (writeToSerial)
  {
    Serial.println(str);
  }

  Heltec.display->clear();
  Heltec.display->drawString(10, 0, str);
  Heltec.display->display();
}

void serialInit()
{
  // // Initialize serial and wait for port to open:
  // https://bit.ly/3CI7m59
  Serial.begin(115200);
  // This delay gives the chance to wait for a Serial Monitor without blocking if none is found
  delay(1500);
}

void cloudInit()
{
  // !!! MUST BE CALLED BEFORE ANYTHING ELSE about cloud
  // Defined in thingProperties.h
  initProperties();

  // Connect to Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);

  /*
     The following function allows you to obtain more information
     related to the state of network and IoT Cloud connection and errors
     the higher number the more granular information you’ll get.
     The default is 0 (only errors).
     Maximum is 4
 */
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
}
