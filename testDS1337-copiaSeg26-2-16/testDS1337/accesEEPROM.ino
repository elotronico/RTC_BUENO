/*
*	Aqui esta el mapeado de la eeprom:
*	0~180 --> tablaHorarioEncendidos[9][20]
*	
*	
*	
*	
*	
*	
*	
*	
*
*
*/

//----------------------------------------------------------
//crea la matriz preestablecida por mi en la memoria eeprom
// y comprueba si se ha escrito bien
//----------------------------------------------------------
void EEPROMformatearArrayProgramacion(void)
{
	//se escribe en la eeprom
	int ptr = 0;
		
	for(int fila=0;fila<20; fila++){
		for (int columna=0; columna<9; columna++){

			EEPROM.write(ptr, (uint8_t)1);
			ptr++;		 

		}
	}

	EEPROM.write(ptr,'\r');
	
	//comprueba lo escrito
	ptr= 0;
	for(int fila=0; fila<20; fila++){
		for(int columna = 0; columna<9; columna++){
			if( (uint8_t)1 != EEPROM.read(ptr)){
				avisoError(7);
			}
			ptr++;
		}		
	}
	if(EEPROM.read(ptr) != '\r'){
		avisoError(8);
	}

	Serial.println("--------------------");
	Serial.println("los " +(String)ptr + "registros de EEPROM se pusieron a 1");
}

//----------------------------------------------------------
//leemos los valores de la programacion guardada en la eeprom
//esto se debe leer a cada reinicio o cuando marche la luz.
//----------------------------------------------------------
void leerProgramacionDeEEPROM(void)
{
	unsigned int ptr=0;
	for(int fila = 0; fila<20; fila++){
		for(int columna=0; columna<9; columna++){
			tablaHorarioEncendidos[fila][columna]= EEPROM.read(ptr);
			ptr++;
		}
	}

	Serial.println("--------------------");
	Serial.println("Se leyeron " + (String)(ptr) + " registros de EEPROM");
}



//----------------------------------------------------------
//guarda la configuracion actual a la EEPROM 
//----------------------------------------------------------
void guardarProgramacionEnEEPROM(void){

	//se escribe en la eeprom
	int ptr = 0;
		
	for(int fila=0;fila<20; fila++){
		for (int columna=0; columna<9; columna++){
			EEPROM.write(ptr, tablaHorarioEncendidos[fila][columna]);
			ptr++;		 
		}
	}

	Serial.println("--------------------");
	Serial.println("Se guardaron " + (String)(ptr) + " registros en la EEPROM");

}




void enviarSerialProgramacionFLASHraw(void)
{


	Serial.println("-----------------------");
	Serial.println(" PROGRAMACION FLASH RAW   ");
	Serial.println("-----------------------");

	for(uint8_t fila = 0; fila<20; fila++){
		
		Serial.print ("Reg " + (String)fila);

		//horarioEnable
		Serial.print ("  " + (String)tablaHorarioEncendidos[fila][horarioEnable]);
		
		//horarioCircuito
		Serial.print ("  " + (String)tablaHorarioEncendidos[fila][horarioCircuito]);

		//horario tipo
		Serial.print("  " + (String)tablaHorarioEncendidos[fila][horarioTipo]);

		//horarioAdelanto
		Serial.print ("  " + (String)tablaHorarioEncendidos[fila][horarioAdelanto]);

		//horarioHora
		Serial.print ("  " + (String)tablaHorarioEncendidos[fila][horarioHora]);

		//horarioMinuto
		Serial.print (":" + (String)tablaHorarioEncendidos[fila][horarioMinuto]);

		//horario accion
		Serial.print ("  " + (String)tablaHorarioEncendidos[fila][horarioAccion]);

		Serial.println (" ");
		
	}

}






//bueno
void enviarSerialProgramacionFLASH(void)
{


	Serial.println("-----------------------");
	Serial.println("   PROGRAMACION FLASH   ");
	Serial.println("-----------------------");

	for(uint8_t fila = 0; fila<20; fila++){
		
		//horarioEnable
		Serial.print ("Reg " + (String)fila);
		if( tablaHorarioEncendidos[fila][horarioEnable]==progHabilitado ){
			Serial.print ("  habilitado  ");
		}
		else{
			Serial.print ("  deshabilitado  ");
		}

		//horarioCircuito
		Serial.print ((String)tablaHorarioEncendidos[fila][horarioCircuito]);

		//horario tipo
		if(tablaHorarioEncendidos[fila][horarioTipo]==astro){
			Serial.print ("  astro");
		}
		else if(tablaHorarioEncendidos[fila][horarioTipo]==orto){
			Serial.print ("  orto");
		}
		else if(tablaHorarioEncendidos[fila][horarioTipo]==ocaso){
			Serial.print ("  ocaso");
		}
		else if(tablaHorarioEncendidos[fila][horarioTipo]==horaFija){
			Serial.print ("  horaFija");
		}


		//horarioAdelanto
		Serial.print ("  " + (String)tablaHorarioEncendidos[fila][horarioAdelanto]);

		//horarioHora
		Serial.print ("  "+(String)tablaHorarioEncendidos[fila][horarioHora]);

		//horarioMinuto
		Serial.print (":"+(String)tablaHorarioEncendidos[fila][horarioMinuto]);

		//horario accion
		if(tablaHorarioEncendidos[fila][horarioAccion]==activar){
			Serial.print ("  activar");
		}
		else if(tablaHorarioEncendidos[fila][horarioAccion]==desactivar){
			Serial.print ("  desactivar");
		}
		

		Serial.println (" ");
		
	}

}


//----------------------------------------------------------
//lee los 180 valores de la tabla de programacion y lo envia por puerto serie
//----------------------------------------------------------
void enviarSerialProgramacionEEPROM(void){

	for (int ptr=0; ptr<180;ptr++){
		Serial.print("Reg " + (String)ptr + '\t' + EEPROM.read(ptr));
	}

}


