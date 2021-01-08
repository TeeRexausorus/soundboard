#include <Keyboard.h>

#define btns A0
int val = 0;
int prevAnalogVal = 0;
char prevVal = ' ';
char currentVal = ' ';

double lastTimeCall = millis();

// La taille du tampon pour le lissage des valeurs lues
const int numReadings = 20;

int readings[numReadings];      // le tampon pour le lissage des valeurs lues
int readIndex = 0;              // L'index de la lecture courante
int total = 0;                  // La somme des valeurs lues
int average = 0;                // La moyenne des valeurs lues
bool skipped = false;           // Un booléen pour

void setup() {
  Serial.begin(9600);
  // On met toutes les valeurs à 0
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }
}

void loop() {
  analogVal = analogRead(btns);

  //on remet la valeur moyennée à 0
  val = 0
  // Si la valeur est inférieure à un seuil arbitraire, on met un délais et on saute le traitement
  if (analogVal < 25){
    delay(200);
  }

  for (int i = 0; i < numReadings; ++i){
    // On soustrait la valeur lue dans la "case" du tampon qu'on va remplir
    total = total - readings[readIndex]
    readings[readIndex] = analogVal;
    // On ajoute la valeur lue au total
    total = total + readings[readIndex];
    // On passe à la case suivante
    readIndex++;
    // On retourne au début du tableau si on en a atteint la fin
    if (readIndex >= numReadings) {
      readIndex = 0;
    }
  }
  // On calcule la moyenne:
  average = total / numReadings;
  val = average;

  //Pour tout l'enchaînement à suivre, on affecte une lettre à une variable
  if (val >= 732 && val <= 740){
    currentVal = 'Q';
  }
  else if (val >= 786 && val <= 793){
    currentVal = 'B';
  }
  else if (val >= 837 && val <= 843){
    currentVal = 'C';
  }
  else if (val >= 630 && val <= 640){
    currentVal = 'D';
  }
  else if (val >= 536 && val <= 545){
    currentVal = 'E';
  }
  else if (val >= 674 && val <= 681){
    currentVal = 'F';
  }
  else if (val >= 650 && val <= 660){
    currentVal = 'G';
  }
  else if (val >= 610 && val <= 620){
    currentVal = 'H';
  }
  else if (val > 580 && val <= 590){
    currentVal = 'I';
  }
  else if (val >= 690 && val <= 720){
    currentVal = 'J';
  }
  else if (val >= 550 && val <= 561){
    currentVal = 'K';
  }
  else if (val >= 850 && val <= 870){
    currentVal = 'L';
  }
  else{
    Serial.println(average);
  }

  // Si currentVal est rempli, et qu'il n'a pas déjà été pressé dans la demi-seconde qui précède
  if(currentVal != ' ' && prevVal != currentVal && (millis() - lastTimeCall > 500) && skipped){

    // On peut changer ici les touches du clavier pressées, voir https://www.arduino.cc/reference/en/language/functions/usb/keyboard/keyboardmodifiers/
    // pour la liste des modificateurs disponibles (KEY_F13 à KEY_F24 peuvent être intéressants à exploiter :) )

    // On  presse les touches puis on les relâche
    Keyboard.press(KEY_LEFT_GUI);
    Keyboard.press(KEY_LEFT_ALT);
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press(currentVal);
    Keyboard.releaseAll();

    // On sauvegarde la valeur envoyée, ainsi que la dernière fois qu'on a envoyé une combinaison de touches
    // Pour ne pas spammer la dite combinaison
    prevVal = currentVal;
    currentVal = ' ';
    lastTimeCall = millis();
    skipped = !skipped;


    delay(200);
  } else if (!skipped) {
    skipped = !skipped;
  }
  // on réinitialise les valeurs pour pouvoir rappeler le même bouton à la suite
  if (millis() - lastTimeCall > 1000){
    currentVal = ' ';
    prevVal = ' ';
  }
}