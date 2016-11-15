#include <Servo.h>

Servo servoX;  // create servo object to control a servo
Servo servoY;  // create servo object to control a servo

int posX = 0;    // variable to store the servo position
int posY = 0;    // variable to store the servo position

void setup() {
  servoX.attach(5);  // attaches the servo on pin 9 to the servo object
  servoY.attach(6);  // attaches the servo on pin 9 to the servo object
  Serial.begin(9600);
  servoX.write(posX);
  servoY.write(posY);
}

void loop() {
  if (Serial.available() > 0) {
    String input = Serial.readString();
    char *inputChar = new char[input.length() + 1];
    strcpy(inputChar, input.c_str());
    char *axis = strtok(inputChar, ":");
    //Serial.println(axis);
    char *value = strtok(NULL, ":");
    //Serial.println(value);
    //cast value to integer
    int intValue = atoi(value);

    if (strcmp(axis, "x") == 0) {
      //Serial.println("eje x");
      if (posX + intValue > 180) {
        posX = 180;
      }
      else {
        posX += intValue;
      }
    }
    else {
      if (strcmp(axis, "y") == 0) {
        //Serial.println("eje y");
        if (posY + intValue > 180) {
          posY = 180;
        }
        else {
          posY += intValue;
        }
      }
      else {
        //Serial.println("Eje erroneo");
      }
    }
    servoX.write(posX);              // tell servo to go to position in variable 'pos'
    servoY.write(posY);              // tell servo to go to position in variable 'pos'
  }
}
