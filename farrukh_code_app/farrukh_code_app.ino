// 27/01/2023 00:15:42
// LED_COBAK6a.ino
// ArduinoBLE - Version: Latest
#include <ArduinoBLE.h>

#define SERVICE_UUID "0000FFE0-0000-1000-8000-00805F9B34FB"
#define CHARACTERISTIC_UUID "0000FFE1-0000-1000-8000-00805F9B34FB"

/*
  LED

  This example creates a BLE peripheral with service that contains a
  characteristic to control an LED.

  The circuit:
  - Arduino MKR WiFi 1010, Arduino Uno WiFi Rev2 board, Arduino Nano 33 IoT,
    Arduino Nano 33 BLE, or Arduino Nano 33 BLE Sense board.

  You can use a generic BLE central app, like LightBlue (iOS and Android) or
  nRF Connect (Android), to interact with the services and characteristics
  created in this sketch.

  This example code is in the public domain.

  *** An LED (plus resistor) can be wired to a microcontroller in two ways ***
  (1) Between pin and GND in which case you have to drive the pin HIGH to switch the LED on.
  (2) Between pin and Vcc in which case you have to drive the pin LOW to switch the LED on.
*/

// BLE LED Service
BLEService ledService(SERVICE_UUID);

// BLE LED Switch Characteristic
BLEUnsignedShortCharacteristic switchCharacteristic(CHARACTERISTIC_UUID, BLERead | BLEWriteWithoutResponse);

void setup()
{
               //Serial.begin(9600);
               Serial.begin(115200);
               while (!Serial);

               // set LED pin to output mode
               pinMode(13, OUTPUT);
               //pinMode(5, OUTPUT);
               //pinMode(6, OUTPUT);
               //pinMode(7, OUTPUT);
               //pinMode(8, OUTPUT);
               //pinMode(9, OUTPUT);

               digitalWrite(13, LOW);  // turn LED_BUILTIN on (when the central disconnects, turn off the LED)
               //digitalWrite(5, HIGH);           // turn LED1 off
               //digitalWrite(6, HIGH);           // turn LED2 off
               //digitalWrite(7, HIGH);           // turn LED3 off
               //digitalWrite(8, HIGH);           // turn LED4 off
               //digitalWrite(9, HIGH);           // turn LED5 off

               // begin initialization
               if (!BLE.begin()) {
                 Serial.println("starting BLE device failed!");

                 while (1);
               }

               // set advertised local name and service UUID:
               BLE.setLocalName("CH Farrukh");
               BLE.setAdvertisedService(ledService);

               // add the characteristic to the service
               ledService.addCharacteristic(switchCharacteristic);

               // add service
               BLE.addService(ledService);

               // set the initial value for the characeristic:
               switchCharacteristic.writeValue(0);

               // start advertising
               BLE.advertise();

               Serial.println("BLE device Nano_33 active, waiting for connection");
}

void loop()
{
  // listen for BLE peripherals to connect:
  BLEDevice central = BLE.central();

               // if a central is connected to peripheral:
               if (central)
               {
                         Serial.print("Connected to central: ");
                         // print the central's MAC address:
                         Serial.println(central.address());

                         // while the central is still connected to peripheral:
                         while (central.connected())
                         {
                                   // if the remote device wrote to the characteristic,
                                   // use the value to control the LED:

                                   // Additional test 
                                   Serial.print("Value Received: ");
                                   Serial.println(switchCharacteristic.value());
                                   
                                   if (switchCharacteristic.written())
                                   {
                                             Serial.print("Value Received: ");
                                             Serial.println(switchCharacteristic.value()); //Check that the value received is valid

                                             switch (switchCharacteristic.value())
                                             {
                                               case 1:
                                                 Serial.println("LED 1 on");
                                                 digitalWrite(13, HIGH);
                                                 break;
                                               case 2:
                                                 Serial.println("LED 2 on");
                                                 digitalWrite(6, LOW);
                                                 break;
                                               case 3:
                                                 Serial.println("LED 3 on");
                                                 digitalWrite(7, LOW);
                                                 break;
                                               case 4:
                                                 Serial.println("LED 4 on");
                                                 digitalWrite(8, LOW);
                                                 break;
                                               case 5:
                                                 Serial.println("LED 5 on");
                                                 digitalWrite(9, LOW);
                                                 break;
                                               case 6:
                                                 Serial.println("LED 1 off");
                                                 digitalWrite(13, LOW);
                                                 break;
                                               case 7:
                                                 Serial.println("LED 2 off");
                                                 digitalWrite(6, HIGH);
                                                 break;
                                               case 8:
                                                 Serial.println("LED 3 off");
                                                 digitalWrite(7, HIGH);
                                                 break;
                                               case 9:
                                                 Serial.println("LED 4 off");
                                                 digitalWrite(8, HIGH);
                                                 break;
                                               case 10:
                                                 Serial.println("LED 5 off");
                                                 digitalWrite(9, HIGH);
                                                 break;
                                             }
                                   }
                         }

                         // when the central disconnects, print it out:
                         Serial.print("Disconnected from central: ");
                         Serial.println(central.address());
                         //digitalWrite(LED_BUILTIN, HIGH);  // when the central disconnects, turn off the LED
                         //digitalWrite(5, HIGH);
                         //digitalWrite(6, HIGH);
                         //digitalWrite(7, HIGH);
                         //digitalWrite(8, HIGH);
                         //digitalWrite(9, HIGH);
               }
}