// LCD
#include <Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd;

const int colorR = 70;
const int colorG = 226;
const int colorB = 70;
// LCD

//Se define el sensor de humedad en el pin A0
#define sensorH1 A0
//Se define el relay que estara conectado a la bomba de agua en el pin 2
#define relay1 2
 
void setup(){
  //Se declara el sensor de humedad como entrada de señal  
  pinMode(sensorH1, INPUT);
  //Se declara el relay como salida de señal  
  pinMode(relay1, OUTPUT);
  //Abre el puerto serie y fija la velocidad en baudios para la transmisión de datos en serie.   
  Serial.begin(9600);

  // LCD
  lcd.begin(16,2);
  lcd.setRGB(colorR, colorG, colorB);
}

void loop(){
  //Se hace la lectura analoga del pin A0 (sensorH1) y se pasa por la funcion map() para ajustar los 
  //valores leidos a los porcentajes que queremos utilizar   
  int valorHumedad1 = map(analogRead(sensorH1), 0, 1023, 100, 0);
  //Se utiliza para imprimir la Humedad en el monitor  
  
  Serial.print("Humedad: ");
  Serial.print(valorHumedad1);
  Serial.println("%");
  
  // LCD
  lcd.clear();
  lcd.write("Humedad: ");
  lcd.print(valorHumedad1);
  lcd.write("%");
  delay(1000);
  // LCD
  
  //En este if realizamos una verificacion de la humedad para añadirle agua a la planta
  //si la planta tiene una humedad menor a 75%.  
  if (valorHumedad1 <= 75){
    //Se manda una señal para que prenda el relay y mande el agua.
    digitalWrite(relay1,1);
    lcd.clear();
    lcd.write("Bomba encendida!");
    delay(10000);
    lcd.clear();
    digitalWrite(relay1,0);
  }
  else{
    //Se manda la señal de apagar el relay para que detenga el agua.    
    digitalWrite(relay1,0);
  }

  
}
