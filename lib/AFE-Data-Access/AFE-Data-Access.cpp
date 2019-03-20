/* AFE Firmware for smart home devices
  LICENSE: https://github.com/tschaban/AFE-Firmware/blob/master/LICENSE
  DOC: http://smart-house.adrian.czabanowski.com/afe-firmware-pl/ */

#include "AFE-Data-Access.h"

AFEDataAccess::AFEDataAccess() {}

const String AFEDataAccess::getDeviceUID() {
  String uid;

#ifdef DEBUG
  Serial << endl
         << endl
         << "----------------- Reading File -------------------";
  Serial << endl << "Opening file: cfg-device-uid.json : ";
#endif

  File configFile = SPIFFS.open("cfg-device-uid.json", "r");

  if (configFile) {
#ifdef DEBUG
    Serial << "success" << endl << "Reading JSON : ";
#endif

    size_t size = configFile.size();
    std::unique_ptr<char[]> buf(new char[size]);
    configFile.readBytes(buf.get(), size);
    StaticJsonBuffer<30> jsonBuffer;
    JsonObject &root = jsonBuffer.parseObject(buf.get());
    if (root.success()) {
#ifdef DEBUG
      root.printTo(Serial);
#endif
      uid = root.get<char *>("uid");
#ifdef DEBUG
      Serial << endl
             << "success" << endl
             << "JSON Buffer size: " << jsonBuffer.size();
#endif
    }

#ifdef DEBUG
    else {
      Serial << "failure";
    }
#endif

    configFile.close();
  }

#ifdef DEBUG
  else {
    Serial << "failure";
  }
  Serial << endl << "--------------------------------------------------";
#endif
  return uid;
}
void AFEDataAccess::saveDeviceUID(const char *uid) {
#ifdef DEBUG
  Serial << endl
         << endl
         << "----------------- Writing File -------------------";
  Serial << endl << "Opening file: cfg-device-uid.json : ";
#endif

  File configFile = SPIFFS.open("cfg-device-uid.json", "w");

  if (configFile) {
#ifdef DEBUG
    Serial << "success" << endl << "Writing JSON : ";
#endif

    StaticJsonBuffer<30> jsonBuffer;
    JsonObject &root = jsonBuffer.createObject();
    root["uid"] = uid;
    root.printTo(configFile);

#ifdef DEBUG
    root.printTo(Serial);
#endif
    configFile.close();

#ifdef DEBUG
    Serial << endl
           << "success" << endl
           << "JSON Buffer size: " << jsonBuffer.size();
#endif

  }
#ifdef DEBUG
  else {
    Serial << endl << "failed to open file for writing";
  }
  Serial << endl << "--------------------------------------------------";
#endif
}

PASSWORD AFEDataAccess::getPasswordConfiguration() {
  PASSWORD configuration;

#ifdef DEBUG
  Serial << endl
         << endl
         << "----------------- Reading File -------------------";
  Serial << endl << "Opening file: cfg-password.json : ";
#endif

  File configFile = SPIFFS.open("cfg-password.json", "r");

  if (configFile) {
#ifdef DEBUG
    Serial << "success" << endl << "Reading JSON : ";
#endif

    size_t size = configFile.size();
    std::unique_ptr<char[]> buf(new char[size]);
    configFile.readBytes(buf.get(), size);
    StaticJsonBuffer<80> jsonBuffer;
    JsonObject &root = jsonBuffer.parseObject(buf.get());
    if (root.success()) {
#ifdef DEBUG
      root.printTo(Serial);
#endif
      configuration.protect = root.get<bool>("protect");
      sprintf(configuration.password, root["password"]);

#ifdef DEBUG
      Serial << endl
             << "success" << endl
             << "JSON Buffer size: " << jsonBuffer.size();
#endif
    }

#ifdef DEBUG
    else {
      Serial << "failure";
    }
#endif

    configFile.close();
  }

#ifdef DEBUG
  else {
    Serial << "failure";
  }
  Serial << endl << "--------------------------------------------------";
#endif
  return configuration;
}
void AFEDataAccess::saveConfiguration(PASSWORD configuration) {
#ifdef DEBUG
  Serial << endl
         << endl
         << "----------------- Writing File -------------------";
  Serial << endl << "Opening file: cfg-password.json : ";
#endif

  File configFile = SPIFFS.open("cfg-password.json", "w");

  if (configFile) {
#ifdef DEBUG
    Serial << "success" << endl << "Writing JSON : ";
#endif

    StaticJsonBuffer<80> jsonBuffer;
    JsonObject &root = jsonBuffer.createObject();
    root["protect"] = configuration.protect;
    root["password"] = configuration.password;
    root.printTo(configFile);

#ifdef DEBUG
    root.printTo(Serial);
#endif
    configFile.close();

#ifdef DEBUG
    Serial << endl
           << "success" << endl
           << "JSON Buffer size: " << jsonBuffer.size();
#endif

  }
#ifdef DEBUG
  else {
    Serial << endl << "failed to open file for writing";
  }
  Serial << endl << "--------------------------------------------------";
#endif
}

