hackaton-robot
==

A telepresence robot built in hours in Telefónica I+D. See [video on vimeo](https://vimeo.com/186282783)

Technologies used:
* [Tokbox](https://tokbox.com/) for live video.
* Arduino to control DC motors.
* Raspberry Pi running a nodejs server that exposes a http endpoint to control the robot and sends orders to the Arduino using serial USB.

Evolving the robot
--

* Version 2 with [3d printed](./3DParts) shock absorbers: https://youtu.be/JkA4-V8ke-c
