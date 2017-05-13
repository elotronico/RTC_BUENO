
//edita la programacion horaria correspondiente a menuposy-1
void mostrarProgramaHorarioLCD(){		//imprimimos el numero de programa que coincide con la pos en menuposy
	
	volatile uint8_t menuY = menuPosY-1;
			delay(delayPulsacion);

			lcd.clear();
			lcd.print("Prog " + String(menuPosY));
			

			//si  esta programacion horaria esta DESACTIVADA
			if(tablaHorarioEncendidos[menuY][horarioEnable] == progDeshabilitado){		
				lcd.setCursor(0,1);
				lcd.print("OFF");
				lcd.setCursor(10,0);
				lcd.print("----------");		
				lcd.setCursor(10,1);
				lcd.print("----------");	
				lcd.setCursor(10,2);
				lcd.print("----------");	
				lcd.setCursor(13,3);
				lcd.print("-----");	
			}


			//si  esta programacion horaria esta ACTIVADA
			else if (tablaHorarioEncendidos[menuY][horarioEnable] == progHabilitado){
				
				lcd.setCursor(10,0);
				lcd.print("Salida "+(String)tablaHorarioEncendidos[menuY][horarioCircuito]);

				lcd.setCursor(0,1);
				lcd.print("ON");
				
				lcd.setCursor(10,1);


				//modo astronomico
				if(tablaHorarioEncendidos[menuY][horarioTipo]==astro){
					lcd.print("Astronomi.");

					lcd.setCursor(10,2);
					lcd.print("          ");

					lcd.setCursor(13,3);
					lcd.print("     ");

				}


				//modo orto
				else if(tablaHorarioEncendidos[menuY][horarioTipo]==orto){
					lcd.print("Orto      ");
					
					lcd.setCursor(10,2);
					if(tablaHorarioEncendidos[menuY][horarioAccion]==activar)
						lcd.print("Activar   ");
					else if(tablaHorarioEncendidos[menuY][horarioAccion]==desactivar)
						lcd.print("Desactivar");

					lcd.setCursor(13,3);
					lcd.print("     ");
				}


				//modo ocaso
				else if(tablaHorarioEncendidos[menuY][horarioTipo]==ocaso){
					lcd.print("Ocaso     ");
					
					lcd.setCursor(10,2);
					if(tablaHorarioEncendidos[menuY][horarioAccion]==activar)
						lcd.print("Activar   ");
					else if(tablaHorarioEncendidos[menuY][horarioAccion]==desactivar)
						lcd.print("Desactivar");

					lcd.setCursor(13,3);
					lcd.print("     ");
				}


				//modo hora fija
				else if(tablaHorarioEncendidos[menuY][horarioTipo]==horaFija){
					lcd.print("Hora fija");
									
					lcd.setCursor(10,2);
					if	   (tablaHorarioEncendidos[menuY][horarioAccion]==activar)
						lcd.print("Activar   ");
					else if(tablaHorarioEncendidos[menuY][horarioAccion]==desactivar)
						lcd.print("Desactivar");

					lcd.setCursor(13,3);
					imprimirDigitosLCD(tablaHorarioEncendidos[menuY][horarioHora]);
					lcd.print(":");
					imprimirDigitosLCD(tablaHorarioEncendidos[menuY][horarioMinuto]);
				}

				//si hay cualquier otro valor es porque hay un ERROR
				else {
				avisoError(11);
				}
			}


			//si hay cualquier otro valor es porque hay un ERROR
			else {
				avisoError(10);
			}



			/*
			lcd.setCursor(8,0);
			lcd.print("Circuito "+ (String)horarioCircuito);




			//si el horario esta habilitado
			if(tablaHorarioEncendidos[menuPosY][horarioEnable] == progHabilitado){
			
				lcd.setCursor(0,1);
				lcd.print("ON ");

				//imprime tipo de horario
				lcd.setCursor(3,0);
				if(tablaHorarioEncendidos[menuPosY][horarioTipo]==astro){
					lcd.print("Astrono");
				}
				else if(tablaHorarioEncendidos[menuPosY][horarioTipo]==horaFija){
					lcd.print("Horario");
				}

				
				
				//imprimie el horario de encendido
				lcd.setCursor(11,0);
				imprimirDigitosLCD((int)(tablaHorarioEncendidos[menuPosY][horarioHoraEncendido]));
				lcd.print(":");
				imprimirDigitosLCD((int)tablaHorarioEncendidos[menuPosY][horarioMinutoEncendo]);

				//imprimie el horario de apagado
				lcd.setCursor(11,1);
				imprimirDigitosLCD((int)tablaHorarioEncendidos[menuPosY][horarioHoraApagado]);
				lcd.print(":");
				imprimirDigitosLCD((int)tablaHorarioEncendidos[menuPosY][horarioMinutoApagado]);

				delay(200);

				

			}
			
			//si esta deshabilitado
			else if (tablaHorarioEncendidos[menuPosY][horarioEnable]==progDeshabilitado){
				lcd.setCursor(0,1);
				lcd.print("OFF");
			
				lcd.setCursor(3,0);
				lcd.print("------- --:--");

				lcd.setCursor(11,1);
				lcd.print("--:--");
			}
			

			else{
				Serial.println("horario " + (String)menuPosY + "ERROR. Valor:"+(String)tablaHorarioEncendidos[menuPosY][0]);
			}
			*/
			
}



