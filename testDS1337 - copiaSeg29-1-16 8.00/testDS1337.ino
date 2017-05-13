//#include "menus.h"

#include "Header.h"
#include <LiquidCrystal_I2C.h>
#include <DS1337RTC.h>
#include <Time.h>
#include <Wire.h>

//-----------------------------------------------------
//---			definiciones para el menu			---
//-----------------------------------------------------
int menuPosicionActualX = 0;
int menuPosicionActualY = 0;

const int menuTamanoMatrizX = 6;
const int menuTamanoMatrizY = 4;
const int menuLineasLCD = 2;

int submenuLongitud [4]={0,5,3,6};

//	  menuLista [z][y][x]
String menuLista[menuLineasLCD][menuTamanoMatrizY][menuTamanoMatrizX] = 
				{
					{	//linea 1 del lcd
						{"L1 - Menu 0.0","a","b","c","d","e"},
						{"L1 - Menu 1.0","L1 - Menu 1.1","L1 - Menu 1.2","L1 - Menu 1.3","L1 - Menu 1.4" , "L1 - Menu 1.5"},
						{"L1 - Menu 2.0","L1 - Menu 2.1","L1 - Menu 2.2","L1 - Menu 2.3","L1 - Menu 2.4" , "L1 - Menu 2.5"},
						{"L1 - Menu 3.0","L1 - Menu 3.1","L1 - Menu 3.2","L1 - Menu 3.3","L1 - Menu 3.4" , "L1 - Menu 3.5"}
					},
					{	//linea 2 del lcd
						{"L2 - Menu 0.0" , "" , "" , "" , "" , ""},
						{"L2 - Menu 1.0" , "L2 - Menu 1.1" , "L2 - Menu 1.2" , "L2 - Menu 1.3" , "L2 - Menu 1.4" , "L2 - Menu 1.5"},
						{"L2 - Menu 2.0" , "L2 - Menu 2.1" , "L2 - Menu 2.2" , "L2 - Menu 2.3" , "L2 - Menu 2.4" , "L2 - Menu 2.5"},
						{"L2 - Menu 3.0" , "L2 - Menu 3.1" , "L2 - Menu 3.2" , "L2 - Menu 3.3" , "L2 - Menu 3.4" , "L2 - Menu 3.5"}
					}
				};


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
	menuActualizar();

}
  
void loop(){
	
	botonPulsado = leerTeclado();

		if (botonPulsado != '0')
		{
			Serial.println((String)"Tecla pulsada: " + botonPulsado);
			actualizarMenu(botonPulsado);
		
			botonPulsado = '0';
		}


	else {}
	
	//leerHora();
		
	delay(250);


}

void actualizarMenu(char teclaPulsada)
{
	if(teclaPulsada== 'd')					//si pulsamos abajo
	{
		if(menuPosicionActualY==0)			//y si estamos en el menu X.0
		{ 
			Serial.println("Y=0  -->  x++");
			menuPosicionActualX++; 
		}		//pasamos al menu (X+1).0
		else								//o si estamos en un submenu
		{
			if(menuPosicionActualX < menuTamanoMatrizX) //y no alcanzamos la ultima poscion
			{
				Serial.println("y!=0  X<tamanoX  -->  Y++");
				menuPosicionActualY++;			//pasamos al siguiente sub-menu
			}
		}
	}

	else if(teclaPulsada=='u')
	{
		if(menuPosicionActualY==0 )			//y si estamos en el menu X.0
		{ 
			Serial.println("Y=0  -->  X--");
			menuPosicionActualX--; 		//pasamos al menu (X-1).0			
		}
		else								//o si estamos en un submenu
		{
			if(menuPosicionActualX > 0) //y no alcanzamos la primera poscion
			{
				Serial.println("Y!=0  x>0  --> y--");
				menuPosicionActualY--;
			}
		}

	}
	
	else if(teclaPulsada== 'o')
	{


	}
	else if(teclaPulsada=='c')
	{

	}

	menuActualizar();


}

void accionMenu()
{
}