DEVICE AFEDataAccess::getDeviceConfiguration() {
  DEVICE configuration;
#ifdef DEBUG
  Serial << endl
         << endl
         << "----------------- Reading File -------------------";
  Serial << endl << "Opening file: cfg-device.json : ";
#endif

  File configFile = SPIFFS.open("cfg-device.json", "r");

  if (configFile) {
#ifdef DEBUG
    Serial << "success" << endl << "Reading JSON : ";
#endif

    size_t size = configFile.size();
    std::unique_ptr<char[]> buf(new char[size]);
    configFile.readBytes(buf.get(), size);
    StaticJsonBuffer<400> jsonBuffer;
    JsonObject &root = jsonBuffer.parseObject(buf.get());
    if (root.success()) {
#ifdef DEBUG
      root.printTo(Serial);
#endif
      sprintf(configuration.name, root["name"]);
      configuration.api.http = root["api"]["http"];
      configuration.api.mqtt = root["api"]["mqtt"];
      configuration.api.domoticz = root["api"]["domoticz"];

      for (uint8_t i = 0; i < sizeof(configuration.isLED); i++) {
        configuration.isLED[i] = root["led"][i];
      }

      for (uint8_t i = 0; i < sizeof(configuration.isSwitch); i++) {
        configuration.isSwitch[i] = root["switch"][i];
      }

      for (uint8_t i = 0; i < sizeof(configuration.isRelay); i++) {
        configuration.isRelay[i] = root["relay"][i];
      }

#ifdef CONFIG_HARDWARE_ADC_VCC
      configuration.isAnalogInput = root["isAnalogInput"] == 1 ? true : false;
#endif

#ifdef DEBUG
      Serial << endl
             << "success" << endl
             << "JSON Buffer size: " << jsonBuffer.size();
#endif
    }

#ifdef DEBUG
    else {
      Serial << "failure";
    }
#endif

    configFile.close();
  }

#ifdef DEBUG
  else {
    Serial << "failure";
  }
  Serial << endl << "--------------------------------------------------";
#endif

  return configuration;
  /*
   Eeprom.read(9, 16).toCharArray(configuration.name,
                                  sizeof(configuration.name));


   configuration.api.http = Eeprom.read(25);
   configuration.api.mqtt = Eeprom.read(228);
   configuration.api.domoticz = Eeprom.read(800);


 #if defined(T0_CONFIG)
   configuration.isLED[0] = Eeprom.read(366);
   configuration.isLED[1] = Eeprom.read(418);
   configuration.isSwitch[1] = Eeprom.read(402);
 #endif


 #if defined(T0_CONFIG) || defined(T0_SHELLY_1_CONFIG)
   configuration.isRelay[0] = Eeprom.read(369);
   configuration.isSwitch[0] = Eeprom.read(395);
 #endif


 #if defined(T1_CONFIG) || defined(T2_CONFIG) || defined(T3_CONFIG) || \
     defined(T4_CONFIG) || defined(T5_CONFIG) || defined(T6_CONFIG)

 #if defined(T1_CONFIG)
   uint8_t index = 77;
 #elif defined(T2_CONFIG)
   uint8_t index = 98;
 #elif defined(T3_CONFIG) || defined(T4_CONFIG) || defined(T5_CONFIG) || \
     defined(T6_CONFIG)
   uint8_t index = 3;
 #endif

   for (uint8_t i = 0; i < sizeof(configuration.isLED); i++) {
     configuration.isLED[i] = Eeprom.read(366 + i * index);
   }
 #endif


 #if defined(T1_CONFIG)
   index = 40;
   for (uint8_t i = 0; i < sizeof(configuration.isRelay); i++) {
     configuration.isRelay[i] = Eeprom.read(396 + i * index);
   }

   index = 7;
   for (uint8_t i = 0; i < sizeof(configuration.isSwitch); i++) {
     configuration.isSwitch[i] = Eeprom.read(382 + i * index);
   }
 #endif


 #if defined(T2_CONFIG)
   index = 0;
   for (uint8_t i = 0; i < sizeof(configuration.isRelay); i++) {
     configuration.isRelay[i] = Eeprom.read(404 + i * index);
   }

   index = 7;
   for (uint8_t i = 0; i < sizeof(configuration.isSwitch); i++) {
     configuration.isSwitch[i] = Eeprom.read(390 + i * index);
   }
 #endif


 #if defined(T3_CONFIG)
   index = 21;
   for (uint8_t i = 0; i < sizeof(configuration.isRelay); i++) {
     configuration.isRelay[i] = Eeprom.read(381 + i * index);
   }

   index = 7;
   for (uint8_t i = 0; i < sizeof(configuration.isSwitch); i++) {
     configuration.isSwitch[i] = Eeprom.read(470 + i * index);
   }

   index = 27;
   for (uint8_t i = 0; i < sizeof(configuration.isPIR); i++) {
     configuration.isPIR[i] = Eeprom.read(505 + i * index);
   }
 #endif


 #if defined(T4_CONFIG)
   index = 27;
   for (uint8_t i = 0; i < sizeof(configuration.isRelay); i++) {
     configuration.isRelay[i] = Eeprom.read(382 + i * index);
   }

   index = 8;
   for (uint8_t i = 0; i < sizeof(configuration.isSwitch); i++) {
     configuration.isSwitch[i] = Eeprom.read(490 + i * index);
   }
 #endif


 #if defined(T5_CONFIG)
   index = 8;

   configuration.isRelay[0] = true; // Relay must be present - hardcoded

   for (uint8_t i = 0; i < sizeof(configuration.isSwitch); i++) {
     configuration.isSwitch[i] = Eeprom.read(398 + i * index);
   }

   index = 24;
   for (uint8_t i = 0; i < sizeof(configuration.isContactron); i++) {
     configuration.isContactron[i] = Eeprom.read(414 + i * index);
   }
 #endif


 #if defined(T6_CONFIG)
   configuration.isRelay[0] = Eeprom.read(373);

   index = 8;
   for (uint8_t i = 0; i < sizeof(configuration.isSwitch); i++) {
     configuration.isSwitch[i] = Eeprom.read(395 + i * index);
   }

   configuration.isHPMA115S0 = Eeprom.read(413);
   configuration.isBMx80 = Eeprom.readUInt8(422);
   configuration.isBH1750 = Eeprom.read(429);

 #endif


 #if defined(T1_CONFIG) || defined(T2_CONFIG) || defined(T5_CONFIG)
 #if defined(T1_CONFIG)
   configuration.isDS18B20 = Eeprom.read(369);
 #elif defined(T2_CONFIG)
   configuration.isDHT = Eeprom.read(369);
 #else
   configuration.isDHT = Eeprom.read(376);
 #endif
 #endif
 */
}
void AFEDataAccess::saveConfiguration(DEVICE configuration) {

#ifdef DEBUG
  Serial << endl
         << endl
         << "----------------- Writing File -------------------";
  Serial << endl << "Opening file: cfg-device.json : ";
#endif

  File configFile = SPIFFS.open("cfg-device.json", "w");

  if (configFile) {
#ifdef DEBUG
    Serial << "success" << endl << "Writing JSON : ";
#endif

    StaticJsonBuffer<400> jsonBuffer;
    JsonObject &root = jsonBuffer.createObject();

    root["name"] = configuration.name;

    JsonObject &jsonAPI = root.createNestedObject("api");
    jsonAPI["http"] = configuration.api.http;
    jsonAPI["mqtt"] = configuration.api.mqtt;
    jsonAPI["domoticz"] = configuration.api.domoticz;

    JsonArray &jsonLED = root.createNestedArray("led");
    for (uint8_t i = 0; i < sizeof(configuration.isLED); i++) {
      jsonLED.add(configuration.isLED[i]);
    }

    JsonArray &jsonSwitch = root.createNestedArray("switch");
    for (uint8_t i = 0; i < sizeof(configuration.isSwitch); i++) {
      jsonSwitch.add(configuration.isSwitch[i]);
    }

    JsonArray &jsonRelay = root.createNestedArray("relay");
    for (uint8_t i = 0; i < sizeof(configuration.isRelay); i++) {
      jsonRelay.add(configuration.isRelay[i]);
    }

#ifdef CONFIG_HARDWARE_ADC_VCC
    root["isAnalogInput"] = configuration.isAnalogInput;
#endif

    root.printTo(configFile);

#ifdef DEBUG
    root.printTo(Serial);
#endif
    configFile.close();

#ifdef DEBUG
    Serial << endl
           << "success" << endl
           << "JSON Buffer size: " << jsonBuffer.size();
#endif

  }
#ifdef DEBUG
  else {
    Serial << endl << "failed to open file for writing";
  }
  Serial << endl << "--------------------------------------------------";
#endif

  /*
    uint8_t index;
    Eeprom.write(9, 16, configuration.name);

  #if defined(T3_CONFIG)
    index = 21;
  #elif defined(T4_CONFIG)
    index = 27;
  #endif

    for (uint8_t i = 0; i < sizeof(configuration.isRelay); i++) {
  #if defined(T0_CONFIG) || defined(T0_SHELLY_1_CONFIG) || defined(T5_CONFIG)
      Eeprom.write(369, configuration.isRelay[i]);
  #elif defined(T1_CONFIG)
      Eeprom.write(396, configuration.isRelay[i]);
  #elif defined(T2_CONFIG)
      Eeprom.write(404, configuration.isRelay[i]);
  #elif defined(T3_CONFIG)
      Eeprom.write(381 + i * index, configuration.isRelay[i]);
  #elif defined(T4_CONFIG)
      Eeprom.write(382 + i * index, configuration.isRelay[i]);
  #elif defined(T6_CONFIG)
      Eeprom.write(373, configuration.isRelay[i]);
  #endif
    }

  #if defined(T0_CONFIG) || defined(T0_SHELLY_1_CONFIG) || defined(T1_CONFIG)
|| \ defined(T2_CONFIG) || defined(T3_CONFIG) index = 7; #elif
defined(T4_CONFIG)
  || defined(T5_CONFIG) || defined(T6_CONFIG) index = 8; #endif

    for (uint8_t i = 0; i < sizeof(configuration.isSwitch); i++) {
  #if defined(T0_CONFIG) || defined(T0_SHELLY_1_CONFIG) || defined(T6_CONFIG)
      Eeprom.write(395 + i * index, configuration.isSwitch[i]);
  #elif defined(T1_CONFIG)
      Eeprom.write(382 + i * index, configuration.isSwitch[i]);
  #elif defined(T2_CONFIG)
      Eeprom.write(390 + i * index, configuration.isSwitch[i]);
  #elif defined(T3_CONFIG)
      Eeprom.write(470 + i * index, configuration.isSwitch[i]);
  #elif defined(T4_CONFIG)
      Eeprom.write(490 + i * index, configuration.isSwitch[i]);
  #elif defined(T5_CONFIG)
      Eeprom.write(398 + i * index, configuration.isSwitch[i]);
  #endif
    }

  #ifdef CONFIG_HARDWARE_LED

  #if defined(T0_CONFIG)
    index = 52;
  #elif defined(T1_CONFIG)
    index = 77;
  #elif defined(T2_CONFIG)
    index = 98;
  #elif defined(T3_CONFIG) || defined(T4_CONFIG) || defined(T5_CONFIG) || \
      defined(T6_CONFIG)
    index = 3;
  #endif

    for (uint8_t i = 0; i < sizeof(configuration.isLED); i++) {
      Eeprom.write(366 + i * index, configuration.isLED[i]);
    }
  #endif

    saveAPI(API_MQTT, configuration.api.mqtt);
    saveAPI(API_HTTP, configuration.api.http);
    saveAPI(API_DOMOTICZ, configuration.api.domoticz);


  #if defined(T1_CONFIG) || defined(T2_CONFIG) || defined(T5_CONFIG)
  #if defined(T1_CONFIG)
    Eeprom.write(369, configuration.isDS18B20);
  #elif defined(T2_CONFIG)
    Eeprom.write(369, configuration.isDHT);
  #else

    Eeprom.write(376, configuration.isDHT);
    index = 24;
    for (uint8_t i = 0; i < sizeof(configuration.isContactron); i++) {
      Eeprom.write(414 + i * index, configuration.isContactron[i]);
    }
  #endif
  #endif

  #if defined(T3_CONFIG)
    index = 27;
    for (uint8_t i = 0; i < sizeof(configuration.isPIR); i++) {
      Eeprom.write(505 + i * index, configuration.isPIR[i]);
    }
  #endif

  #if defined(T6_CONFIG)
    Eeprom.write(413, configuration.isHPMA115S0);
    Eeprom.writeUInt8(422, configuration.isBMx80);
    Eeprom.write(429, configuration.isBH1750);
  #endif


  */
}

FIRMWARE AFEDataAccess::getFirmwareConfiguration() {
  FIRMWARE configuration;

#ifdef DEBUG
  Serial << endl
         << endl
         << "----------------- Reading File -------------------";
  Serial << endl << "Opening file: cfg-firmware.json : ";
#endif

  File configFile = SPIFFS.open("cfg-firmware.json", "r");

  if (configFile) {
#ifdef DEBUG
    Serial << "success" << endl << "Reading JSON : ";
#endif

    size_t size = configFile.size();
    std::unique_ptr<char[]> buf(new char[size]);
    configFile.readBytes(buf.get(), size);
    StaticJsonBuffer<100> jsonBuffer;
    JsonObject &root = jsonBuffer.parseObject(buf.get());
    if (root.success()) {
#ifdef DEBUG
      root.printTo(Serial);
#endif
      configuration.type = root["type"];
      sprintf(configuration.version, root["version"]);
      sprintf(configuration.upgradeURL, root["upgradeURL"]);
      configuration.autoUpgrade = root["autoUpgrade"];

#ifdef DEBUG
      Serial << endl
             << "success" << endl
             << "JSON Buffer size: " << jsonBuffer.size();
#endif
    }

#ifdef DEBUG
    else {
      Serial << "failure";
    }
#endif

    configFile.close();
  }

#ifdef DEBUG
  else {
    Serial << "failure";
  }
  Serial << endl << "--------------------------------------------------";
#endif

  return configuration;
}
void AFEDataAccess::saveConfiguration(FIRMWARE configuration) {
#ifdef DEBUG
  Serial << endl
         << endl
         << "----------------- Writing File -------------------";
  Serial << endl << "Opening file: cfg-firmware.json : ";
#endif

  File configFile = SPIFFS.open("cfg-firmware.json", "w");

  if (configFile) {
#ifdef DEBUG
    Serial << "success" << endl << "Writing JSON : ";
#endif

    StaticJsonBuffer<100> jsonBuffer;
    JsonObject &root = jsonBuffer.createObject();

    root["type"] = configuration.type;
    root["version"] = configuration.version;
    root["autoUpgrade"] = configuration.autoUpgrade;
    root["upgradeURL"] = configuration.upgradeURL;
    root.printTo(configFile);
#ifdef DEBUG
    root.printTo(Serial);
#endif
    configFile.close();

#ifdef DEBUG
    Serial << endl
           << "success" << endl
           << "JSON Buffer size: " << jsonBuffer.size();
#endif

  }
#ifdef DEBUG
  else {
    Serial << endl << "failed to open file for writing";
  }
  Serial << endl << "--------------------------------------------------";
#endif
}

