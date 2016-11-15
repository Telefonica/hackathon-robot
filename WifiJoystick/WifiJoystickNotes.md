Wifi Joystick.
----------------------------------
Wireless Joystick that allows us to control the orientation of a remote camera, or telepresence robot remotely using a Wifi network.

  Joystick                        UDP Server                           Arduino
                                                                                              ___
    [=]                             --------                           -------     Servo      | |---
     |             UDP              |    º |         Serial           // º º//  ------------  ¯¯¯
   -----      ------------->        |      |     --------------->    // º º//   ------------  ___
   |   |      Communication         |      |      Communication     /------/      Motors      | |---
   -----                            --------                                                  ¯¯¯

Architecture:
------------------
Joystick:
NodeMCU board with ESP8266 Microcontroller. (Wifi integrated)
Analog Joystick module with 2 axis and a push button.
Analog to Digital converter. I2C
Powerbank.

Server:
Node Js server that accept UDP packages and send messages to an arduino using serial communication.

Camera Platform:
 Arduino device. (Arduino UNO or Arduino Nano board.)
 Two servo motors SG90. From 0º to 180º.

Main Repository:
------------------
https://github.com/Telefonica/hackathon-robot

Folders:
-----------------
https://github.com/Telefonica/hackathon-robot/cameraControl
https://github.com/Telefonica/hackathon-robot/WifiJoystick
