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

//buena, esta es copia seg
void siHayInterrupcion(void){
	//1  actualiza la hora del RTC -->micro
	//2  apaga alarma RTC
	//3  comprueba programaciones horarias y acuta sobre salidas
	//4  programa siguiente alarma

	
	Serial.println();
	Serial.println("------------------------------");
	Serial.println("-------cambio de minuto--------");
	Serial.println("------------------------------");

	//1  actualizamos la hora marcada por el RTC --> micro
	leerHora();
	actualizarPantallaPpalLCD();
	
	//2  apaga alarma RTC
	RTC.resetAlarms();

	//3  comprueba programaciones horarias y acuta sobre salidas
	//recorremos las 20 filas de la tabla de horarios
	for(uint8_t prog=0; prog<20; prog++){			
		Serial.println("");
		Serial.print("programa " + (String)prog + " - ");
		if(tablaHorarioEncendidos[prog][horarioEnable] == progHabilitado){					//si el prog 1 esta habilitado
			Serial.print("habilitado - ");
			

			//--------------------------------------------------------------
			// TIPO DE HORARIO --> ORTO (ENCIENDE O APAGA SEGUN ASTRONOMICO)
			//--------------------------------------------------------------
			if(tablaHorarioEncendidos[prog][horarioTipo] == orto){							//y esta configurado como orto
				Serial.print("orto\t");
				if(horaActual>=horaAmanece && minutoActual>=minutoAmanece){		//si pasa de la hora de orto
					if(tablaHorarioEncendidos[prog][horarioAccion]==activar){
						activarSalida(tablaHorarioEncendidos[prog][horarioCircuito]);
					}
					else{
						desactivarSalida(tablaHorarioEncendidos[prog][horarioCircuito]);
					}				
				}

				if(tablaHorarioEncendidos[prog][horarioAccion]==activar){

				}
				else if(tablaHorarioEncendidos[prog][horarioAccion]==desactivar){

				}
				

			}
			
			//---------------------------------------------------------------
			// TIPO DE HORARIO --> OCASO (ENCIENDE O APAGA SEGUN ASTRONOMICO)
			//---------------------------------------------------------------
			else if(tablaHorarioEncendidos[prog][horarioTipo] == ocaso){
				Serial.print("ocaso\t");
			}


			//---------------------------------------------------------------------
			// TIPO DE HORARIO --> ASTRONOMICO (ENCIENDE Y APAGA SEGUN ASTRONOMICO)
			//---------------------------------------------------------------------
			else if(tablaHorarioEncendidos[prog][horarioTipo] == astro){
					Serial.print("astronomico - ");
					Serial.println("");

					if(horaActual >= horaAnochece){
						Serial.print(">---ok");
					}
					else					{
						Serial.print("fallo 1");
					}
						
					if(minutoActual >= minutoAnochece){
						Serial.println(">---ok");
					}
					else					{
						Serial.print("fallo 2");
					}


					if(horaActual<= horaAmanece){
						Serial.print(">---aa");
					}
					else					{
						Serial.print("fallo 3");
					}
						
					if(minutoActual<minutoAmanece){
						Serial.println(">---a");
					}
					else					{
						Serial.print("fallo 4");
					}





					

					if( (horaActual >= horaAnochece) && (minutoActual >= minutoAnochece)){				//si la hora y el minuto actual es igual que la hora de ocaso
							Serial.println("por la noche");
							activarSalida(tablaHorarioEncendidos[prog][horarioCircuito]);	
							//Serial.println(">anochece -> salida " + (String)tablaHorarioEncendidos[prog][horarioCircuito] + " activada");					
					}

					else if ( (horaActual<= horaAmanece) && (minutoActual<minutoAmanece)){
							Serial.println("por la mañana");
							activarSalida(tablaHorarioEncendidos[prog][horarioCircuito]);
							//Serial.println("<amanece -> salida " + (String)tablaHorarioEncendidos[prog][horarioCircuito] + " activada");								
					}

					else {
						desactivarSalida(tablaHorarioEncendidos[prog][horarioCircuito]);
						Serial.println("de dia");
					}
			}					

			//---------------------------------------------------------------------------------------------
			// TIPO DE HORARIO --> HORA FIJA (ENCIENDE O APAGA SEGUN LA HORA FIJA QUE INDIQUEMOS NOSOTROS)
			//---------------------------------------------------------------------------------------------
			else if(tablaHorarioEncendidos[prog][horarioTipo] == horaFija){
				Serial.print("h. fija\t");

			}
		}
		
		else if(tablaHorarioEncendidos[prog][horarioEnable] == progDeshabilitado){
			Serial.print("desabilitado");
		}
	}

	//programamos la siguiente interrupcion
	RTCrenuevaInterrupcion();

}

