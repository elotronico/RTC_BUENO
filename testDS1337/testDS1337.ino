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

	rAstro();
	rOrto();
	rOcaso();
	rHfija();


	/*
	//---------------------------
	//comprobamos astronomicos
	//---------------------------
	//comprueba y actua sobre alguna salida si esta programada como astronomica
	bool a=false,b=false,c=false;
	for(uint8_t circuito=1;circuito<9;circuito++){
		a= revisaProgramacionAstronomica(circuito);
		b= revisaProgramacionOcaso(circuito);
		c= revisaProgramacionOrto(circuito);
		//revisaprogramacionHoraFija(circuito);
		Serial.println("Circuito "+(String)circuito+" con prog "+(String)a+(String)b+(String)c);
	}
	*/

	
	

	refrescarSalidas();

	//programamos la siguiente interrupcion
	
	RTCrenuevaInterrupcion();
	ponerEnHora(diaActual,mesActual,anoActual,horaActual,minutoActual,58);

	//actualizarPantallaPpalLCD();
	imprimirHoraSerial();
	enviaSerialEstadoSalidas();
	//enviarSerialProgramacionFLASH();

}

//revisa programacion astronomica
void rAstro(){
	for(uint8_t prog=0;prog<20; prog++)	{
		if(tablaHorarioEncendidos[prog][horarioEnable]==progHabilitado){
			if(tablaHorarioEncendidos[prog][horarioTipo]==astro){
				if(mdiarioAmanece>mdiarioHora || mdiarioHora>=mdiarioAnochece){
					activarSalida(tablaHorarioEncendidos[prog][horarioCircuito]);					
				}		
				else{
					desactivarSalida(prog);
				}
			}
		}
	}
}

//revisa acciones en orto
void rOrto(){

	for(uint8_t prog=0;prog<20; prog++)	{
		if(tablaHorarioEncendidos[prog][horarioEnable]==progHabilitado){
			if(tablaHorarioEncendidos[prog][horarioTipo]==orto){
				if(esAntesOrto==false){		//si es despues del orto
					if(tablaHorarioEncendidos[prog][horarioAccion]==activar){
						activarSalida(tablaHorarioEncendidos[prog][horarioCircuito]);					
					}
					else if (tablaHorarioEncendidos[prog][horarioAccion]==desactivar){
						desactivarSalida(tablaHorarioEncendidos[prog][horarioCircuito]);
					}
				}		
				else{
					//desactivarSalida(prog);
				}
			}
		}
	}


}

//revisa acciones en ocaso
void rOcaso(){

	for(uint8_t prog=0;prog<20; prog++)	{
		if(tablaHorarioEncendidos[prog][horarioEnable]==progHabilitado){
			if(tablaHorarioEncendidos[prog][horarioTipo]==ocaso){
				if(esDespuesOcaso()==true){
					if(tablaHorarioEncendidos[prog][horarioAccion]==activar){
						activarSalida(tablaHorarioEncendidos[prog][horarioCircuito]);					
					}
					else if (tablaHorarioEncendidos[prog][horarioAccion]==desactivar){
						desactivarSalida(tablaHorarioEncendidos[prog][horarioCircuito]);
					}
				}		
				else{
					//desactivarSalida(prog);
				}
			}
		}
	}


}

//revisa acciones en horas fijas
void rHfija(){
	
	for(int i=0; i<20;i++){
		if(mdiarioC1ordenado[i]>0){
##error
		}
	}


}


bool revisaProgramaHoraFija(uint8_t circuito){
		//si el programa esta habilitado
	for(uint8_t prog=0; prog<19;prog++){	
		if(tablaHorarioEncendidos[prog][horarioEnable]){
			
			
		
		}
	}
}





