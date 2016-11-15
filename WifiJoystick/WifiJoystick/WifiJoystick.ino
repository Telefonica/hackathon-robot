#include <ESP8266WiFi.h>
#include <Wire.h>
#include <Adafruit_ADS1015.h>
#include <WiFiUDP.h>


Adafruit_ADS1115 ads;

int clickKey = D3;

const char* ssid = "Walqa-Guest";
const char* password = "walqa2016";
boolean wifiConnected = false;

int udpPort = 3000;
const char* udpHost = "192.168.140.49";
WiFiUDP UDP;

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println();
  Serial.print("Running:");
  // put your setup code here, to run once:
  ads.setGain(GAIN_ONE);        // 1x gain   +/- 4.096V  1 bit = 2mV      0.125mV
  ads.begin();
  pinMode(clickKey, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected Walqa-Guest");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  digitalWrite(LED_BUILTIN, LOW);
}

int remap(int adcValue) {
  if (adcValue >= -2 && adcValue <=2 ) {
    return 0;
  }
  else if (adcValue >= -6 && adcValue <=-3 ) {
    return -1;
  }
  else if (adcValue >= -10 && adcValue <=-7 ) {
    return -2;
  }
  else if (adcValue >= -15 && adcValue <=-11 ) {
    return -3;
  }
  else if (adcValue >= 3 && adcValue <=6 ) {
    return 1;
  }
  else if (adcValue >= 7 && adcValue <=11 ) {
    return 2;
  }
  else if (adcValue >= 11 && adcValue <=15 ) {
    return 3;
  }
}

int inverse(int key) {
  if (key == HIGH) {
    return 0;
  }
  return 1;
}

unsigned char udpSend( char * msg)
{ 
  UDP.beginPacket(udpHost, udpPort);
  Serial.println(msg);
  UDP.write(msg);
  return UDP.endPacket();
}

void loop() {
  int16_t adc0, adc1;
  adc0 = ads.readADC_SingleEnded(0);
  adc1 = ads.readADC_SingleEnded(1);
  int adc0x = 0;
  int adc1y = 0;
  adc0x = map(adc0, 13, 24926, -14, 14);
  adc1y = map(adc1, 24, 25894, -14, 14);

  int clickStatus =  digitalRead(clickKey);
  int remapedX = remap(adc0x);
  int remapedY = remap(adc1y);
  int remapedClick = inverse(clickStatus);
  Serial.print("AIN0: "); Serial.println(remapedX);
  Serial.print("AIN1: "); Serial.println(remapedY);
  Serial.print("Click: "); Serial.println(remapedClick);
  delay(150);
  if (remapedX == 0 && remapedY == 0 && remapedClick == 0) {
    Serial.print("No action");
  } else {
    String str = "x:"+ String(remapedX, DEC) + ",y:"+String(remapedY, DEC)+",k:"+ String(remapedClick, DEC);
    int str_len = str.length() + 1;
    char char_array[str_len];
  
    // Copy it over 
    str.toCharArray(char_array, str_len); 
    udpSend(char_array);
  }

}