NETWORK AFEDataAccess::getNetworkConfiguration() {
  NETWORK configuration;

#ifdef DEBUG
  Serial << endl
         << endl
         << "----------------- Reading File -------------------";
  Serial << endl << "Opening file: cfg-network.json : ";
#endif

  File configFile = SPIFFS.open("cfg-network.json", "r");

  if (configFile) {
#ifdef DEBUG
    Serial << "success" << endl << "Reading JSON : ";
#endif

    size_t size = configFile.size();
    std::unique_ptr<char[]> buf(new char[size]);
    configFile.readBytes(buf.get(), size);
    StaticJsonBuffer<300> jsonBuffer;
    JsonObject &root = jsonBuffer.parseObject(buf.get());
    if (root.success()) {
#ifdef DEBUG
      root.printTo(Serial);
#endif

      sprintf(configuration.ssid, root["ssid"]);
      sprintf(configuration.password, root["password"]);

      configuration.isDHCP = root["isDHCP"];

      configuration.ip = IPfromString(root["ip"]);
      configuration.gateway = IPfromString(root["gateway"]);
      configuration.subnet = IPfromString(root["subnet"]);

      configuration.noConnectionAttempts = root["noConnectionAttempts"];
      configuration.waitTimeConnections = root["waitTimeConnections"];
      configuration.waitTimeSeries = root["waitTimeSeries"];

#ifdef DEBUG
      Serial << endl
             << "success" << endl
             << "JSON Buffer size: " << jsonBuffer.size();
#endif
    }

#ifdef DEBUG
    else {
      Serial << "failure";
    }
#endif

    configFile.close();
  }

#ifdef DEBUG
  else {
    Serial << "failure";
  }
  Serial << endl << "--------------------------------------------------";
#endif

  return configuration;
}
void AFEDataAccess::saveConfiguration(NETWORK configuration) {
#ifdef DEBUG
  Serial << endl
         << endl
         << "----------------- Writing File -------------------";
  Serial << endl << "Opening file: cfg-network.json : ";
#endif

  File configFile = SPIFFS.open("cfg-network.json", "w");

  if (configFile) {
#ifdef DEBUG
    Serial << "success" << endl << "Writing JSON : ";
#endif

    StaticJsonBuffer<300> jsonBuffer;
    JsonObject &root = jsonBuffer.createObject();

    root["ssid"] = configuration.ssid;
    root["password"] = configuration.password;
    root["isDHCP"] = configuration.isDHCP;
    root["ip"] = configuration.ip.toString();
    root["gateway"] = configuration.gateway.toString();
    root["subnet"] = configuration.subnet.toString();

    root["noConnectionAttempts"] = configuration.noConnectionAttempts;
    root["waitTimeConnections"] = configuration.waitTimeConnections;
    root["waitTimeSeries"] = configuration.waitTimeSeries;

    root.printTo(configFile);
#ifdef DEBUG
    root.printTo(Serial);
#endif
    configFile.close();

#ifdef DEBUG
    Serial << endl
           << "success" << endl
           << "JSON Buffer size: " << jsonBuffer.size();
#endif

  }
#ifdef DEBUG
  else {
    Serial << endl << "failed to open file for writing";
  }
  Serial << endl << "--------------------------------------------------";
#endif
}

MQTT AFEDataAccess::getMQTTConfiguration() {
  MQTT configuration;

#ifdef DEBUG
  Serial << endl
         << endl
         << "----------------- Reading File -------------------";
  Serial << endl << "Opening file: cfg-mqtt-broker.json : ";
#endif

  File configFile = SPIFFS.open("cfg-mqtt-broker.json", "r");

  if (configFile) {
#ifdef DEBUG
    Serial << "success" << endl << "Reading JSON : ";
#endif

    size_t size = configFile.size();
    std::unique_ptr<char[]> buf(new char[size]);
    configFile.readBytes(buf.get(), size);
    StaticJsonBuffer<200> jsonBuffer;
    JsonObject &root = jsonBuffer.parseObject(buf.get());
    if (root.success()) {
#ifdef DEBUG
      root.printTo(Serial);
#endif

      sprintf(configuration.host, root["host"]);

      configuration.ip = IPfromString(root["ip"]);
      configuration.port = root["port"];
      sprintf(configuration.user, root["user"]);
      sprintf(configuration.password, root["password"]);
      sprintf(configuration.mqtt.topic, root["topic"]);

#ifdef DEBUG
      Serial << endl
             << "success" << endl
             << "JSON Buffer size: " << jsonBuffer.size();
#endif
    }

#ifdef DEBUG
    else {
      Serial << "failure";
    }
#endif

    configFile.close();
  }

#ifdef DEBUG
  else {
    Serial << "failure";
  }
  Serial << endl << "--------------------------------------------------";
#endif

  return configuration;
}
void AFEDataAccess::saveConfiguration(MQTT configuration) {
#ifdef DEBUG
  Serial << endl
         << endl
         << "----------------- Writing File -------------------";
  Serial << endl << "Opening file: cfg-mqtt-broker.json : ";
#endif

  File configFile = SPIFFS.open("cfg-mqtt-broker.json", "w");

  if (configFile) {
#ifdef DEBUG
    Serial << "success" << endl << "Writing JSON : ";
#endif

    StaticJsonBuffer<200> jsonBuffer;
    JsonObject &root = jsonBuffer.createObject();

    root["host"] = configuration.host;
    root["ip"] = configuration.ip.toString();
    root["port"] = configuration.port;
    root["user"] = configuration.user;
    root["password"] = configuration.password;
    root["topic"] = configuration.mqtt.topic;

    root.printTo(configFile);
#ifdef DEBUG
    root.printTo(Serial);
#endif
    configFile.close();

#ifdef DEBUG
    Serial << endl
           << "success" << endl
           << "JSON Buffer size: " << jsonBuffer.size();
#endif

  }
#ifdef DEBUG
  else {
    Serial << endl << "failed to open file for writing";
  }
  Serial << endl << "--------------------------------------------------";
#endif
}

DOMOTICZ AFEDataAccess::getDomoticzConfiguration() {
  DOMOTICZ configuration;
#ifdef DEBUG
  Serial << endl
         << endl
         << "----------------- Reading File -------------------";
  Serial << endl << "Opening file: cfg-domoticz-server.json : ";
#endif

  File configFile = SPIFFS.open("cfg-domoticz-server.json", "r");

  if (configFile) {
#ifdef DEBUG
    Serial << "success" << endl << "Reading JSON : ";
#endif

    size_t size = configFile.size();
    std::unique_ptr<char[]> buf(new char[size]);
    configFile.readBytes(buf.get(), size);
    StaticJsonBuffer<200> jsonBuffer;
    JsonObject &root = jsonBuffer.parseObject(buf.get());
    if (root.success()) {
#ifdef DEBUG
      root.printTo(Serial);
#endif

      configuration.protocol = root["protocol"];
      sprintf(configuration.host, root["host"]);
      configuration.port = root["port"];
      sprintf(configuration.user, root["user"]);
      sprintf(configuration.password, root["password"]);

#ifdef DEBUG
      Serial << endl
             << "success" << endl
             << "JSON Buffer size: " << jsonBuffer.size();
#endif
    }

#ifdef DEBUG
    else {
      Serial << "failure";
    }
#endif

    configFile.close();
  }

#ifdef DEBUG
  else {
    Serial << "failure";
  }
  Serial << endl << "--------------------------------------------------";
#endif
  return configuration;
}
void AFEDataAccess::saveConfiguration(DOMOTICZ configuration) {
#ifdef DEBUG
  Serial << endl
         << endl
         << "----------------- Writing File -------------------";
  Serial << endl << "Opening file: cfg-domoticz-server.json : ";
#endif

  File configFile = SPIFFS.open("cfg-domoticz-server.json", "w");

  if (configFile) {
#ifdef DEBUG
    Serial << "success" << endl << "Writing JSON : ";
#endif

    StaticJsonBuffer<200> jsonBuffer;
    JsonObject &root = jsonBuffer.createObject();

    root["protocol"] = configuration.protocol;
    root["host"] = configuration.host;
    root["port"] = configuration.port;
    root["user"] = configuration.user;
    root["password"] = configuration.password;
    root.printTo(configFile);
#ifdef DEBUG
    root.printTo(Serial);
#endif
    configFile.close();

#ifdef DEBUG
    Serial << endl
           << "success" << endl
           << "JSON Buffer size: " << jsonBuffer.size();
#endif

  }
#ifdef DEBUG
  else {
    Serial << endl << "failed to open file for writing";
  }
  Serial << endl << "--------------------------------------------------";
#endif
}