//edita la programacion horaria correspondiente a menuposy-1
void editarProgramacion(){		
		
	volatile uint8_t menuY = menuPosY-1;

	//actualizarProgramaHorarioLCD();		//esto lee los datos de la tabla y los muestra en el lcd
	
	
	//----------- modificamos on off -------------------
	lcd.setCursor(2,1);		
	lcd.blink_on();
	
	teclaPulsada='0';
	delay(delayPulsacion);

	//minentras no pulsemos ok
	while(teclaPulsada != 'o'){

		teclaPulsada = leerTeclado();	
		

		if((teclaPulsada =='u') | (teclaPulsada == 'd')){
			
			if(tablaHorarioEncendidos[menuY][horarioEnable]==progHabilitado){			//si el horario esta habilitado
				tablaHorarioEncendidos[menuY][horarioEnable]=progDeshabilitado;			//lo deshabilitamos
			}
			else if(tablaHorarioEncendidos[menuY][horarioEnable]==progDeshabilitado){	//si el horario esta deshabilitado
				tablaHorarioEncendidos[menuY][horarioEnable]=progHabilitado;			//lo habilitamos
			}

			teclaPulsada = '0';	
			mostrarProgramaHorarioLCD();
			lcd.setCursor(2,1);		
			delay(delayPulsacion);
		}
	}

	delay(delayPulsacion);
	teclaPulsada='0';

	
	if(tablaHorarioEncendidos[menuY][horarioEnable]==progHabilitado){

		//----------- modificamos la salida sobre la que actua -------------------
		lcd.setCursor(10,0);
	
		//minentras no pulsemos ok
		while(teclaPulsada != 'o'){
	
			teclaPulsada = '0';	
			teclaPulsada = leerTeclado();	

			//si pulsamos arriba
			if(teclaPulsada =='u'){
				//y el circuito seleccionado es menor que 8
				if(tablaHorarioEncendidos[menuY][horarioCircuito]<8){
					//incrementamos
					tablaHorarioEncendidos[menuY][horarioCircuito]++;
				
					mostrarProgramaHorarioLCD();
					lcd.setCursor(10,0);		
					delay(delayPulsacion);			
				}
			}


			//si pulsamos abajo
			else if(teclaPulsada=='d'){
				if(tablaHorarioEncendidos[menuY][horarioCircuito]>1){
					tablaHorarioEncendidos[menuY][horarioCircuito]--;
	
					mostrarProgramaHorarioLCD();
					lcd.setCursor(10,0);		
					delay(delayPulsacion);	
				}					
			}	
		}
	
		teclaPulsada='0';
		delay(delayPulsacion);


		//----------- modificamos la accion que desencadena -------------------
		lcd.setCursor(10,1);
	
		//minentras no pulsemos ok
		while(teclaPulsada != 'o'){
	
			teclaPulsada = '0';	
			teclaPulsada = leerTeclado();	

			//si pulsamos arriba
			if(teclaPulsada =='u'){
				if(tablaHorarioEncendidos[menuY][horarioTipo]<3){		//3+1 es el numero de opciones que tenemos (ver header.h)
					//incrementamos
					tablaHorarioEncendidos[menuY][horarioTipo]++;
				
					mostrarProgramaHorarioLCD();
					lcd.setCursor(10,1);		
					delay(delayPulsacion);			
				}
			}
		
			//si pulsamos abajo
			else if(teclaPulsada=='d'){
				if(tablaHorarioEncendidos[menuY][horarioTipo]>0){
					//decrementamos
					tablaHorarioEncendidos[menuY][horarioTipo]--;
				
					mostrarProgramaHorarioLCD();
					lcd.setCursor(10,1);		
					delay(delayPulsacion);	
				}					
			}	
		}

		teclaPulsada='0';
		delay(delayPulsacion);
	

		//----------- si no es astronomico --> elegimos como queremos que actue sobre la salida -------------------
		if(tablaHorarioEncendidos[menuY][horarioTipo] != astro){
			lcd.setCursor(10,2);

			while(teclaPulsada !='o'){
				teclaPulsada = leerTeclado();

				if(teclaPulsada =='u' | teclaPulsada == 'd'){
					if(tablaHorarioEncendidos[menuY][horarioAccion]==activar){			//si el horario esta habilitado
						tablaHorarioEncendidos[menuY][horarioAccion]=desactivar;			//lo deshabilitamos
					}
					else if(tablaHorarioEncendidos[menuY][horarioAccion]==desactivar){	//si el horario esta deshabilitado
						tablaHorarioEncendidos[menuY][horarioAccion]=activar;			//lo habilitamos

					}
					teclaPulsada = '0';	
					mostrarProgramaHorarioLCD();
					lcd.setCursor(10,2);		
					delay(delayPulsacion);
				}
			}


			teclaPulsada='0';
			delay(delayPulsacion);
	
			//----------- si es por hora fija --> elegimos a que hora queremos que actue -------------------
			if(tablaHorarioEncendidos[menuY][horarioTipo]== horaFija){
				lcd.setCursor(13,3);

				//establecemos hora
				while(teclaPulsada!='o'){
						delay(delayPulsacion);
						teclaPulsada = leerTeclado();
						if((teclaPulsada == 'u') & (tablaHorarioEncendidos[menuY][horarioHora]<23)){		//hora ++
							tablaHorarioEncendidos[menuY][horarioHora]++;
							lcd.setCursor(13,3);
							imprimirDigitosLCD(tablaHorarioEncendidos[menuY][horarioHora]);
							lcd.setCursor(13,3);
						}
						else if ((teclaPulsada =='d') & (tablaHorarioEncendidos[menuY][horarioHora]>0)){		//hora --
							tablaHorarioEncendidos[menuY][horarioHora]--;
							lcd.setCursor(13,3);
							imprimirDigitosLCD(tablaHorarioEncendidos[menuY][horarioHora]);
							lcd.setCursor(13,3);
						}				
					}

					lcd.setCursor(16,3);


					//establecer minutos
					teclaPulsada='0';
					while (teclaPulsada != 'o')	{
						delay(delayPulsacion);
						teclaPulsada = leerTeclado();
						if((teclaPulsada == 'u') && (tablaHorarioEncendidos[menuY][horarioMinuto]<59)){		//minutos ++
							tablaHorarioEncendidos[menuY][horarioMinuto]++;
							lcd.setCursor(16,3);
							imprimirDigitosLCD(tablaHorarioEncendidos[menuY][horarioMinuto]);
							lcd.setCursor(16,3);
						}
						else if ((teclaPulsada =='d') && (tablaHorarioEncendidos[menuY][horarioMinuto]>0)){		//minutos --
							tablaHorarioEncendidos[menuY][horarioMinuto]--;
							lcd.setCursor(16,3);
							imprimirDigitosLCD(tablaHorarioEncendidos[menuY][horarioMinuto]);
							lcd.setCursor(16,3);
						}
						else if (teclaPulsada== 'c'){			//cancelamos cambios
							lcd.clear();
							lcd.blink_off();
							lcd.print("Cancelado");
							delay(1000);
							return;
						}
					}
			}
		}	
	}


	//--------------- salimos -----------------------
	teclaPulsada='0';
	delay(delayPulsacion);
	guardarProgramacionEnEEPROM();
	
	lineas();
	Serial.println("Programacion Modificada");
	enviarSerialProgramacionFLASH();
	siHayInterrupcion();		//comprobamos si hay que actuar sobre alguna salida con la nueva programacion
	teclaPulsada='0';

	lcd.blink_off();

	ordenarHorariosFijos();
	
}