void siHayInterrupcion1(void){

	
	Serial.println();
	Serial.println("------------------------------");
	Serial.println("-------cambio de minuto--------");
	Serial.println("------------------------------");
	

	//1  actualizamos la hora marcada por el RTC --> micro
	leerHora();
		
	//2  apaga alarma RTC
	RTC.resetAlarms();


	revisaProgramacionAstronomica();	
	revisaProgramacionOrto();
	revisaProgramacionOcaso();

	/*

	for(uint8_t circuitoScan=0; circuitoScan<7; circuitoScan++){			


		for(uint8_t prog=0; prog<20;prog++){

				Serial.println("");
				Serial.print("Circuito " + (String)circuitoScan + " - ");

				//si el prog que escaneamos coincide con el circuito que estamos revisando
				if(tablaHorarioEncendidos[prog][horarioCircuito] == circuitoScan){					
					Serial.print("Prog "+ (String)prog +  " - ");
			
					//--------------------------------------------------------------
					// TIPO DE HORARIO --> ORTO (ENCIENDE O APAGA SEGUN ASTRONOMICO)
					//--------------------------------------------------------------
					if(tablaHorarioEncendidos[prog][horarioTipo] == orto){							//y esta configurado como orto
						Serial.print("orto\t");

					}

					//---------------------------------------------------------------
					// TIPO DE HORARIO --> OCASO (ENCIENDE O APAGA SEGUN ASTRONOMICO)
					//---------------------------------------------------------------
					else if(tablaHorarioEncendidos[prog][horarioTipo] == ocaso){
						Serial.print("ocaso\t");
					
					}
					

					//---------------------------------------------------------------------
					// TIPO DE HORARIO --> ASTRONOMICO (ENCIENDE Y APAGA SEGUN ASTRONOMICO)
					//---------------------------------------------------------------------
					else if(tablaHorarioEncendidos[prog][horarioTipo] == astro){
							Serial.print("astronomico - ");

							if(horaActual >= horaAnochece & minutoActual >= minutoAnochece){				//si la hora y el minuto actual es igual que la hora de ocaso
						
									activarSalida(tablaHorarioEncendidos[prog][horarioCircuito]);	
									//Serial.println(">anochece -> salida " + (String)tablaHorarioEncendidos[prog][horarioCircuito] + " activada");					
							}

							else if (horaActual<= horaAmanece && minutoActual<minutoAmanece){
						
									activarSalida(tablaHorarioEncendidos[prog][horarioCircuito]);
									//Serial.println("<amanece -> salida " + (String)tablaHorarioEncendidos[prog][horarioCircuito] + " activada");								
							}

							else {
								desactivarSalida(tablaHorarioEncendidos[prog][horarioCircuito]);
							}
					}					

					//---------------------------------------------------------------------------------------------
					// TIPO DE HORARIO --> HORA FIJA (ENCIENDE O APAGA SEGUN LA HORA FIJA QUE INDIQUEMOS NOSOTROS)
					//---------------------------------------------------------------------------------------------
					else if(tablaHorarioEncendidos[prog][horarioTipo] == horaFija){
						Serial.print("h. fija\t");
					}
				}		
	}
	}
	
	*/

	//programamos la siguiente interrupcion
	RTCrenuevaInterrupcion();
	actualizarPantallaPpalLCD();

	imprimirHoraSerial();
	enviaSerialEstadoSalidas();
	//enviarSerialProgramacionFLASH();
}


//comprueba si hay que actuar sobre alguna salida por accion: astronomica
void revisaProgramacionAstronomica(){

	//recorremos los 20 programas
	for(uint8_t prog=0; prog<20;prog++){
	
		//si el programa esta habilitado
		if(tablaHorarioEncendidos[prog][horarioEnable]==progHabilitado){

			//y si el programa es tipo astronomico
			if(tablaHorarioEncendidos[prog][horarioTipo] == astro){
	
				//si estamos despues del ocaso
				if((horaActual >= horaAnochece) && (minutoActual >= minutoAnochece)){				
						activarSalida(tablaHorarioEncendidos[prog][horarioCircuito]);	
						Serial.println("785: es despues del ocaso");					
				}

				//o si estamos antes del orto
				else if ((horaActual<= horaAmanece) && (minutoActual<minutoAmanece)){
						
						activarSalida(tablaHorarioEncendidos[prog][horarioCircuito]);
						Serial.println("786: es antes del orto");								
				}

				//de lo contrario estamos durante el dia
				else {
					desactivarSalida(tablaHorarioEncendidos[prog][horarioCircuito]);
					Serial.println("777: es de dia");
				}
			}
		}	
	}
}


