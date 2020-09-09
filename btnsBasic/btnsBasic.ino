#include <Keyboard.h>

#define btns A0
int val = 0;
// char ctrlKey = Keyboard.KEY_LEFT_GUI;
char prevVal = ' ';
char lastVal = ' ';
double lastTimeCall = millis();
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  val = analogRead(btns);
  int avg;
  for(int j = 0; j < 2; j++){
    avg = 0;
    for (int i = 0; i < 10; i++){
      avg += val;
    }
  }
  
  avg /= 10;
  val = avg;
  if (val >= 734 && val <= 740){
    lastVal = 'A';
  }
  else if (val >= 786 && val <= 790){
    lastVal = 'B';
  }
  else if (val >= 837 && val <= 843){
    lastVal = 'C';
  }
  else if (val >= 630 && val <= 640){
    lastVal = 'D';
  }
  else if (val >= 537 && val <= 545){
    lastVal = 'E';
  }
  else if (val >= 675 && val <= 680){
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
  else if (val >= 710 && val <= 720){
    lastVal = 'J';
  }
  else if (val >= 550 && val <= 560){
    lastVal = 'K';
  }
  else if (val >= 860 && val <= 870){
    lastVal = 'L';
  }
  else{
    Serial.println(val);
  }
  if(lastVal != ' ' && prevVal != lastVal && (millis() - lastTimeCall > 500)){
    Serial.println(lastVal);
    Keyboard.press(Keyboard.KEY_LEFT_GUI);
    // Keyboard.press(lastVal);
    
    prevVal = lastVal;
    lastVal = ' ';
    lastTimeCall = millis();
  }
  if (millis() - lastTimeCall > 1000){
    lastVal = ' ';
    prevVal = ' ';
  }
  
}