//bueno
//comprobamos si es despues del ocas
//si esdespues del ocaso devuelve 1
// sino devuelve 0
bool esDespuesOcaso(void){
	
	//si es cualquier hora mayor que la hora de anochecer
	if(horaActual>(horaAnochece+1)){
		Serial.println("esDespuesOcaso()=true");
		return true;
	}

	//si es la misma hora que la de anochecer
	else if(horaActual==horaAnochece){

		//y si el minuto es igual o mayor al de ocaso
		if(minutoActual >= minutoAnochece){
			Serial.println("esDespuesOcaso()=true");
			return true;
		}
		//si la hora es igual pero el minuto es distinto
		else {
			Serial.println("esDespuesOcaso()=false");
			return false;
		}
	}

	//si la hora actual es menor que la de anochecer
	else {
		Serial.println("esDespuesOcaso()=false");
		return false;
	}


	//otro metodo alternativo
	/*
tmElements_t FechaAhora, FechaOcaso ;
   FechaOcaso.Second = 0;
   FechaOcaso.Minute = minutoAnochece;
   FechaOcaso.Hour = horaAnochece;
   FechaOcaso.Day = diaActual ;
   FechaOcaso.Month = mesActual ;
   FechaOcaso.Year = anoActual -1970 ;

   FechaAhora.Second = 0;
   FechaAhora.Minute = minutoActual;
   FechaAhora.Hour = horaActual;
   FechaAhora.Day = diaActual;
   FechaAhora.Month = mesActual;
   FechaAhora.Year = anoActual-1970;

time_t TAhora = makeTime(FechaAhora);
time_t TOcaso = makeTime(FechaOcaso);

	
	Serial.println((String)TAhora);
	Serial.print("ocaso:");
	Serial.println((String)TOcaso);

	if(TAhora>=TOcaso){				
		Serial.println("785: es despues del ocaso");	
		return true;
	}
	else{
		Serial.println("444: es antes del ocaso");
		return false;
	}
	*/

}



//bueno
//comprobamos si es antes del orto
// si antes del orto devuelve 1 
// sino devuelve 0
bool esAntesOrto(void){

	//si la hora actual es cualquier otra anterior a la de amanecer
	if(horaActual<horaAmanece){
		Serial.println("esDespuesOcaso()=true");
		return true;
	}

	//si la hora actual es igual a la de amanecer
	else if(horaActual==horaAmanece){

		//y el minuto es anterior al minuto de amanecer
		if (minutoActual<minutoAmanece){
			Serial.println("esDespuesOcaso()=true");
			return true;
		}

		//si la hora es igual pero el minuto es mayor o igual al de amanecer
		else{
			Serial.println("esDespuesOcaso()=false");
			return false;
		}
	}
		
	//si la hora actual es mayor a la de amanecer
	else{
		Serial.println("esDespuesOcaso()=false");
		return false;
	}
	


	//este es otro metodo alternativo
	/*		
tmElements_t FechaAhora, FechaOrto ;

   FechaOrto.Second = 0;
   FechaOrto.Minute = minutoAmanece;
   FechaOrto.Hour = horaAmanece;
   FechaOrto.Day = diaActual ;
   FechaOrto.Month = mesActual ;
   FechaOrto.Year = anoActual -1970 ;

   FechaAhora.Second = 0;
   FechaAhora.Minute = minutoActual;
   FechaAhora.Hour = horaActual;
   FechaAhora.Day = diaActual;
   FechaAhora.Month = mesActual;
   FechaAhora.Year = anoActual-1970;

time_t TAhora = makeTime(FechaAhora);
time_t TOrto = makeTime(FechaOrto);

	Serial.println((String)TAhora);
	Serial.print("orto:");
	Serial.println((String)TOrto);

	if(TAhora<TOrto){
		Serial.println("786: es antes del orto");	
		return HIGH;
	}
	else{
		Serial.println("555: es despues del orto");	
		return false;
	}
	*/


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
	actualizarPantallaPpalLCD();		
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



//----------------------------------------
//   envia un codigo de error por el COM
//----------------------------------------
void avisoError(int codigoError)
{
	Serial.println("Error cod: " + (String)codigoError);
}