#ifdef CONFIG_HARDWARE_LED
LED AFEDataAccess::getLEDConfiguration(uint8_t id) {
  LED configuration;

  char fileName[15];
  sprintf(fileName, "cfg-led-%d.json", id);

#ifdef DEBUG
  Serial << endl
         << endl
         << "----------------- Reading File -------------------";
  Serial << endl << "Opening file: " << fileName << " : ";
#endif

  File configFile = SPIFFS.open(fileName, "r");

  if (configFile) {
#ifdef DEBUG
    Serial << "success" << endl << "Reading JSON : ";
#endif

    size_t size = configFile.size();
    std::unique_ptr<char[]> buf(new char[size]);
    configFile.readBytes(buf.get(), size);
    StaticJsonBuffer<50> jsonBuffer;
    JsonObject &root = jsonBuffer.parseObject(buf.get());
    if (root.success()) {
#ifdef DEBUG
      root.printTo(Serial);
#endif

      configuration.gpio = root.get<int>("gpio");
      configuration.changeToOppositeValue =
          root.get<bool>("changeToOppositeValue");

#ifdef DEBUG
      Serial << endl
             << "success" << endl
             << "JSON Buffer size: " << jsonBuffer.size();
#endif
    }

#ifdef DEBUG
    else {
      Serial << "failure";
    }
#endif

    configFile.close();
  }

#ifdef DEBUG
  else {
    Serial << "failure";
  }
  Serial << endl << "--------------------------------------------------";
#endif
  return configuration;
}
void AFEDataAccess::saveConfiguration(uint8_t id, LED configuration) {
  char fileName[15];
  sprintf(fileName, "cfg-led-%d.json", id);

#ifdef DEBUG
  Serial << endl
         << endl
         << "----------------- Writing File -------------------";
  Serial << endl << "Opening file: " << fileName << " : ";
#endif

  File configFile = SPIFFS.open(fileName, "w");

  if (configFile) {
#ifdef DEBUG
    Serial << "success" << endl << "Writing JSON : ";
#endif

    StaticJsonBuffer<50> jsonBuffer;
    JsonObject &root = jsonBuffer.createObject();
    root["gpio"] = configuration.gpio;
    root["changeToOppositeValue"] = configuration.changeToOppositeValue;
    root.printTo(configFile);
#ifdef DEBUG
    root.printTo(Serial);
#endif
    configFile.close();

#ifdef DEBUG
    Serial << endl
           << "success" << endl
           << "JSON Buffer size: " << jsonBuffer.size();
#endif

  }
#ifdef DEBUG
  else {
    Serial << endl << "failed to open file for writing";
  }
  Serial << endl << "--------------------------------------------------";
#endif
}
#endif