//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------

void ordenarHorariosFijos(){
		

		lineas();
		Serial.println("programacion minutaria desordenada");
		
		//ordenamos todos los valorees de horas fijas en una matriz (convertidos en minutos)
		for(uint8_t i=0;i<20;i++){
			mdiarioProgramacionDesord[i] = (tablaHorarioEncendidos[i][horarioHora]*60) + tablaHorarioEncendidos[i][horarioMinuto];
			Serial.println((String)mdiarioProgramacionDesord[i]);
		}

		//ordenamos y separarmos los horarios por circuitos
		//----------------------------------------------
		//    ordenamos el circuito 1
		//----------------------------------------------
		//separamos los horarios por circuitos (solo los que estan habilitados)
		for(uint8_t prog=0; prog<20; prog++){			
			
			if(eshfija¿(1,prog)==true){
				mdiarioC1ordenado[prog]=mdiarioProgramacionDesord[prog];
			}
			else{
				mdiarioC1ordenado[prog]=0;
			}			
		}

		/* sort array using qsort functions */ 
		qsort(mdiarioC1ordenado, 20, sizeof(int), int_cmp);

		//----------------------------------------------
		//    ordenamos el circuito 2
		//----------------------------------------------
		//separamos los horarios por circuitos (solo los que estan habilitados)
		for(uint8_t prog=0; prog<20; prog++){			
			
			if(eshfija¿(2,prog)==true){
				mdiarioC2ordenado[prog]=mdiarioProgramacionDesord[prog];
			}
			else{
				mdiarioC2ordenado[prog]=0;
			}			
		}

		/* sort array using qsort functions */ 
		qsort(mdiarioC2ordenado, 20, sizeof(int), int_cmp);

		//----------------------------------------------
		//    ordenamos el circuito 3
		//----------------------------------------------
		//separamos los horarios por circuitos (solo los que estan habilitados)
		for(uint8_t prog=0; prog<20; prog++){			
			
			if(eshfija¿(3,prog)==true){
				mdiarioC3ordenado[prog]=mdiarioProgramacionDesord[prog];
			}
			else{
				mdiarioC3ordenado[prog]=0;
			}			
		}

		/* sort array using qsort functions */ 
		qsort(mdiarioC3ordenado, 20, sizeof(int), int_cmp);
		//----------------------------------------------
		//    ordenamos el circuito 4
		//----------------------------------------------
		//separamos los horarios por circuitos (solo los que estan habilitados)
		for(uint8_t prog=0; prog<20; prog++){			
			
			if(eshfija¿(4,prog)==true){
				mdiarioC4ordenado[prog]=mdiarioProgramacionDesord[prog];
			}
			else{
				mdiarioC4ordenado[prog]=0;
			}			
		}

		/* sort array using qsort functions */ 
		qsort(mdiarioC4ordenado, 20, sizeof(int), int_cmp);

		//----------------------------------------------
		//    ordenamos el circuito 5
		//----------------------------------------------
		//separamos los horarios por circuitos (solo los que estan habilitados)
		for(uint8_t prog=0; prog<20; prog++){			
			
			if(eshfija¿(5,prog)==true){
				mdiarioC5ordenado[prog]=mdiarioProgramacionDesord[prog];
			}
			else{
				mdiarioC5ordenado[prog]=0;
			}			
		}

		/* sort array using qsort functions */ 
		qsort(mdiarioC5ordenado, 20, sizeof(int), int_cmp);


		//----------------------------------------------
		//    ordenamos el circuito 6
		//----------------------------------------------
		//separamos los horarios por circuitos (solo los que estan habilitados)
		for(uint8_t prog=0; prog<20; prog++){			
			
			if(eshfija¿(6,prog)==true){
				mdiarioC6ordenado[prog]=mdiarioProgramacionDesord[prog];
			}
			else{
				mdiarioC6ordenado[prog]=0;
			}			
		}

		/* sort array using qsort functions */ 
		qsort(mdiarioC6ordenado, 20, sizeof(int), int_cmp);
				//----------------------------------------------
		//    ordenamos el circuito 7
		//----------------------------------------------
		//separamos los horarios por circuitos (solo los que estan habilitados)
		for(uint8_t prog=0; prog<20; prog++){			
			
			if(eshfija¿(7,prog)==true){
				mdiarioC7ordenado[prog]=mdiarioProgramacionDesord[prog];
			}
			else{
				mdiarioC7ordenado[prog]=0;
			}			
		}

		/* sort array using qsort functions */ 
		qsort(mdiarioC7ordenado, 20, sizeof(int), int_cmp);

		//----------------------------------------------
		//    ordenamos el circuito 8
		//----------------------------------------------
		//separamos los horarios por circuitos (solo los que estan habilitados)
		for(uint8_t prog=0; prog<20; prog++){			
			
			if(eshfija¿(8,prog)==true){
				mdiarioC8ordenado[prog]=mdiarioProgramacionDesord[prog];
			}
			else{
				mdiarioC8ordenado[prog]=0;
			}			
		}

		/* sort array using qsort functions */ 
		qsort(mdiarioC8ordenado, 20, sizeof(int), int_cmp);


		
}



