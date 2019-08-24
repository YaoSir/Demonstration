# Advanced BLE Demo with Arduino
## What is this?
This project aims to get sensor data from [Arduino NANO 33 BLE SENSE](https://store.arduino.cc/usa/nano-33-ble-sense-with-headers) using [GL-X750 Spitz](https://www.gl-inet.com/products/gl-x750/) through BLE. And then push it to the Cloud through MQTT.
![BLE to Internet](https://github.com/YaoSir/Demonstration/blob/master/images/BLE-Internet.JPG)
## How to make it?
- **Hardware Requirements**  
Firstly, prepare an [Arduino NANO 33 BLE SENSE](https://store.arduino.cc/usa/nano-33-ble-sense-with-headers). It has many environment sensors which provide us temperature, pressure, humidity and acceleration information. It supports BLE (Bluetooth Low Energy), so we can easily get these data through BLE.
Secondly, prepare a [GL-X750 Spitz](https://www.gl-inet.com/products/gl-x750/) or [GL-S1300 Convexa-S](https://www.gl-inet.com/products/gl-s1300/), they all support BLE. Here I use GL-X750. It supports BLE and 4G LTE. So you can get sensor data from BLE and then send it to the Cloud through either wan port or 4G LTE.

- **Software Requirements**  
For Arduino NANO 33 BLE SENSE, install following Libraries on your Arduino IDE.
[How to install and use Arduino IDE](https://www.arduino.cc/en/Main/Software)
`ArduinoBLE, Arduino_APDS9960, Arduino_HTS221, Arduino_LPS22HB, Arduino_LSM9DS1`
For GL-X750 Spitz or GL-S1300 Convexa-S, install the BLE packages `gl-ble`.  
You can login to the router's web interface and search "gl-ble" in the "Plug-ins" page, click "install" to install the package. Or just type command `opkg update & opkg install gl-ble` in the router's SSH terminal.
- **Set Arduino Board**  
Connect the Arduino board to computer, open the Arduino IDE and then set the Arduino serial COM. After that, copy the file `arduino_sensors.cpp` to the IDE, upload it to the Arduino board. When finished, a BLE device "Arduino_Sensors" will be brodcasted. You can easily check it with the Bluetooth of your smartphone.
- **Set The Router**  
[Get into the router's SSH terminal](https://docs.gl-inet.com/en/3/app/ssh/), copy the file `arduino_sensors.sh` to the router. Add execution permission and run the script with command `chmod +x arduino_sensors.sh & sh arduino_sensors.sh`.
## Examples
If everything is OK, you can see the sensors' data printed in the SSH terminal like that.
![](https://github.com/YaoSir/Demonstration/blob/master/images/sensor_data.JPG)
Login to the [cloud](https://www.goodcloud.xyz/#/login), you will see the sensor data send from your router.
![](https://github.com/YaoSir/Demonstration/blob/master/images/cloud.JPG) 
## Related Links
- [How to set cloud](https://docs.gl-inet.com/en/3/app/cloud/)
- [How to use MQTT](https://docs.gl-inet.com/en/3/app/ble2mqtt/)