RELAY AFEDataAccess::getRelayConfiguration(uint8_t id) {
  RELAY configuration;
  char fileName[17];
  sprintf(fileName, "cfg-relay-%d.json", id);

#ifdef DEBUG
  Serial << endl
         << endl
         << "----------------- Reading File -------------------";
  Serial << endl << "Opening file: " << fileName << " : ";
#endif

  File configFile = SPIFFS.open(fileName, "r");

  if (configFile) {
#ifdef DEBUG
    Serial << "success" << endl << "Reading JSON : ";
#endif

    size_t size = configFile.size();
    std::unique_ptr<char[]> buf(new char[size]);
    configFile.readBytes(buf.get(), size);
    StaticJsonBuffer<200> jsonBuffer;
    JsonObject &root = jsonBuffer.parseObject(buf.get());
    if (root.success()) {
#ifdef DEBUG
      root.printTo(Serial);
#endif

      configuration.gpio = root.get<int>("gpio");
      sprintf(configuration.name, root.get<char *>("name"));
      configuration.timeToOff = root.get<float>("timeToOff");
      configuration.state.powerOn = root.get<float>("statePowerOn");
      configuration.state.MQTTConnected = root.get<int>("stateMQTTConnected");
      configuration.domoticz.idx = root.get<long>("idx");
      sprintf(configuration.mqtt.topic, root.get<char *>("MQTTTopic"));
      configuration.ledID = root.get<int>("ledID");

#ifdef DEBUG
      Serial << endl
             << "success" << endl
             << "JSON Buffer size: " << jsonBuffer.size();
#endif
    }

#ifdef DEBUG
    else {
      Serial << "failure";
    }
#endif

    configFile.close();
  }

#ifdef DEBUG
  else {
    Serial << "failure";
  }
  Serial << endl << "--------------------------------------------------";
#endif
  /*
  #if defined(T3_CONFIG)
    uint8_t nextRelay = 21;
  #elif defined(T4_CONFIG)
    uint8_t nextRelay = 27;
  #endif

  #if defined(T0_CONFIG) || defined(T0_SHELLY_1_CONFIG)
    configuration.gpio = Eeprom.readUInt8(370);
  #elif defined(T1_CONFIG)
    configuration.gpio = Eeprom.readUInt8(397);
  #elif defined(T2_CONFIG)
    configuration.gpio = Eeprom.readUInt8(405);
  #elif defined(T3_CONFIG)
    configuration.gpio = Eeprom.readUInt8(382 + id * nextRelay);
  #elif defined(T4_CONFIG)
    configuration.gpio = Eeprom.readUInt8(383 + id * nextRelay);
  #elif defined(T5_CONFIG)
    configuration.gpio = Eeprom.readUInt8(462);
  #elif defined(T6_CONFIG)
    configuration.gpio = Eeprom.readUInt8(374);
  #endif

  #if defined(T0_CONFIG) || defined(T0_SHELLY_1_CONFIG)
    configuration.timeToOff = Eeprom.read(372, 5).toFloat();
  #elif defined(T1_CONFIG)
    configuration.timeToOff = Eeprom.read(399, 5).toFloat();
  #elif defined(T2_CONFIG)
    configuration.timeToOff = Eeprom.read(407, 5).toFloat();
  #elif defined(T4_CONFIG)
    configuration.timeToOff = Eeprom.read(385 + id * nextRelay, 5).toFloat();
  #elif defined(T5_CONFIG)
    configuration.timeToOff = Eeprom.read(463, 4).toInt();
  #endif


  #if !defined(T5_CONFIG)

  #if defined(T0_CONFIG) || defined(T0_SHELLY_1_CONFIG)
    configuration.statePowerOn = Eeprom.readUInt8(377);
  #elif defined(T1_CONFIG)
    configuration.statePowerOn = Eeprom.readUInt8(404);
  #elif defined(T2_CONFIG)
    configuration.statePowerOn = Eeprom.readUInt8(412);
  #elif defined(T3_CONFIG)
    configuration.statePowerOn = Eeprom.readUInt8(384 + id * nextRelay);
  #elif defined(T4_CONFIG)
    configuration.statePowerOn = Eeprom.readUInt8(390 + id * nextRelay);
  #elif defined(T6_CONFIG)
    configuration.statePowerOn = Eeprom.readUInt8(376);
  #endif

  #if defined(T0_CONFIG) || defined(T0_SHELLY_1_CONFIG)
    Eeprom.read(378, 16).toCharArray(configuration.name,
                                     sizeof(configuration.name));
  #elif defined(T1_CONFIG)
    Eeprom.read(405, 16).toCharArray(configuration.name,
                                     sizeof(configuration.name));
  #elif defined(T2_CONFIG)
    Eeprom.read(413, 16).toCharArray(configuration.name,
                                     sizeof(configuration.name));
  #elif defined(T3_CONFIG)
    Eeprom.read(385 + id * nextRelay, 16)
        .toCharArray(configuration.name, sizeof(configuration.name));
  #elif defined(T4_CONFIG)
    Eeprom.read(391 + id * nextRelay, 16)
        .toCharArray(configuration.name, sizeof(configuration.name));
  #elif defined(T6_CONFIG)
    Eeprom.read(377, 16).toCharArray(configuration.name,
                                     sizeof(configuration.name));
  #endif

  #if defined(T0_CONFIG) || defined(T0_SHELLY_1_CONFIG)
    configuration.stateMQTTConnected = Eeprom.readUInt8(394);
  #elif defined(T1_CONFIG)
    configuration.stateMQTTConnected = Eeprom.readUInt8(421);
  #elif defined(T2_CONFIG)
    configuration.stateMQTTConnected = Eeprom.readUInt8(429);
  #elif defined(T3_CONFIG)
    configuration.stateMQTTConnected = Eeprom.readUInt8(401 + id * nextRelay);
  #elif defined(T4_CONFIG)
    configuration.stateMQTTConnected = Eeprom.readUInt8(407 + id * nextRelay);
  #elif defined(T6_CONFIG)
    configuration.stateMQTTConnected = Eeprom.readUInt8(393);
  #endif

    Eeprom.read(334, 32).toCharArray(configurationMQTT.topic,
                                     sizeof(configurationMQTT.topic));



  #if defined(T0_CONFIG)
    configuration.ledID = Eeprom.readUInt8(421);
  #elif defined(T1_CONFIG)
    configuration.ledID = Eeprom.readUInt8(442);
  #elif defined(T2_CONFIG)
    configuration.ledID = Eeprom.readUInt8(463);
  #elif defined(T3_CONFIG)
    configuration.ledID = Eeprom.readUInt8(618 + id);
  #elif defined(T4_CONFIG)
    configuration.ledID = Eeprom.readUInt8(531 + id);
  #elif defined(T6_CONFIG)
    configuration.ledID = Eeprom.readUInt8(394);
  #endif

  #if !defined(T6_CONFIG)
    configuration.idx = Eeprom.read(930 + 6 * id, 6).toInt();
  #else
    configuration.idx = Eeprom.read(920, 6).toInt();
  #endif

  #if defined(T1_CONFIG) || defined(T2_CONFIG)
  #if defined(T1_CONFIG)
    configuration.thermostat.turnOn = Eeprom.read(423, 5).toFloat();
    configuration.thermostat.turnOff = Eeprom.read(428, 5).toFloat();
    configuration.thermostat.turnOnAbove = Eeprom.read(433);
    configuration.thermostat.turnOffAbove = Eeprom.read(434);
    configuration.thermostat.enabled = isRegulatorEnabled(THERMOSTAT_REGULATOR);
  #else
    configuration.thermostat.turnOn = Eeprom.read(431, 5).toFloat();
    configuration.thermostat.turnOff = Eeprom.read(436, 5).toFloat();
    configuration.thermostat.turnOnAbove = Eeprom.read(441);
    configuration.thermostat.turnOffAbove = Eeprom.read(442);
    configuration.thermostat.enabled = isRegulatorEnabled(THERMOSTAT_REGULATOR);
  #endif
  #endif

  #if defined(T2_CONFIG)
    configuration.humidistat.turnOn = Eeprom.read(444, 5).toFloat();
    configuration.humidistat.turnOff = Eeprom.read(449, 5).toFloat();
    configuration.humidistat.turnOnAbove = Eeprom.read(454);
    configuration.humidistat.turnOffAbove = Eeprom.read(455);
    configuration.humidistat.enabled = isRegulatorEnabled(HUMIDISTAT_REGULATOR);
  #endif


  #if defined(T1_CONFIG)
    configuration.thermalProtection = Eeprom.read(436, 3).toInt();
  #elif defined(T2_CONFIG)
    configuration.thermalProtection = Eeprom.read(457, 3).toInt();
  #endif

  #endif
  */

  return configuration;
}
void AFEDataAccess::saveConfiguration(uint8_t id, RELAY configuration) {
  char fileName[17];
  sprintf(fileName, "cfg-relay-%d.json", id);

#ifdef DEBUG
  Serial << endl
         << endl
         << "----------------- Writing File -------------------";
  Serial << endl << "Opening file: " << fileName << " : ";
#endif

  File configFile = SPIFFS.open(fileName, "w");

  if (configFile) {
#ifdef DEBUG
    Serial << "success" << endl << "Writing JSON : ";
#endif

    StaticJsonBuffer<200> jsonBuffer;
    JsonObject &root = jsonBuffer.createObject();

    root["gpio"] = configuration.gpio;
    root["name"] = configuration.name;
    root["timeToOff"] = configuration.timeToOff;
    root["statePowerOn"] = configuration.state.powerOn;
    root["stateMQTTConnected"] = configuration.state.MQTTConnected;
    root["ledID"] = configuration.ledID;
    root["idx"] = configuration.domoticz.idx;
    root["MQTTTopic"] = configuration.mqtt.topic;

    root.printTo(configFile);
#ifdef DEBUG
    root.printTo(Serial);
#endif
    configFile.close();

#ifdef DEBUG
    Serial << endl
           << "success" << endl
           << "JSON Buffer size: " << jsonBuffer.size();
#endif

  }
#ifdef DEBUG
  else {
    Serial << endl << "failed to open file for writing";
  }
  Serial << endl << "--------------------------------------------------";
#endif
  /*
  #if defined(T3_CONFIG)
    uint8_t nextRelay = 21;
  #elif defined(T4_CONFIG)
    uint8_t nextRelay = 27;
  #endif

  #if defined(T0_CONFIG) || defined(T0_SHELLY_1_CONFIG)
    Eeprom.writeUInt8(370, configuration.gpio);
  #elif defined(T1_CONFIG)
    Eeprom.writeUInt8(397, configuration.gpio);
  #elif defined(T2_CONFIG)
    Eeprom.writeUInt8(405, configuration.gpio);
  #elif defined(T3_CONFIG)
    Eeprom.writeUInt8(382 + id * nextRelay, configuration.gpio);
  #elif defined(T4_CONFIG)
    Eeprom.writeUInt8(383 + id * nextRelay, configuration.gpio);
  #elif defined(T5_CONFIG)
    Eeprom.writeUInt8(462, configuration.gpio);
  #elif defined(T6_CONFIG)
    Eeprom.writeUInt8(374, configuration.gpio);
  #endif

  #if defined(T0_CONFIG) || defined(T0_SHELLY_1_CONFIG)
    Eeprom.write(372, 5, configuration.timeToOff);
  #elif defined(T1_CONFIG)
    Eeprom.write(399, 5, configuration.timeToOff);
  #elif defined(T2_CONFIG)
    Eeprom.write(407, 5, configuration.timeToOff);
  #elif defined(T4_CONFIG)
    Eeprom.write(385 + id * nextRelay, 5, configuration.timeToOff);
  #elif defined(T5_CONFIG)
    Eeprom.write(463, 4, configuration.timeToOff);
  #endif

  #if !defined(T5_CONFIG)

  #if defined(T0_CONFIG) || defined(T0_SHELLY_1_CONFIG)
    Eeprom.writeUInt8(377, configuration.statePowerOn);
  #elif defined(T1_CONFIG)
    Eeprom.writeUInt8(404, configuration.statePowerOn);
  #elif defined(T2_CONFIG)
    Eeprom.writeUInt8(412, configuration.statePowerOn);
  #elif defined(T3_CONFIG)
    Eeprom.writeUInt8(384 + id * nextRelay, configuration.statePowerOn);
  #elif defined(T4_CONFIG)
    Eeprom.writeUInt8(390 + id * nextRelay, configuration.statePowerOn);
  #elif defined(T6_CONFIG)
    Eeprom.writeUInt8(376, configuration.statePowerOn);
  #endif

  #if defined(T0_CONFIG) || defined(T0_SHELLY_1_CONFIG)
    Eeprom.write(378, 16, configuration.name);
  #elif defined(T1_CONFIG)
    Eeprom.write(405, 16, configuration.name);
  #elif defined(T2_CONFIG)
    Eeprom.write(413, 16, configuration.name);
  #elif defined(T3_CONFIG)
    Eeprom.write(385 + id * nextRelay, 16, configuration.name);
  #elif defined(T4_CONFIG)
    Eeprom.write(391 + id * nextRelay, 16, configuration.name);
  #elif defined(T6_CONFIG)
    Eeprom.write(377, 16, configuration.name);
  #endif

  #if defined(T0_CONFIG) || defined(T0_SHELLY_1_CONFIG)
    Eeprom.writeUInt8(394, configuration.stateMQTTConnected);
  #elif defined(T1_CONFIG)
    Eeprom.writeUInt8(421, configuration.stateMQTTConnected);
  #elif defined(T2_CONFIG)
    Eeprom.writeUInt8(429, configuration.stateMQTTConnected);
  #elif defined(T3_CONFIG)
    Eeprom.writeUInt8(401 + id * nextRelay, configuration.stateMQTTConnected);
  #elif defined(T4_CONFIG)
    Eeprom.writeUInt8(407 + id * nextRelay, configuration.stateMQTTConnected);
  #elif defined(T6_CONFIG)
    Eeprom.writeUInt8(393, configuration.stateMQTTConnected);
  #endif

  #if defined(T0_CONFIG)
    Eeprom.writeUInt8(421, configuration.ledID);
  #elif defined(T1_CONFIG)
    Eeprom.writeUInt8(442, configuration.ledID);
  #elif defined(T2_CONFIG)
    Eeprom.writeUInt8(463, configuration.ledID);
  #elif defined(T3_CONFIG)
    Eeprom.writeUInt8(618 + id, configuration.ledID);
  #elif defined(T4_CONFIG)
    Eeprom.writeUInt8(531 + id, configuration.ledID);
  #elif defined(T6_CONFIG)
    Eeprom.writeUInt8(394, configuration.ledID);
  #endif

  #if !defined(T6_CONFIG)
    Eeprom.write(930 + 6 * id, 6, (long)configuration.idx);
  #else
    Eeprom.write(920, 6, (long)configuration.idx);
  #endif

  #if defined(T1_CONFIG)
    Eeprom.write(436, 3, configuration.thermalProtection);
  #elif defined(T2_CONFIG)
    Eeprom.write(457, 3, configuration.thermalProtection);
  #endif

  #endif
  */
}

SWITCH AFEDataAccess::getSwitchConfiguration(uint8_t id) {
  SWITCH configuration;

  char fileName[18];
  sprintf(fileName, "cfg-switch-%d.json", id);

#ifdef DEBUG
  Serial << endl
         << endl
         << "----------------- Reading File -------------------";
  Serial << endl << "Opening file: " << fileName << " : ";
#endif

  File configFile = SPIFFS.open(fileName, "r");

  if (configFile) {
#ifdef DEBUG
    Serial << "success" << endl << "Reading JSON : ";
#endif

    size_t size = configFile.size();
    std::unique_ptr<char[]> buf(new char[size]);
    configFile.readBytes(buf.get(), size);
    StaticJsonBuffer<200> jsonBuffer;
    JsonObject &root = jsonBuffer.parseObject(buf.get());
    if (root.success()) {
#ifdef DEBUG
      root.printTo(Serial);
#endif

      configuration.gpio = root.get<int>("gpio");
      configuration.type = root.get<int>("type");
      configuration.sensitiveness = root.get<int>("sensitiveness");
      configuration.functionality = root.get<int>("functionality");
      configuration.relayID = root.get<int>("relayID");
      sprintf(configuration.mqtt.topic, root.get<char *>("MQTTTopic"));
      configuration.domoticz.idx = root.get<int>("idx");

#ifdef DEBUG
      Serial << endl
             << "success" << endl
             << "JSON Buffer size: " << jsonBuffer.size();
#endif
    }

#ifdef DEBUG
    else {
      Serial << "failure";
    }
#endif

    configFile.close();
  }

#ifdef DEBUG
  else {
    Serial << "failure";
  }
  Serial << endl << "--------------------------------------------------";
#endif

  return configuration;
}
void AFEDataAccess::saveConfiguration(uint8_t id, SWITCH configuration) {
  char fileName[18];
  sprintf(fileName, "cfg-switch-%d.json", id);

#ifdef DEBUG
  Serial << endl
         << endl
         << "----------------- Writing File -------------------";
  Serial << endl << "Opening file: " << fileName << " : ";
#endif

  File configFile = SPIFFS.open(fileName, "w");

  if (configFile) {
#ifdef DEBUG
    Serial << "success" << endl << "Writing JSON : ";
#endif

    StaticJsonBuffer<200> jsonBuffer;
    JsonObject &root = jsonBuffer.createObject();

    root["gpio"] = configuration.gpio;
    root["type"] = configuration.type;
    root["sensitiveness"] = configuration.sensitiveness;
    root["functionality"] = configuration.functionality;
    root["relayID"] = configuration.relayID;
    root["idx"] = configuration.domoticz.idx;
    root["MQTTTopic"] = configuration.mqtt.topic;

    root.printTo(configFile);
#ifdef DEBUG
    root.printTo(Serial);
#endif
    configFile.close();

#ifdef DEBUG
    Serial << endl
           << "success" << endl
           << "JSON Buffer size: " << jsonBuffer.size();
#endif

  }
#ifdef DEBUG
  else {
    Serial << endl << "failed to open file for writing";
  }
  Serial << endl << "--------------------------------------------------";
#endif
}