//comprueba si hay que actuar sobre alguna salida por accion: orto
void revisaProgramacionOrto(){

	//recorremos los 20 programas
	for(uint8_t prog=0; prog<20;prog++){

		//si el programa esta habilitado
		if(tablaHorarioEncendidos[prog][horarioEnable]==progHabilitado){

			//si el programa es tipo orto
			if(tablaHorarioEncendidos[prog][horarioTipo] == orto){

				//si estamos despues del orto
				if (horaActual>= horaAmanece && minutoActual>=minutoAmanece){
					
					if(tablaHorarioEncendidos[prog][horarioAccion] == activar){
						activarSalida(tablaHorarioEncendidos[prog][horarioCircuito]);
						Serial.println("revisaProgramacionOrto(): encendemos despues de orto");								
					}
					else{
						desactivarSalida(tablaHorarioEncendidos[prog][horarioCircuito]);
						Serial.println("revisaProgramacionOrto(): apagamos despues de orto");	
					}
				}
			}
		}
	}
}


//comprueba si hay que actuar sobre alguna salida por accion: ocaso
void revisaProgramacionOcaso(){

	//recorremos los 20 programas
	for(uint8_t prog=0; prog<20;prog++){

		//si el programa esta habilitado
		if(tablaHorarioEncendidos[prog][horarioEnable]==progHabilitado){

			//si el programa es tipo orto
			if(tablaHorarioEncendidos[prog][horarioTipo] == ocaso){

				//si estamos despues del orto
				if (horaActual>= horaAmanece && minutoActual>=minutoAmanece){
					
					if(tablaHorarioEncendidos[prog][horarioAccion] == activar){
						activarSalida(tablaHorarioEncendidos[prog][horarioCircuito]);
						Serial.println("revisaProgramacionOcaso(): encendemos despues de ocaso");								
					}
					else{
						desactivarSalida(tablaHorarioEncendidos[prog][horarioCircuito]);
						Serial.println("revisaProgramacionOcaso(): apagamos despues de ocaso");	
					}
				}
			}
		}
	}
}




//-----------------------------------------------------
//---					void SETUP 					---
//-----------------------------------------------------

void setup(){

	lcd.begin();
	Serial.begin(9600);

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
	pinMode(salida4,OUTPUT);
	pinMode(salida5,OUTPUT);
	pinMode(salida6,OUTPUT);
	pinMode(salida7,OUTPUT);
	pinMode(salida8,OUTPUT);

	digitalWrite(salida1,LOW);
	digitalWrite(salida2,LOW);
	digitalWrite(salida3,LOW);
	digitalWrite(salida4,LOW);
	digitalWrite(salida5,LOW);
	digitalWrite(salida6,LOW);
	digitalWrite(salida7,LOW);
	digitalWrite(salida8,LOW);

	
	

	//actualizarMenuLcd();
	
	

	leerProgramacionDeEEPROM();								//pasa tabla horarios de la EEPROM --> FLASH

	leerHora();												//refresca los valores anoActual, mesActual,diaActual, horaActual minutoActual
	calculoOrtoOcaso(diaActual, mesActual, anoActual);		//calculamos el orto y ocaso para el dia actual

	RTC.resetAlarms();
	attachInterrupt(digitalPinToInterrupt(RTCpinInt), RTCinterrupcion, FALLING);		//interrupcion del reloj (INTA)
	siHayInterrupcion();				//comprueba si hay que activar alguna salida y programa la interrupcion para el minuto siguiente
	//	RTCrenuevaInterrupcion();		//programa la interrupcion para el minuto siguiente
	lcd.clear();
	
	actualizarPantallaPpalLCD();
	enviarSerialProgramacionFLASH();
	
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





void avisoError(int codigoError)
{
	Serial.println("Error cod: " + (String)codigoError);
}

