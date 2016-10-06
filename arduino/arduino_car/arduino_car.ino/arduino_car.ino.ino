//motor A connected between A01 and A02
//motor B connected between B01 and B02

int STBY = 10; //standby

//Motor A
int PWMA = 3; //Speed control 
int AIN1 = 9; //Direction
int AIN2 = 8; //Direction

//Motor B
int PWMB = 5; //Speed control
int BIN1 = 11; //Direction
int BIN2 = 12; //Direction
unsigned long lastActionTs = millis();
const int STOP = 0;
const int RIGHT = 3;
const int LEFT = 2;
const int FORWARD = 1;
const int BACKWARD = 4;

int current_action = STOP;

void setup(){
  Serial.begin(9600);
  pinMode(STBY, OUTPUT);

  pinMode(PWMA, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);

  pinMode(PWMB, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
}


void turn_left(){
  current_action = LEFT;
  move(2, 0, 1);
  move(1, 255, 1);
}

void turn_right(){
  current_action = RIGHT;
  move(1, 0, 1);
  move(2, 255, 1);
}


void go_forward(){
  if (current_action == FORWARD){
    return;
  }
   if (current_action == BACKWARD){
      for (int i=255;i<=0;i--){
        delay(5);
        move(1, i, 0);
        move(2, i, 0);
      }
   }
  current_action = FORWARD;
  for (int i=0;i<=255;i++){
    delay(5);
    move(1, i, 1);
    move(2, i, 1);
  }
}


void go_backward(){
  if (current_action == BACKWARD){
    return;
  }
   if (current_action == FORWARD){
      for (int i=255;i<=0;i--){
        delay(5);
        move(1, i, 1);
        move(2, i, 1);
      }
   }
  current_action = BACKWARD;  
  for (int i=0;i<=255;i++){
    delay(5);
    move(1, i, 0);
    move(2, i, 0);
  }
}

void stop_car(){
  stop();
  current_action = STOP;
}

void loop(){

    
  if (Serial.available() > 0) {
      lastActionTs = millis();
      int action = Serial.read();
          
      switch(action) {
        case STOP:
        case STOP + 48:
          stop_car();
          break;
        case LEFT:
        case LEFT + 48:
          turn_left();
          break;
        case RIGHT:
        case RIGHT + 48:
          turn_right();
          break;
        case FORWARD:
        case FORWARD + 48:
          go_forward();
          break;
        case BACKWARD:
        case BACKWARD + 48:
          go_backward();
          break;   
      }
      Serial.println(action);
//      delay(1000);        // delay in between reads for stability
    } else if (lastActionTs + 300 < millis()) {
      stop_car();
      lastActionTs = millis();
      Serial.println("STOP");
    }

  
}


void move(int motor, int speed, int direction){
//Move specific motor at speed and direction
//motor: 0 for B 1 for A
//speed: 0 is off, and 255 is full speed
//direction: 0 clockwise, 1 counter-clockwise

  digitalWrite(STBY, HIGH); //disable standby

  boolean inPin1 = LOW;
  boolean inPin2 = HIGH;

  if(direction == 1){
    inPin1 = HIGH;
    inPin2 = LOW;
  }

  if(motor == 1){
    digitalWrite(AIN1, inPin1);
    digitalWrite(AIN2, inPin2);
    analogWrite(PWMA, speed);
  }else{
    digitalWrite(BIN1, inPin1);
    digitalWrite(BIN2, inPin2);
    analogWrite(PWMB, speed);
  }
}

void stop(){
//enable standby  
  digitalWrite(STBY, LOW); 
}
 
