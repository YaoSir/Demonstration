#include <ArduinoBLE.h>
#include <Arduino_HTS221.h>
#include <Arduino_LPS22HB.h>
#include <Arduino_LSM9DS1.h>

BLEService ledService("19B10000-E8F2-537E-4F6C-D104768A1214"); // BLE LED Service

// BLE LED Switch Characteristic - custom 128-bit UUID, read and writable by central
BLEByteCharacteristic switchCharacteristic("19B10001-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite);
BLEFloatCharacteristic pressureCharacteristic("19B10002-E8F2-537E-4F6C-D104768A1214", BLERead);
BLEFloatCharacteristic tempCharacteristic("19B10003-E8F2-537E-4F6C-D104768A1214", BLERead );
BLEFloatCharacteristic humiCharacteristic("19B10004-E8F2-537E-4F6C-D104768A1214", BLERead);
BLEFloatCharacteristic AcceXCharacteristic("19B10005-E8F2-537E-4F6C-D104768A1214", BLERead);
BLEFloatCharacteristic AcceYCharacteristic("19B10006-E8F2-537E-4F6C-D104768A1214", BLERead);
BLEFloatCharacteristic AcceZCharacteristic("19B10007-E8F2-537E-4F6C-D104768A1214", BLERead);
long previousMillis = 0;
long currentMillis = 0;
const int ledPin = 13; // pin to use for the LED
                                                                                                                            
void setup() {
 
  //Set led pin
  pinMode(ledPin, OUTPUT);
  
  // begin initialization
  if (!BLE.begin()) {
    while (1);
  }
  if (!HTS.begin()) {
    while (1);
  }
  if (!BARO.begin()) {
    while (1);
  }
  if (!IMU.begin()) {
    while (1);
  }
  
  // set advertised local name and service UUID:
  BLE.setLocalName("Arduino_Sensors");
  BLE.setAdvertisedService(ledService);

  // add the characteristic to the service
  ledService.addCharacteristic(switchCharacteristic);
  ledService.addCharacteristic(pressureCharacteristic);
  ledService.addCharacteristic(tempCharacteristic);
  ledService.addCharacteristic(humiCharacteristic);
  ledService.addCharacteristic(AcceXCharacteristic);
  ledService.addCharacteristic(AcceYCharacteristic);
  ledService.addCharacteristic(AcceZCharacteristic);

  // add service
  BLE.addService(ledService);

  // set the initial value for the characeristic:
  switchCharacteristic.writeValue(0);
  pressureCharacteristic.writeValue(0);
  tempCharacteristic.writeValue(0);
  humiCharacteristic.writeValue(0);
  AcceXCharacteristic.writeValue(0);
  AcceYCharacteristic.writeValue(0);
  AcceZCharacteristic.writeValue(0);
  
  // start advertising
  BLE.advertise();

  //Serial.println("BLE LED Peripheral");  
}

void loop() {
  
 BLEDevice central = BLE.central();

  // if a central is connected to peripheral:
  if (central) {

    // while the central is still connected to peripheral:
    while (central.connected()) {
      // if the remote device wrote to the characteristic,
      // use the value to control the LED:
      currentMillis = millis();
      if (currentMillis - previousMillis >= 1000) {
        previousMillis = currentMillis;
        updateHTS221();
        updateLPS22H();
        updateAcce();
      }
      if (switchCharacteristic.written()) {
        if (switchCharacteristic.value()) {   // any value other than 0
          //Serial.println("LED on");
          digitalWrite(ledPin, LOW);         // will turn the LED on
        } else {                              // a 0 value
          //Serial.println(F("LED off"));
          digitalWrite(ledPin, HIGH);          // will turn the LED off
        }
      }
    }

    // when the central disconnects, print it out:
    //Serial.print(F("Disconnected from central: "));
    //Serial.println(central.address());
  }
}
void updateHTS221()
{
   float temperature = HTS.readTemperature();
   float humidity    = HTS.readHumidity();
   tempCharacteristic.writeValue(temperature);
   humiCharacteristic.writeValue(humidity);
}
void updateLPS22H()
{
  float pressure = BARO.readPressure();
   pressureCharacteristic.writeValue(pressure);
}
void updateAcce()
{
  float x, y, z;

  if (IMU.accelerationAvailable()) {
    IMU.readAcceleration(x, y, z);
    AcceXCharacteristic.writeValue(x);
    AcceYCharacteristic.writeValue(y);
    AcceZCharacteristic.writeValue(z);
  }
}
