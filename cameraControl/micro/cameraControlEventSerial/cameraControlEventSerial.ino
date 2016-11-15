
#include <Servo.h>

String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete
Servo servoX;
Servo servoY;
int posX = 0;
int posY = 0;

void setup() {
  // initialize serial:
  Serial.begin(115200);
  // reserve 200 bytes for the inputString:
  inputString.reserve(20);
  servoX.attach(5);
  servoX.write(posX);
  servoY.attach(6);
  servoY.write(posY);
}

void loop() {
  // print the string when a newline arrives:
  if (stringComplete) {
    //Serial.println(inputString);
    Serial.print("posiciones: ");
    Serial.print(posY);
    Serial.print(" -- ");
    Serial.println(posX);
    // clear the string:
    inputString = "";
    stringComplete = false;
  }
}

/*
  SerialEvent occurs whenever a new data comes in the
  hardware serial RX.  This routine is run between each
  time loop() runs, so using delay inside loop can delay
  response.  Multiple bytes of data may be available.
*/
void serialEvent() {
  Serial.println("Entra");
  while(Serial.available()) {
    Serial.println("Entra2");
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString  :
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      Serial.println("fin de linea");
      //Serial.println(inputString);
      //int intValue = inputString.toInt();
      //posX = posX + intValue;
      //servoX.write(posX);
      char *inputChar = new char[inputString.length() + 1];
      strcpy(inputChar, inputString.c_str());
      char *axisX = strtok(inputChar, ",");
      char *axisY = strtok(NULL, ",");


      char *axisXPrefix = strtok(axisX, ":");
      //Serial.println(axis);
      char *axisXValue = strtok(NULL, ":");

      char *axisYPrefix = strtok(axisY, ":");
      //Serial.println(axis);
      char *axisYValue = strtok(NULL, ":");

      int intValueX = atoi(axisXValue);
      int intValueY = atoi(axisYValue);
      if (intValueX >= -3 && intValueX <= 3) {
        if (posX + intValueX > 180) {
          posX = 180;
        }
        else if (posX + intValueX <= 0) {
          posX = 0;
        }
        else {
          posX += intValueX;
        }
        servoX.write(posX);
      }

      if (intValueY >= -3 && intValueY <= 3) {
        if (posY + intValueY > 180) {
          posY = 180;
        }
        else if (posY + intValueY <= 0) {
          posY = 0;
        }
        else {
          posY += intValueY;
        }
        servoY.write(posY);
      }
    }
    stringComplete = true;
  }

}
