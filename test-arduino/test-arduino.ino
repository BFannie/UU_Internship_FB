/*
  LED

  This example creates a Bluetooth® Low Energy peripheral with service that contains a
  characteristic to control an LED.

  The circuit:
  - Arduino MKR WiFi 1010, Arduino Uno WiFi Rev2 board, Arduino Nano 33 IoT,
    Arduino Nano 33 BLE, or Arduino Nano 33 BLE Sense board.

  You can use a generic Bluetooth® Low Energy central app, like LightBlue (iOS and Android) or
  nRF Connect (Android), to interact with the services and characteristics
  created in this sketch.

  This example code is in the public domain.
*/

#include <ArduinoBLE.h>

BLEService ledService("180A"); // Bluetooth® Low Energy LED Service

// Bluetooth® Low Energy LED Switch Characteristic - custom 128-bit UUID, read and writable by central
BLEByteCharacteristic switchCharacteristic("2A57", BLERead | BLEWrite);

const int ledPin = LED_BUILTIN; // pin to use for the LED

void setup() {
  Serial.begin(9600);
  while (!Serial);

  // set LED pin to output mode
  pinMode(LED_BUILTIN, OUTPUT);

  // begin initialization
  if (!BLE.begin()) {
    Serial.println("starting Bluetooth® Low Energy module failed!");

    while (1);
  }

  // set advertised local name and service UUID:
  BLE.setLocalName("Nano 33 IoT");
  BLE.setAdvertisedService(ledService);

  // add the characteristic to the service
  ledService.addCharacteristic(switchCharacteristic);

  // add service
  BLE.addService(ledService);

  // set the initial value for the characeristic:
  switchCharacteristic.writeValue(0);

  // start advertising
  BLE.advertise();

  Serial.println("BLE LED Peripheral");
}

void loop() {
  // listen for Bluetooth® Low Energy peripherals to connect:
  BLEDevice central = BLE.central();

  // if a central is connected to peripheral:
  if (central) {
    Serial.print("Connected to central: ");
    // print the central's MAC address:
    Serial.println(central.address());

    // while the central is still connected to peripheral:
while (central.connected()) {
  // if the remote device wrote to the characteristic,
  // use the value to control the LED:
  if (switchCharacteristic.written()) {
    switch (switchCharacteristic.value()) {   // any value other than 0
      case 01:
        Serial.println("LED on");
        digitalWrite(LED_BUILTIN, HIGH);            // will turn the LED on
        break;
      case 02:
          Serial.println("LED fast blink");
          digitalWrite(LED_BUILTIN, HIGH);         // will turn the LED on
          delay(500);
          digitalWrite(LED_BUILTIN, LOW);         // will turn the LED off
          delay(500);
          digitalWrite(LED_BUILTIN, HIGH);      // will turn the LED on
          delay(500);
          digitalWrite(LED_BUILTIN, LOW);       // will turn the LED off
        break;
      case 03:
        Serial.println("LED slow blink");
        digitalWrite(LED_BUILTIN, HIGH);         // will turn the LED on
          delay(1000);
          digitalWrite(LED_BUILTIN, LOW);         // will turn the LED off
          delay(1000);
          digitalWrite(LED_BUILTIN, HIGH);      // will turn the LED on
          delay(1000);
          digitalWrite(LED_BUILTIN, LOW);       // will turn the LED off
        break;
      default:
        Serial.println(F("LED off"));
        digitalWrite(LED_BUILTIN, LOW);          // will turn the LED off
        break;
    }
  }
}

    // when the central disconnects, print it out:
    Serial.print(F("Disconnected from central: "));
    Serial.println(central.address());
    digitalWrite(LED_BUILTIN,LOW);   //it will turn the LEDoff
  }
}
