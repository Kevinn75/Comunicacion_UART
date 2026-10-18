#include <Arduino.h>

int Estado = 0;
long maxValue = 0;
long minValue = 0;
long secretValue = 0;

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("--- Iniciando Juego de Adivinanza ---");
  Serial.println("Escoja el valor minimo:");

  randomSeed(analogRead(36));
}

void loop() {
  if (Serial.available() > 0) {
    long NumInt = Serial.parseInt();

    // Limpiar el buffer de caracteres residuales (\n, \r)
    while (Serial.available() > 0) {
      Serial.read();
    }

    switch (Estado) {
      case 0:
        minValue = NumInt;
        Serial.print("Valor minimo seleccionado: ");
        Serial.println(minValue);
        Serial.println("Ingrese el valor maximo para adivinar:");
        Estado = 1;
        break;

      case 1:
        maxValue = NumInt;
        if (maxValue <= minValue) {
          Serial.println("El valor ingresado es menor o igual al limite inferior, por favor intente otra vez:");
        } else {
          Serial.print("Valor maximo seleccionado: ");
          Serial.println(maxValue);

          secretValue = random(minValue, maxValue + 1);

          Serial.println("\n¡El juego ha iniciado! Realiza tu primer intento:");
          Estado = 2;
        }
        break;

      case 2:
        Serial.print("Tu intento: ");
        Serial.println(NumInt);

        if (NumInt < secretValue) {
          Serial.println("El numero secreto es MAYOR que el que introdujiste...");
        } 
        else if (NumInt > secretValue) {
          Serial.println("El numero secreto es MENOR que el que introdujiste...");
        } 
        else {
          Serial.println("\n¡EXCELENTE! ¡Adivinaste el numero!");
          Serial.println("-----------------------------------");
          Serial.println("Vamos a jugar de nuevo. Ingrese un nuevo valor MINIMO:");
          
          Estado = 0; 
        }
        break;
    }
  }
}