#ifdef CONFIG_HARDWARE_DS18B20
DS18B20 AFEDataAccess::getSensorConfiguration() {
  DS18B20 configuration;
  configuration.gpio = Eeprom.readUInt8(370);
  configuration.correction = Eeprom.read(371, 5).toFloat();
  configuration.interval = Eeprom.read(376, 5).toInt();
  configuration.unit = Eeprom.readUInt8(381);
  configuration.sendOnlyChanges = Eeprom.read(446);
  configuration.idx = Eeprom.read(936, 6).toInt();
  return configuration;
}
void AFEDataAccess::saveConfiguration(DS18B20 configuration) {
  Eeprom.writeUInt8(370, configuration.gpio);
  Eeprom.write(371, 5, (float)configuration.correction);
  Eeprom.write(376, 5, (long)configuration.interval);
  Eeprom.writeUInt8(381, configuration.unit);
  Eeprom.write(446, configuration.sendOnlyChanges);
  Eeprom.write(936, 6, (long)configuration.idx);
}
#endif

#ifdef CONFIG_HARDWARE_DHXX
DH AFEDataAccess::getSensorConfiguration() {
  DH configuration;
#if defined(T2_CONFIG)
  configuration.gpio = Eeprom.readUInt8(370);
  configuration.type = Eeprom.readUInt8(371);
  configuration.interval = Eeprom.read(372, 5).toInt();
  configuration.temperature.unit = Eeprom.readUInt8(377);
  configuration.temperature.correction = Eeprom.read(378, 4).toFloat();
  configuration.humidity.correction = Eeprom.read(387, 3).toFloat();
  configuration.temperatureIdx = Eeprom.read(936, 6).toInt();
  configuration.humidityIdx = Eeprom.read(942, 6).toInt();
  configuration.temperatureAndHumidityIdx = Eeprom.read(948, 6).toInt();
  configuration.sendOnlyChanges = Eeprom.read(467);
  configuration.publishHeatIndex = Eeprom.read(974);
  configuration.publishDewPoint = Eeprom.read(382);
#else
  configuration.gpio = Eeprom.readUInt8(377);
  configuration.type = Eeprom.readUInt8(378);
  configuration.interval = Eeprom.read(379, 5).toInt();
  configuration.temperature.unit = Eeprom.readUInt8(384);
  configuration.temperature.correction = Eeprom.read(385, 4).toFloat();
  configuration.humidity.correction = Eeprom.read(394, 3).toFloat();
  configuration.temperatureIdx = Eeprom.read(954, 6).toInt();
  configuration.humidityIdx = Eeprom.read(960, 6).toInt();
  configuration.temperatureAndHumidityIdx = Eeprom.read(966, 6).toInt();
  configuration.sendOnlyChanges = Eeprom.read(397);
  configuration.publishHeatIndex = Eeprom.read(990);
  configuration.publishDewPoint = Eeprom.read(389);
#endif

  return configuration;
}
void AFEDataAccess::saveConfiguration(DH configuration) {
#if defined(T2_CONFIG)
  Eeprom.writeUInt8(370, configuration.gpio);
  Eeprom.writeUInt8(371, configuration.type);
  Eeprom.write(372, 5, (long)configuration.interval);
  Eeprom.writeUInt8(377, configuration.temperature.unit);
  Eeprom.write(378, 4, (float)configuration.temperature.correction);
  Eeprom.write(387, 3, (float)configuration.humidity.correction);
  Eeprom.write(936, 6, (long)configuration.temperatureIdx);
  Eeprom.write(942, 6, (long)configuration.humidityIdx);
  Eeprom.write(948, 6, (long)configuration.temperatureAndHumidityIdx);
  Eeprom.write(467, configuration.sendOnlyChanges);
  Eeprom.write(974, configuration.publishHeatIndex);
  Eeprom.write(382, configuration.publishDewPoint);
#else
  Eeprom.writeUInt8(377, configuration.gpio);
  Eeprom.writeUInt8(378, configuration.type);
  Eeprom.write(379, 5, (long)configuration.interval);
  Eeprom.writeUInt8(384, configuration.temperature.unit);
  Eeprom.write(385, 4, (float)configuration.temperature.correction);
  Eeprom.write(394, 3, (float)configuration.humidity.correction);
  Eeprom.write(954, 6, (long)configuration.temperatureIdx);
  Eeprom.write(960, 6, (long)configuration.humidityIdx);
  Eeprom.write(966, 6, (long)configuration.temperatureAndHumidityIdx);
  Eeprom.write(397, configuration.sendOnlyChanges);
  Eeprom.write(990, configuration.publishHeatIndex);
  Eeprom.write(389, configuration.publishDewPoint);
#endif
}
#endif

/* T3: PIR */
#if defined(T3_CONFIG)
PIR AFEDataAccess::getPIRConfiguration(uint8_t id) {
  PIR configuration;
  MQTT configurationMQTT;
  uint8_t nextPIR = 27;
  configuration.gpio = Eeprom.readUInt8(506 + id * nextPIR);

  Eeprom.read(507 + id * nextPIR, 16)
      .toCharArray(configuration.name, sizeof(configuration.name));

  configuration.ledId = Eeprom.readUInt8(524 + id * nextPIR);
  configuration.relayId = Eeprom.readUInt8(525 + id * nextPIR);
  configuration.howLongKeepRelayOn = Eeprom.read(526 + id * nextPIR, 5).toInt();
  configuration.invertRelayState = Eeprom.read(531 + id * nextPIR);

  configuration.outputDefaultState = Eeprom.readUInt8(613 + id);
  configuration.idx = Eeprom.read(954 + id * 6, 6).toInt();

  Eeprom.read(334, 32).toCharArray(configurationMQTT.topic,
                                   sizeof(configurationMQTT.topic));

  sprintf(configuration.mqttTopic, "%s%s/", configurationMQTT.topic,
          configuration.name);

  return configuration;
}
void AFEDataAccess::saveConfiguration(uint8_t id, PIR configuration) {
  uint8_t nextPIR = 27;
  Eeprom.writeUInt8(506 + id * nextPIR, configuration.gpio);
  Eeprom.write(507 + id * nextPIR, 16, configuration.name);
  Eeprom.writeUInt8(524 + id * nextPIR, configuration.ledId);
  Eeprom.writeUInt8(525 + id * nextPIR, configuration.relayId);
  Eeprom.write(526 + id * nextPIR, 5, (long)configuration.howLongKeepRelayOn);
  Eeprom.write(531 + id * nextPIR, configuration.invertRelayState);

  Eeprom.writeUInt8(613 + id, configuration.outputDefaultState);
  Eeprom.write(954 + id, 6, (long)configuration.idx);
}
#endif

#if defined(T5_CONFIG)
CONTACTRON AFEDataAccess::getContactronConfiguration(uint8_t id) {
  CONTACTRON configuration;
  uint8_t nextContactron = 24;
  MQTT configurationMQTT;

  configuration.gpio = Eeprom.readUInt8(415 + id * nextContactron);
  configuration.outputDefaultState =
      Eeprom.readUInt8(416 + id * nextContactron);
  configuration.ledID = Eeprom.readUInt8(417 + id * nextContactron);
  configuration.bouncing = Eeprom.read(418 + id * nextContactron, 4).toInt();

  Eeprom.read(422 + id * nextContactron, 16)
      .toCharArray(configuration.name, sizeof(configuration.name));

  Eeprom.read(334, 32).toCharArray(configurationMQTT.topic,
                                   sizeof(configurationMQTT.topic));

  sprintf(configuration.mqttTopic, "%s%s/", configurationMQTT.topic,
          configuration.name);

  configuration.idx = Eeprom.read(942 + id * 6, 6).toInt();

  return configuration;
}
void AFEDataAccess::saveConfiguration(uint8_t id, CONTACTRON configuration) {
  uint8_t nextContactron = 24;
  Eeprom.writeUInt8(415 + id * nextContactron, configuration.gpio);
  Eeprom.writeUInt8(416 + id * nextContactron,
                    configuration.outputDefaultState);
  Eeprom.writeUInt8(417 + id * nextContactron, configuration.ledID);
  Eeprom.write(418 + id * nextContactron, 4, (long)configuration.bouncing);
  Eeprom.write(422 + id * nextContactron, 16, configuration.name);
  Eeprom.write(942 + id * 6, 6, (long)configuration.idx);
}

