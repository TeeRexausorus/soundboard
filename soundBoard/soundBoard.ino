#include <Keyboard.h>
#include "confButtons.h"

#define btns A0
int val = 0;
int analogVal = 0;
char prevVal = ' ';
char currentVal = ' ';

double lastTimeCall = millis();

// La taille du tampon pour le lissage des valeurs lues
const int numReadings = 20;

int readings[numReadings];      // le tampon pour le lissage des valeurs lues
int readIndex = 0;              // L'index de la lecture courante
int total = 0;                  // La somme des valeurs lues
int average = 0;                // La moyenne des valeurs lues

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
  val = 0;
  // Si la valeur est inférieure à un seuil arbitraire, on met un délais et on saute le traitement
  if (analogVal < 25){
    delay(100);
  }

  for (int i = 0; i < numReadings; ++i){
    // On soustrait la valeur lue dans la "case" du tampon qu'on va remplir
    total = total - readings[readIndex];
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
  val = total / numReadings;

  //Pour tout l'enchaînement à suivre, on affecte une touche à une variable
  if (val >= key01min && val <= key01max){
    currentVal = 0xF0; // KEY_F13
  }
  else if (val >= key02min && val <= key02max){
    currentVal = 0xF1; // KEY_F14
  }
  else if (val >= key03min && val <= key03max){
    currentVal = 0xF2; // KEY_F15
  }
  else if (val >= key04min && val <= key04max){
    currentVal = 0xF3; // KEY_F16
  }
  else if (val >= key05min && val <= key05max){
    currentVal = 0xF4; // KEY_F17
  }
  else if (val >= key06min && val <= key06max){
    currentVal = 0xF5; // KEY_F18
  }
  else if (val >= key07min && val <= key07max){
    currentVal = 0xF6; // KEY_F19
  }
  else if (val >= key08min && val <= key08max){
    currentVal = 0xF7; // KEY_F20
  }
  else if (val > key09min && val <= key09max){
    currentVal = 0xF8; // KEY_F21
  }
  else if (val >= key10min && val <= key10max){
    currentVal = 0xF9; // KEY_F22
  }
  else if (val >= key11min && val <= key11max){
    currentVal = 0xFA; // KEY_F23
  }
  else if (val >= key12min && val <= key12max){
    currentVal = 0xFB; // KEY_F24
  }
  else{
    Serial.println(average);
  }

  // Si currentVal est rempli, et qu'il n'a pas déjà été pressé dans la demi-seconde qui précède
  if(currentVal != ' ' && prevVal != currentVal && (millis() - lastTimeCall > 500)){

    // On peut changer ici les touches du clavier pressées, voir https://www.arduino.cc/reference/en/language/functions/usb/keyboard/keyboardmodifiers/
    // pour la liste des modificateurs disponibles (KEY_F13 à KEY_F24 peuvent être intéressants à exploiter :) )

    // On  presse les touches puis on les relâche
    Keyboard.press(KEY_LEFT_SHIFT);
    Keyboard.press(currentVal);
    delay(50);
    Keyboard.releaseAll();

    // On sauvegarde la valeur envoyée, ainsi que la dernière fois qu'on a envoyé une combinaison de touches
    // Pour ne pas spammer la dite combinaison
    prevVal = currentVal;
    currentVal = ' ';
    lastTimeCall = millis();


  }
  // on réinitialise les valeurs pour pouvoir rappeler le même bouton à la suite
  if (millis() - lastTimeCall > 10){
    currentVal = ' ';
    prevVal = ' ';
  }
}
