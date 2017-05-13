//#include "menus.h"

//#define debug		//habilita comandos serie

volatile bool stateled= false;
volatile bool stateinterrupt = false;


#include <EEPROM.h>
#include <LiquidCrystal_I2C.h>
#include <DS1337RTC.h>
#include <Time.h>
#include <Wire.h>
#include <TimeLord.h>

#include "Header.h"


void siHayInterrupcion(void){
	
	Serial.println();
	lineas();
	Serial.println("-------cambio de minuto--------");
	lineas();
	

	//1  actualizamos la hora marcada por el RTC --> micro
	leerHora();
		
	//2  apaga alarma RTC
	RTC.resetAlarms();


	//revisa si hay que actuar sobre alguna salida
	revisaProgramaciones();

	
	//programamos la siguiente interrupcion
	RTCrenuevaInterrupcion();
	
	
	
	ponerEnHora(diaActual,mesActual,anoActual,horaActual,minutoActual,58);

	//actualizarPantallaPpalLCD();
	imprimirHoraSerial();
	enviaSerialEstadoSalidas();
	//enviarSerialProgramacionFLASH();

}






//-----------------------------------------------------
//---					void SETUP 					---
//-----------------------------------------------------

void setup(){

	lcd.begin();
	Serial.begin(57600);

	lcd.print("Iniciando...");
	Serial.println("Iniciando...");
	delay(1000);

	//led indicador como salida
	pinMode(led,OUTPUT);		
	digitalWrite(led,HIGH);

	//configuracion de botones
	pinMode(btnCancel,INPUT);
	pinMode(btnOk,INPUT);
	pinMode(btnUp,INPUT);
	pinMode(btnDown,INPUT);


	pinMode(salida1,OUTPUT);
	pinMode(salida2,OUTPUT);
	pinMode(salida3,OUTPUT);


	digitalWrite(salida1,LOW);
	digitalWrite(salida2,LOW);
	digitalWrite(salida3,LOW);

	
	

	//actualizarMenuLcd();
		

	leerProgramacionDeEEPROM();								//pasa tabla horarios de la EEPROM --> FLASH

	leerHora();												//refresca los valores anoActual, mesActual,diaActual, horaActual minutoActual
	calculoOrtoOcaso(diaActual, mesActual, anoActual);		//calculamos el orto y ocaso para el dia actual

	RTC.resetAlarms();
	attachInterrupt(digitalPinToInterrupt(RTCpinInt), RTCinterrupcion, FALLING);		//interrupcion del reloj (INTA)
	siHayInterrupcion();				//comprueba si hay que activar alguna salida y programa la interrupcion para el minuto siguiente
	actualizarPantallaPpalLCD();		
	lcd.clear();
	
	actualizarPantallaPpalLCD();

	
	Serial.println("salimos del setup");
	

}



  
//-----------------------------------------------------
//---					void LOOP 					---
//-----------------------------------------------------
void loop(){
	
	delay(delayPulsacion);
	teclaPulsada = leerTeclado();
	
	if(teclaPulsada != '0'){	
		#ifdef debug
		Serial.println("TelcaPulsada: " + (String)teclaPulsada);
		#endif	
		actualizarPosicionMenu();
		
		teclaPulsada = '0';
	}

	if((stateinterrupt == true) &(menuPosX == 0)){			//comprobamos si la interrupcion ha activado el flag
		stateinterrupt = false;			//lo reseteamos
		siHayInterrupcion();			//hacemos el codigo propio de la interrupcion
		actualizarPantallaPpalLCD();
	}

	
	if(menuPosX == 0 && menuPosY ==0){	
		delay(250);
		teclaPulsada = leerTeclado();
	
		if(teclaPulsada != '0'){	
			actualizarPosicionMenu();
			teclaPulsada = '0';
		}

		delay(250);
		stateled = !stateled;
		digitalWrite(led,stateled);
		lcd.setCursor(4,1);
		if(stateled==false){
			lcd.print(" ");
		}
		else{
			lcd.print(":");
		}
	
	} 
	
}





