//#include "menus.h"

#include "Header.h"
#include <LiquidCrystal_I2C.h>
#include <DS1337RTC.h>
#include <Time.h>
#include <Wire.h>

//-----------------------------------------------------
//---			definiciones para el menu			---
//-----------------------------------------------------



#define alarmPin 12

LiquidCrystal_I2C lcd(0X27,16,2);

char *monthName[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
char botonPulsado = '0';

void setup(){
	pinMode(led,OUTPUT);		//led como salida
	digitalWrite(led,HIGH);

	pinMode(btnUp,INPUT);
	pinMode(btnDown,INPUT);
	pinMode(btnOk,INPUT);
	pinMode(btnC,INPUT);	

	pinMode(alarmPin, INPUT);
	digitalWrite(alarmPin,HIGH);		//??????

	Serial.begin(9600);
	lcd.begin();
	lcd.print("iniciado reloj");
	delay(500);
	

}
  
void loop(){
	
	botonPulsado = leerTeclado();

		if (botonPulsado != '0')
		{
			Serial.println((String)"Tecla pulsada: " + botonPulsado);
			//añadir accion aqui
			botonPulsado = '0';
		}


	else {}
	
	//leerHora();
		
	delay(250);


}




