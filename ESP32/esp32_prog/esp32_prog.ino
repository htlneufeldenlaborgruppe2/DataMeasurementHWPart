#include "paulvha_SCD30.h"
#define scd_debug 0

/* Put your SSID & Password */
const char* ssid = "raspi";  // Enter SSID here
const char* password = "20raspi19!";  //Enter Password here

int measurePin = 15;  //io26
int ledPower = 35;    
int noisePin = 16;//enter input pin
//int reedPin = 27;

int sensorPinLDR = 13; // select the input pin for LDR

int sensorValueLDR = 0; // variable to store the value coming from the sensor


unsigned int samplingTime = 280;
unsigned int deltaTime = 40;
unsigned int sleepTime = 9600;
unsigned int counterMulti = 0;
unsigned int counterDust = 0;
unsigned int counterLDR = 0;
unsigned int counterNoise = 0;

//unsigned int countDoor = 0;
//unsigned int reedTemp = 1;

double voMeasured = 0;
double calcVoltage = 0;
double dustDensity = 0;
double dustTemp = 0;
double noiseValue = 0;
double noiseValueTemp = 0;
double maxNoise = 0;
double minNoise = 1000000;
double milliseconds = millis();

float co2=0;
float temp=0;
float humidity=0;

String noiseAllValues = "";

double interruptCount=0;

/* Put IP Address details */
bool req = true;
SCD30 airSensor;



void setup() {
  Serial.begin(115200);
setup_dust();
setup_co2_hum_temp(); 
}
void loop() {
  if(millis() - milliseconds > 500) {
  loop_co2_hum_temp();
  measure_dust();
  measure_ldr();
  measure_noise();
  milliseconds = millis();
  }
  //reed();

  if(Serial.readString()!=""){


   if(counterDust>0 && counterLDR>0 && counterMulti > 0 && counterNoise>0){
      Serial.println("dust:" + String(dustTemp/counterDust)+
      ";ldr:"+String(sensorValueLDR/counterLDR)+
      ";humidity:"+String(humidity/counterMulti)+
      ";co2:"+String(co2/counterMulti)+
      ";temp:"+String(temp/counterMulti)+
      ";noise:"+String(noiseValue/counterNoise)+
      ";noisemin:"+String(minNoise)+
      ";noisemax:"+String(maxNoise)+
     ";noisevalues:"+noiseAllValues);
      
      resetAll();
   }     
        
      } 
}

void resetAll() {
  dustTemp = 0;
  counterDust = 0;
  sensorValueLDR = 0;
  counterLDR = 0;
  humidity = 0;
  co2 = 0;
  temp = 0;
  counterMulti = 0;
  noiseValue = 0;
  counterNoise = 0;
  noiseAllValues="";
}

void measure_noise() {
  counterNoise = counterNoise +1;
  float noiseTemp = analogRead(noisePin);
  if(noiseTemp > maxNoise){
      maxNoise = noiseTemp;
    }
  else if(noiseTemp < minNoise) {
      minNoise = noiseTemp;
    }
  noiseValue = noiseValue + noiseTemp;
  //noiseAllValues = noiseAllValues + String(noiseTemp) + "_";
}

void measure_ldr() {
  counterLDR = counterLDR + 1;
  float valueRead=analogRead(sensorPinLDR);
  sensorValueLDR= sensorValueLDR - (1.2759 * valueRead) + 1286.7;
}

void measure_dust(){
  counterDust = counterDust + 1;
    digitalWrite(ledPower,LOW);
  delayMicroseconds(samplingTime);

  voMeasured = analogRead(measurePin);

  delayMicroseconds(deltaTime);
  digitalWrite(ledPower,HIGH);
  delayMicroseconds(sleepTime);

  calcVoltage = voMeasured*(5000/1024);
  dustDensity = 0.17*calcVoltage-0.1;

  if ( dustDensity < 0)
  {
    dustDensity = 0.00;
  } 
  dustTemp = dustTemp + dustDensity;
}

/*void resetDoor() {
  countDoor = 0;
}*/

void setup_dust(){
    pinMode(ledPower, OUTPUT);
  digitalWrite(ledPower,HIGH);
}

/*void setup_reed() {
    pinMode (reedPin, INPUT);
}*/

void setup_co2_hum_temp(){
  Wire.begin();
  airSensor.setDebug(scd_debug);

  airSensor.begin(Wire); //This will cause readings to occur every two seconds
}

/*void reed() {
  int reed_input;

  reed_input = digitalRead (reedPin);

  if(reed_input == 0 && reedTemp == 1) {
      countDoor = countDoor + 1;
  }
  reedTemp = reed_input;
}*/

void loop_co2_hum_temp(){
  if (airSensor.dataAvailable())
  {
    counterMulti = counterMulti +1;
    //Serial.print("co2(ppm):");
    co2=co2 + airSensor.getCO2();
    //Serial.print(co2);

    //Serial.print(" temp(C):");
    temp=temp + airSensor.getTemperature();
    //Serial.println(temp);

    //Serial.print(" humidity(%):");
    humidity=humidity + airSensor.getHumidity();
    //Serial.println(humidity);

    //Serial.println();
  }
}