GATE AFEDataAccess::getGateConfiguration() {
  GATE configuration;
  for (uint8_t i = 0; i < sizeof(configuration.state); i++) {
    configuration.state[i] = Eeprom.readUInt8(467 + i);
  }
  configuration.idx = Eeprom.read(936, 6).toInt();
  return configuration;
}
void AFEDataAccess::saveConfiguration(GATE configuration) {
  for (uint8_t i = 0; i < sizeof(configuration.state); i++) {
    Eeprom.writeUInt8(467 + i, configuration.state[i]);
  }
  Eeprom.write(936, 6, (long)configuration.idx);
}

uint8_t AFEDataAccess::getGateState() { return Eeprom.readUInt8(471); }

void AFEDataAccess::saveGateState(uint8_t state) {
  Eeprom.writeUInt8(471, state);
}
#endif

#ifdef CONFIG_FUNCTIONALITY_REGULATOR
void AFEDataAccess::saveConfiguration(REGULATOR configuration, uint8_t type) {

  if (type == THERMOSTAT_REGULATOR) {
    saveRegulatorState(configuration.enabled, THERMOSTAT_REGULATOR);
  } else {
    saveRegulatorState(configuration.enabled, HUMIDISTAT_REGULATOR);
  }

#if defined(T1_CONFIG)
  Eeprom.write(423, 5, configuration.turnOn);
  Eeprom.write(428, 5, configuration.turnOff);
  Eeprom.write(433, configuration.turnOnAbove);
  Eeprom.write(434, configuration.turnOffAbove);
#else
  uint8_t index = type == THERMOSTAT_REGULATOR ? 0 : 13;
  Eeprom.write(431 + index, 5, configuration.turnOn);
  Eeprom.write(436 + index, 5, configuration.turnOff);
  Eeprom.write(441 + index, configuration.turnOnAbove);
  Eeprom.write(442 + index, configuration.turnOffAbove);

#endif
}

boolean AFEDataAccess::isRegulatorEnabled(uint8_t type) {
  if (type == THERMOSTAT_REGULATOR) {
#if defined(T1_CONFIG)
    return Eeprom.read(435);
#else
    return Eeprom.read(443);
#endif
  } else {
    return Eeprom.read(456);
  }
}

void AFEDataAccess::saveRegulatorState(boolean state, uint8_t type) {
  if (type == THERMOSTAT_REGULATOR) {
#if defined(T1_CONFIG)
    Eeprom.write(435, state);
#else
    Eeprom.write(443, state);
#endif
  } else {
    Eeprom.write(456, state);
  }
}
#endif

void AFEDataAccess::saveVersion(const char *version) {
  FIRMWARE configuration = getFirmwareConfiguration();
  sprintf(configuration.version, version);
  saveConfiguration(configuration);
}

/* Relay state methods*/
#if !defined(T5_CONFIG)
boolean AFEDataAccess::getRelayState(uint8_t id) {
  boolean state = false;
  char fileName[23];
  sprintf(fileName, "cfg-relay-state-%d.json", id);

#ifdef DEBUG
  Serial << endl
         << endl
         << "----------------- Reading File -------------------";
  Serial << endl << "Opening file: " << fileName << " : ";
#endif

  File configFile = SPIFFS.open(fileName, "r");

  if (configFile) {
#ifdef DEBUG
    Serial << "success" << endl << "Reading JSON : ";
#endif

    size_t size = configFile.size();
    std::unique_ptr<char[]> buf(new char[size]);
    configFile.readBytes(buf.get(), size);
    StaticJsonBuffer<50> jsonBuffer;
    JsonObject &root = jsonBuffer.parseObject(buf.get());
    if (root.success()) {
#ifdef DEBUG
      root.printTo(Serial);
#endif
      state = root.get<bool>("state");

#ifdef DEBUG
      Serial << endl
             << "success" << endl
             << "JSON Buffer size: " << jsonBuffer.size();
#endif
    }

#ifdef DEBUG
    else {
      Serial << "failure";
    }
#endif

    configFile.close();
  }

#ifdef DEBUG
  else {
    Serial << "failure";
  }
  Serial << endl << "--------------------------------------------------";
#endif
  return state;
}
void AFEDataAccess::saveRelayState(uint8_t id, boolean state) {
  char fileName[23];
  sprintf(fileName, "cfg-relay-state-%d.json", id);

#ifdef DEBUG
  Serial << endl
         << endl
         << "----------------- Writing File -------------------";
  Serial << endl << "Opening file: " << fileName << " : ";
#endif

  File configFile = SPIFFS.open(fileName, "w");

  if (configFile) {
#ifdef DEBUG
    Serial << "success" << endl << "Writing JSON : ";
#endif

    StaticJsonBuffer<50> jsonBuffer;
    JsonObject &root = jsonBuffer.createObject();

    root["state"] = state;

    root.printTo(configFile);
#ifdef DEBUG
    root.printTo(Serial);
#endif
    configFile.close();

#ifdef DEBUG
    Serial << endl
           << "success" << endl
           << "JSON Buffer size: " << jsonBuffer.size();
#endif

  }
#ifdef DEBUG
  else {
    Serial << endl << "failed to open file for writing";
  }
  Serial << endl << "--------------------------------------------------";
#endif
}
#endif /* End: Relay */

uint8_t AFEDataAccess::getDeviceMode() {
  boolean mode = MODE_FIRST_TIME_LAUNCH;
#ifdef DEBUG
  Serial << endl
         << endl
         << "----------------- Reading File -------------------";
  Serial << endl << "Opening file: cfg-device-mode.json : ";
#endif

  File configFile = SPIFFS.open("cfg-device-mode.json", "r");

  if (configFile) {
#ifdef DEBUG
    Serial << "success" << endl << "Reading JSON : ";
#endif

    size_t size = configFile.size();
    std::unique_ptr<char[]> buf(new char[size]);
    configFile.readBytes(buf.get(), size);
    StaticJsonBuffer<50> jsonBuffer;
    JsonObject &json = jsonBuffer.parseObject(buf.get());
    if (json.success()) {
#ifdef DEBUG
      json.printTo(Serial);
      Serial << endl;
#endif
      mode = json["mode"];
#ifdef DEBUG
      Serial << "success";
#endif
    }
#ifdef DEBUG
    else {
      Serial << "failure";
    }
#endif

    configFile.close();
  }

#ifdef DEBUG
  else {
    Serial << "failure";
  }
  Serial << endl << "--------------------------------------------------";
#endif

  return mode;
}
void AFEDataAccess::saveDeviceMode(uint8_t mode) {
#ifdef DEBUG
  Serial << endl
         << endl
         << "----------------- Writing File -------------------";
  Serial << endl << "Opening file: cfg-device-mode.json : ";
#endif

  File configFile = SPIFFS.open("cfg-device-mode.json", "w");

  if (configFile) {
#ifdef DEBUG
    Serial << "success" << endl << "Writing JSON : ";
#endif

    StaticJsonBuffer<50> jsonBuffer;
    JsonObject &json = jsonBuffer.createObject();
    json["mode"] = mode;
    json.printTo(configFile);
#ifdef DEBUG
    json.printTo(Serial);
    Serial << endl;
#endif
    configFile.close();

#ifdef DEBUG
    Serial << "success";
#endif

  }
#ifdef DEBUG
  else {
    Serial << endl << "failed to open file for writing";
  }
  Serial << endl << "--------------------------------------------------";
#endif
}

uint8_t AFEDataAccess::getLanguage() {
  uint8_t language = 0;
#ifdef DEBUG
  Serial << endl
         << endl
         << "----------------- Reading File -------------------";
  Serial << endl << "Opening file: cfg-ui-language.json : ";
#endif

  File configFile = SPIFFS.open("cfg-ui-language.json", "r");

  if (configFile) {
#ifdef DEBUG
    Serial << "success" << endl << "Reading JSON : ";
#endif

    size_t size = configFile.size();
    std::unique_ptr<char[]> buf(new char[size]);
    configFile.readBytes(buf.get(), size);
    StaticJsonBuffer<100> jsonBuffer;
    JsonObject &root = jsonBuffer.parseObject(buf.get());
    if (root.success()) {
#ifdef DEBUG
      root.printTo(Serial);
#endif
      language = root["language"];
#ifdef DEBUG
      Serial << endl
             << "success" << endl
             << "JSON Buffer size: " << jsonBuffer.size();
#endif
    }

#ifdef DEBUG
    else {
      Serial << "failure";
    }
#endif

    configFile.close();
  }

#ifdef DEBUG
  else {
    Serial << "failure";
  }
  Serial << endl << "--------------------------------------------------";
#endif

  return language;
}
void AFEDataAccess::saveLanguage(uint8_t language) {
#ifdef DEBUG
  Serial << endl
         << endl
         << "----------------- Writing File -------------------";
  Serial << endl << "Opening file: cfg-ui-language.json : ";
#endif

  File configFile = SPIFFS.open("cfg-ui-language.json", "w");

  if (configFile) {
#ifdef DEBUG
    Serial << "success" << endl << "Writing JSON : ";
#endif

    StaticJsonBuffer<200> jsonBuffer;
    JsonObject &root = jsonBuffer.createObject();

    root["language"] = language;
    root.printTo(configFile);
#ifdef DEBUG
    root.printTo(Serial);
#endif
    configFile.close();

#ifdef DEBUG
    Serial << endl
           << "success" << endl
           << "JSON Buffer size: " << jsonBuffer.size();
#endif

  }
#ifdef DEBUG
  else {
    Serial << endl << "failed to open file for writing";
  }
  Serial << endl << "--------------------------------------------------";
#endif
}