void imprimeSerialHorariosFijosOrdenados(void){
	
		lineas();
		Serial.println("Programa1");
		for(uint8_t i=0;i<20;i++){
			Serial.println((String)mdiarioC1ordenado[i]);
		}
		lineas();
		Serial.println("Programa2");
		for(uint8_t i=0;i<20;i++){
			Serial.println((String)mdiarioC2ordenado[i]);
		}
		lineas();
		Serial.println("Programa3");
		for(uint8_t i=0;i<20;i++){
			Serial.println((String)mdiarioC3ordenado[i]);
		}
		lineas();
		Serial.println("Programa4");
		for(uint8_t i=0;i<20;i++){
			Serial.println((String)mdiarioC4ordenado[i]);
		}
		lineas();
		Serial.println("Programa5");
		for(uint8_t i=0;i<20;i++){
			Serial.println((String)mdiarioC5ordenado[i]);
		}
		lineas();
		Serial.println("Programa6");
		for(uint8_t i=0;i<20;i++){
			Serial.println((String)mdiarioC6ordenado[i]);
		}
		lineas();
		Serial.println("Programa7");
		for(uint8_t i=0;i<20;i++){
			Serial.println((String)mdiarioC7ordenado[i]);
		}
		lineas();
		Serial.println("Programa8");
		for(uint8_t i=0;i<20;i++){
			Serial.println((String)mdiarioC8ordenado[i]);
		}


}

//---------------------------------------------------------------------------------------------
//		comprueba si el programa esta habilitado como hora fija para ese circuito
//---------------------------------------------------------------------------------------------
bool eshfija¿(uint8_t circuito, uint8_t prog){
			if(tablaHorarioEncendidos[prog][horarioCircuito]==circuito){
				//si el prog esta habilitado y en modo hra fija
				if((tablaHorarioEncendidos[prog][horarioEnable]==progHabilitado)&&(tablaHorarioEncendidos[prog][horarioTipo]==horaFija)){
					//escribimos el valor de la hora (en minutos)
					return true;
				}
				else{
					//sino escribimos 0
					return false;
				}
			}
			else{
				return false;
			}
}


/* qsort int comparison function */ 
int int_cmp(const void *a, const void *b) 
{ 
    const int *ia = (const int *)a; // casting pointer types 
    const int *ib = (const int *)b;
    return *ia  - *ib; 
	/* integer comparison: returns negative if b > a 
	and positive if a > b */ 
} 


//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------




//sin desarrollar
void cambiarCoordenadasGeograficas(void){



}



//sin desarrollar
void establecerCiudad(void){

}

//sin desarrollar
void cambiarZonaHoraria(void){

}




