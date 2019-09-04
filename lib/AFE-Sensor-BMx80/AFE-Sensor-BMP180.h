/* AFE Firmware for smart home devices, Website: https://afe.smartnydom.pl/ */

#ifndef _AFE_Sensor_BMP180_h
#define _AFE_Sensor_BMP180_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include <AFE-BMx80-Sensor-Structure.h>
#include <Adafruit_BMP085.h>

#ifdef DEBUG
#include <Streaming.h>
#endif

class AFESensorBMP180 {

private:
  Adafruit_BMP085 bme;

public:
  BMx80 *configuration;
  BMx80_DATA data;

  /* Constructor: entry parameter is GPIO number where Sensor is connected to */
  AFESensorBMP180(BMx80 *);

  boolean begin();

  boolean read();

  BMx80_DATA get();
};

#endif
