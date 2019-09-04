/* AFE Firmware for smart home devices, Website: https://afe.smartnydom.pl/ */

#include "AFE-Sensor-BMP180.h"

AFESensorBMP180::AFESensorBMP180(){};

boolean AFESensorBMP180::begin(BMx80 *_configuration) {

  configuration = _configuration;

#ifdef DEBUG
  Serial << endl << "Sensor type: BMP180";
#endif
  if (configuration->i2cAddress != 0) {
#ifdef DEBUG
    Serial << endl << "Address: 0x" << _HEX(configuration->i2cAddress);
#endif
    return bme.begin(BMP085_ULTRAHIGHRES, configuration->i2cAddress);
  } else {
#ifdef DEBUG
    Serial << endl << "Error: Address not set";
#endif
    return false;
  }
}

boolean AFESensorBMP180::read() {
#ifdef DEBUG
  Serial << endl << "Sensor: BMP180";
#endif
  data.temperature = bme.readTemperature();
  data.pressure = bme.readPressure() / 100.0;

  return true;
}
