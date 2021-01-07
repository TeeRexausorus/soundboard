#include <Keyboard.h>

#define btns A0
int val = 0;
int prevAnalogVal = 0;
char prevVal = ' ';
char lastVal = ' ';

double lastTimeCall = millis();

// value to determine the size of the readings array.
const int numReadings = 20;

int readings[numReadings];      // the readings from the analog input
int readIndex = 0;              // the index of the current reading
int total = 0;                  // the running total
int average = 0;                // the average
bool skipped = false;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  // initialize all the readings to 0:
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }
}

void loop() {
  // We tempo a bit to avoid wrong average
  if (prevAnalogVal < 25){
    delay(200);
  }
  int valTmp = 0;
  for (int i = 0; i < numReadings; ++i){
    // subtract the last reading:
    total = total - readings[readIndex];
    // read from the sensor:
    valTmp = analogRead(btns);
    readings[readIndex] = valTmp;
    // add the reading to the total:
    total = total + readings[readIndex];
    // advance to the next position in the array:
    readIndex = (readIndex + 1) % numReadings;
    // if we're at the end of the array...
    if (readIndex >= numReadings) {
      // ...wrap around to the beginning:
      readIndex = 0;
    }
  }
  // calculate the average:
  average = total / numReadings;
  // send it to the computer as ASCII digits
  // Serial.println(average);

  val = average;
  
  if (val >= 732 && val <= 740){
    lastVal = 'Q';
  }
  else if (val >= 786 && val <= 793){
    lastVal = 'B';
  }
  else if (val >= 837 && val <= 843){
    lastVal = 'C';
  }
  else if (val >= 630 && val <= 640){
    lastVal = 'D';
  }
  else if (val >= 536 && val <= 545){
    lastVal = 'E';
  }
  else if (val >= 674 && val <= 681){
    lastVal = 'F';
  }
  else if (val >= 650 && val <= 660){
    lastVal = 'G';
  }
  else if (val >= 610 && val <= 620){
    lastVal = 'H';
  }
  else if (val > 580 && val <= 590){
    lastVal = 'I';
  }
  else if (val >= 690 && val <= 720){
    lastVal = 'J';
  }
  else if (val >= 550 && val <= 561){
    lastVal = 'K';
  }
  else if (val >= 850 && val <= 870){
    lastVal = 'L';
  }
  else{
    Serial.println(average);
  }
  
  if(lastVal != ' ' && prevVal != lastVal && (millis() - lastTimeCall > 500) && skipped){
    Serial.println(lastVal);
    //*
    Keyboard.press(KEY_LEFT_GUI);
    Keyboard.press(KEY_LEFT_ALT);
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press(lastVal);
    Keyboard.releaseAll();//*/
    prevVal = lastVal;
    lastVal = ' ';
    lastTimeCall = millis();
    skipped = !skipped;
    delay(200);
  } else if (!skipped) {
    skipped = !skipped;
  }
  if (millis() - lastTimeCall > 1000){
    lastVal = ' ';
    prevVal = ' ';
  }
  prevAnalogVal = analogRead(btns);
}