#ifdef CONFIG_HARDWARE_LED
uint8_t AFEDataAccess::getSystemLedID() {
  uint8_t id = 0;

#ifdef DEBUG
  Serial << endl
         << endl
         << "----------------- Reading File -------------------";
  Serial << endl << "Opening file: cfg-system-led.json : ";
#endif

  File configFile = SPIFFS.open("cfg-system-led.json", "r");

  if (configFile) {
#ifdef DEBUG
    Serial << "success" << endl << "Reading JSON : ";
#endif

    size_t size = configFile.size();
    std::unique_ptr<char[]> buf(new char[size]);
    configFile.readBytes(buf.get(), size);
    StaticJsonBuffer<50> jsonBuffer;
    JsonObject &root = jsonBuffer.parseObject(buf.get());
    if (root.success()) {
#ifdef DEBUG
      root.printTo(Serial);
#endif
      id = root.get<int>("id");

#ifdef DEBUG
      Serial << endl
             << "success" << endl
             << "JSON Buffer size: " << jsonBuffer.size();
#endif
    }

#ifdef DEBUG
    else {
      Serial << "failure";
    }
#endif

    configFile.close();
  }

#ifdef DEBUG
  else {
    Serial << "failure";
  }
  Serial << endl << "--------------------------------------------------";
#endif
  return id;
}
void AFEDataAccess::saveSystemLedID(uint8_t id) {
#ifdef DEBUG
  Serial << endl
         << endl
         << "----------------- Writing File -------------------";
  Serial << endl << "Opening file: cfg-system-led.json : ";
#endif

  File configFile = SPIFFS.open("cfg-system-led.json", "w");

  if (configFile) {
#ifdef DEBUG
    Serial << "success" << endl << "Writing JSON : ";
#endif

    StaticJsonBuffer<50> jsonBuffer;
    JsonObject &root = jsonBuffer.createObject();

    root["id"] = id;

    root.printTo(configFile);
#ifdef DEBUG
    root.printTo(Serial);
#endif
    configFile.close();

#ifdef DEBUG
    Serial << endl
           << "success" << endl
           << "JSON Buffer size: " << jsonBuffer.size();
#endif

  }
#ifdef DEBUG
  else {
    Serial << endl << "failed to open file for writing";
  }
  Serial << endl << "--------------------------------------------------";
#endif
}
#endif

void AFEDataAccess::saveAPI(uint8_t apiID, boolean state) {
  DEVICE configuration = getDeviceConfiguration();
  if (apiID == API_HTTP) {
    configuration.api.http = state;
  } else if (apiID == API_MQTT) {
    configuration.api.mqtt = state;
  } else if (apiID == API_DOMOTICZ) {
    configuration.api.domoticz = state;
    if (state) {
      configuration.api.http = true;
    }
  }
  saveConfiguration(configuration);
}

#ifdef CONFIG_HARDWARE_HPMA115S0
HPMA115S0 AFEDataAccess::getHPMA115S0SensorConfiguration() {
  HPMA115S0 configuration;
  configuration.interval = Eeprom.read(414, 5).toInt();
  configuration.timeToMeasure = Eeprom.read(419, 3).toInt();
  configuration.idx.pm25 = Eeprom.read(926, 6).toInt();
  configuration.idx.pm10 = Eeprom.read(932, 6).toInt();
  return configuration;
}
void AFEDataAccess::saveConfiguration(HPMA115S0 configuration) {
  Eeprom.write(414, 5, (long)configuration.interval);
  Eeprom.write(419, 3, (long)configuration.timeToMeasure);
  Eeprom.write(926, 6, (long)configuration.idx.pm25);
  Eeprom.write(932, 6, (long)configuration.idx.pm10);
}
#endif

#ifdef CONFIG_HARDWARE_UART
SERIALPORT AFEDataAccess::getSerialPortConfiguration() {
  SERIALPORT configuration;
  configuration.RXD = Eeprom.readUInt8(411);
  configuration.TXD = Eeprom.readUInt8(412);
  return configuration;
}
void AFEDataAccess::saveConfiguration(SERIALPORT configuration) {
  Eeprom.writeUInt8(411, configuration.RXD);
  Eeprom.writeUInt8(412, configuration.TXD);
}
#endif

#ifdef CONFIG_HARDWARE_BMX80
BMx80 AFEDataAccess::getBMx80SensorConfiguration() {
  BMx80 configuration;
  configuration.interval = Eeprom.read(423, 5).toInt();
  configuration.i2cAddress = Eeprom.readUInt8(428);
  configuration.idx.temperatureHumidityPressure = Eeprom.read(938, 6).toInt();
  configuration.idx.gasResistance = Eeprom.read(944, 6).toInt();
  configuration.idx.temperature = Eeprom.read(950, 6).toInt();
  configuration.idx.humidity = Eeprom.read(956, 6).toInt();
  configuration.idx.pressure = Eeprom.read(962, 6).toInt();
  return configuration;
}
void AFEDataAccess::saveConfiguration(BMx80 configuration) {
  Eeprom.write(423, 5, (long)configuration.interval);
  Eeprom.writeUInt8(428, configuration.i2cAddress);
  Eeprom.write(938, 6, (long)configuration.idx.temperatureHumidityPressure);
  Eeprom.write(944, 6, (long)configuration.idx.gasResistance);
  Eeprom.write(950, 6, (long)configuration.idx.temperature);
  Eeprom.write(956, 6, (long)configuration.idx.humidity);
  Eeprom.write(962, 6, (long)configuration.idx.pressure);
}
#endif

#ifdef CONFIG_HARDWARE_BH1750
BH1750 AFEDataAccess::getBH1750SensorConfiguration() {
  BH1750 configuration;
  configuration.interval = Eeprom.read(430, 5).toInt();
  configuration.i2cAddress = Eeprom.readUInt8(435);
  configuration.mode = Eeprom.readUInt8(436);
  configuration.idx = Eeprom.read(968, 6).toInt();
  return configuration;
}
void AFEDataAccess::saveConfiguration(BH1750 configuration) {
  Eeprom.write(430, 5, (long)configuration.interval);
  Eeprom.writeUInt8(435, configuration.i2cAddress);
  Eeprom.writeUInt8(436, configuration.mode);
  Eeprom.write(968, 6, (long)configuration.idx);
}
#endif

#ifdef CONFIG_HARDWARE_ADC_VCC

ADCINPUT AFEDataAccess::getADCInputConfiguration() {
  ADCINPUT configuration;

#ifdef DEBUG
  Serial << endl
         << endl
         << "----------------- Reading File -------------------";
  Serial << endl << "Opening file: cfg-analog-input.json : ";
#endif

  File configFile = SPIFFS.open("cfg-analog-input.json", "r");

  if (configFile) {
#ifdef DEBUG
    Serial << "success" << endl << "Reading JSON : ";
#endif

    size_t size = configFile.size();
    std::unique_ptr<char[]> buf(new char[size]);
    configFile.readBytes(buf.get(), size);
    StaticJsonBuffer<300> jsonBuffer;
    JsonObject &root = jsonBuffer.parseObject(buf.get());
    if (root.success()) {
#ifdef DEBUG
      root.printTo(Serial);
#endif
      configuration.gpio = root["gpio"];
      configuration.interval = root["interval"];
      configuration.numberOfSamples = root["numberOfSamples"];
      configuration.maxVCC = root["maxVCC"];
      sprintf(configuration.mqtt.topic, root["mqttTopic"]);
      configuration.domoticz.raw = root["idx"]["raw"];
      configuration.domoticz.percent = root["idx"]["percent"];
      configuration.domoticz.voltage = root["idx"]["voltage"];
#ifdef DEBUG
      Serial << endl
             << "success" << endl
             << "JSON Buffer size: " << jsonBuffer.size();
#endif
    }

#ifdef DEBUG
    else {
      Serial << "failure";
    }
#endif

    configFile.close();
  }

#ifdef DEBUG
  else {
    Serial << "failure";
  }
  Serial << endl << "--------------------------------------------------";
#endif

  return configuration;
}
void AFEDataAccess::saveConfiguration(ADCINPUT configuration) {
#ifdef DEBUG
  Serial << endl
         << endl
         << "----------------- Writing File -------------------";
  Serial << endl << "Opening file: cfg-analog-input.json : ";
#endif

  File configFile = SPIFFS.open("cfg-analog-input.json", "w");

  if (configFile) {
#ifdef DEBUG
    Serial << "success" << endl << "Writing JSON : ";
#endif

    StaticJsonBuffer<300> jsonBuffer;
    JsonObject &root = jsonBuffer.createObject();
    JsonObject &idx = root.createNestedObject("idx");

    root["gpio"] = configuration.gpio;
    root["interval"] = configuration.interval;
    root["numberOfSamples"] = configuration.numberOfSamples;
    root["maxVCC"] = configuration.maxVCC;
    root["mqttTopic"] = configuration.mqtt.topic;
    idx["raw"] = configuration.domoticz.raw;
    idx["percent"] = configuration.domoticz.percent;
    idx["voltage"] = configuration.domoticz.voltage;
    root.printTo(configFile);
#ifdef DEBUG
    root.printTo(Serial);
#endif
    configFile.close();

#ifdef DEBUG
    Serial << endl
           << "success" << endl
           << "JSON Buffer size: " << jsonBuffer.size();
#endif

  }
#ifdef DEBUG
  else {
    Serial << endl << "failed to open file for writing";
  }
  Serial << endl << "--------------------------------------------------";
#endif
};
#endif

IPAddress AFEDataAccess::IPfromString(const char *address) {
  IPAddress ip;
  if (!ip.fromString(address)) {
#ifdef DEBUG
    Serial << endl
           << "ERROR: converting from IP String (" << address
           << ") to IP address";
#endif
  };
  return ip;
}