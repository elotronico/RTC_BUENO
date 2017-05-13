
//edita la programacion horaria correspondiente a menuposy-1
void mostrarPrograma1(){		//imprimimos el numero de programa que coincide con la pos en menuposy
	
			delay(delayPulsacion);

			lcd.clear();
			lcd.print("Voluntario " + String(menuPosY));
			
			//si  esta programacion horaria esta DESACTIVADA
			if(enC1==0){		
				lcd.setCursor(0,1);
				lcd.print("Desactivado");
			}


			//si  esta programacion horaria esta ACTIVADA
			else if (enC1==1){
				lcd.setCursor(0,1);
				lcd.print("Activado");

				lcd.setCursor(0,2);
				lcd.print("Encendido: Ocaso");

				lcd.setCursor(0,3);				
				lcd.print("Apagado:   " );
				imprimirDigitosLCD(horaOffc1);
				lcd.print(":");
				imprimirDigitosLCD(minutoOffc1);
								
				//si hay cualquier otro valor es porque hay un ERROR
			}

			//si hay cualquier otro valor es porque hay un ERROR
			else {
				avisoError(10);
			}						
}


void mostrarPrograma2(){

		
			delay(delayPulsacion);

			lcd.clear();
			lcd.print("Voluntario " + String(menuPosY));
			
			//si  esta programacion horaria esta DESACTIVADA
			if(enC2==0){		
				lcd.setCursor(0,1);
				lcd.print("Desactivado");
			}


			//si  esta programacion horaria esta ACTIVADA
			else if (enC2==1){
				lcd.setCursor(0,1);
				lcd.print("Activado");


				lcd.setCursor(0,2);				
				lcd.print("Encendido: " );
				imprimirDigitosLCD(horaOnC2);
				lcd.print(":");
				imprimirDigitosLCD(minutoOnC2);


				lcd.setCursor(0,3);
				lcd.print("Apagado:   Orto");

				
								
				//si hay cualquier otro valor es porque hay un ERROR
			}

			//si hay cualquier otro valor es porque hay un ERROR
			else {
				avisoError(10);
			}	



}


//edita la programacion horaria correspondiente a menuposy-1
void editarPrograma2(){		
	Serial.println("editar prog 2");
	
	//----------- modificamos on off -------------------
	lcd.setCursor(0,1);		
	lcd.blink_on();
	
	teclaPulsada='0';
	delay(delayPulsacion);

	//minentras no pulsemos ok
	while(teclaPulsada != 'o'){

		teclaPulsada = leerTeclado();	
		

		if((teclaPulsada =='u') | (teclaPulsada == 'd')){
			
			if(enC2==0){			//si el horario esta habilitado
				enC2=1;				//lo deshabilitamos
			}
			else if(enC2==1){	//si el horario esta deshabilitado
				enC2=0;			//lo habilitamos
			}

			teclaPulsada = '0';	
			mostrarPrograma2();
			lcd.setCursor(0,1);		
			delay(delayPulsacion);
		}
	}

	delay(delayPulsacion);
	teclaPulsada='0';

		
	//----------- si es por hora fija --> elegimos a que hora queremos que actue -------------------
	if(enC2==1){
		lcd.setCursor(11,2);

		//establecemos hora
		while(teclaPulsada!='o'){
				delay(delayPulsacion);
				teclaPulsada = leerTeclado();
				if((teclaPulsada == 'u') & (horaOnC2<23)){			//hora ++
					horaOnC2++;
					lcd.setCursor(11,2);
					imprimirDigitosLCD(horaOnC2);
					lcd.setCursor(11,2);
				}
				else if ((teclaPulsada =='d') & (horaOnC2>0)){		//hora --
					horaOnC2--;
					lcd.setCursor(11,2);
					imprimirDigitosLCD(horaOnC2);
					lcd.setCursor(11,2);
				}				
			}

			lcd.setCursor(14,2);


			//establecer minutos
			teclaPulsada='0';
			while (teclaPulsada != 'o')	{
				delay(delayPulsacion);
				teclaPulsada = leerTeclado();
				if((teclaPulsada == 'u') && (minutoOnC2<59)){			//minutos ++
					minutoOnC2++;
					lcd.setCursor(14,2);
					imprimirDigitosLCD(minutoOnC2);
					lcd.setCursor(14,2);
				}
				else if ((teclaPulsada =='d') && (minutoOnC2>0)){		//minutos --
					minutoOnC2--;
					lcd.setCursor(14,2);
					imprimirDigitosLCD(minutoOnC2);
					lcd.setCursor(14,2);
				}
			}
	
			mdiarioC2=(horaOnC2*60)+minutoOnC2;	
	}
			
	//--------------- salimos -----------------------
	teclaPulsada='0';
	delay(delayPulsacion);
	//guardarProgramacionEnEEPROM();
	
	lineas();
	Serial.println("Programacion Modificada");
	siHayInterrupcion();		//comprobamos si hay que actuar sobre alguna salida con la nueva programacion
	teclaPulsada='0';

	lcd.blink_off();


}


//edita la programacion horaria correspondiente a menuposy-1
void editarPrograma1(){		
		
	Serial.println("editar prog 1");
	//----------- modificamos on off -------------------
	lcd.setCursor(0,1);		
	lcd.blink_on();
	
	teclaPulsada='0';
	delay(delayPulsacion);

	//minentras no pulsemos ok
	while(teclaPulsada != 'o'){

		teclaPulsada = leerTeclado();	
		

		if((teclaPulsada =='u') | (teclaPulsada == 'd')){
			
			if(enC1==0){			//si el horario esta habilitado
				enC1=1;			//lo deshabilitamos
			}
			else if(enC1==1){	//si el horario esta deshabilitado
				enC1=0;			//lo habilitamos
			}

			teclaPulsada = '0';	
			mostrarPrograma1();
			lcd.setCursor(0,1);		
			delay(delayPulsacion);
		}
	}

	delay(delayPulsacion);
	teclaPulsada='0';

		
	//----------- si es por hora fija --> elegimos a que hora queremos que actue -------------------
	if(enC1==1){
		lcd.setCursor(11,3);

		//establecemos hora
		while(teclaPulsada!='o'){
				delay(delayPulsacion);
				teclaPulsada = leerTeclado();
				if((teclaPulsada == 'u') & (horaOffc1<23)){		//hora ++
					horaOffc1++;
					lcd.setCursor(11,3);
					imprimirDigitosLCD(horaOffc1);
					lcd.setCursor(11,3);
				}
				else if ((teclaPulsada =='d') & (horaOffc1>0)){		//hora --
					horaOffc1--;
					lcd.setCursor(11,3);
					imprimirDigitosLCD(horaOffc1);
					lcd.setCursor(11,3);
				}				
			}

			lcd.setCursor(14,3);


			//establecer minutos
			teclaPulsada='0';
			while (teclaPulsada != 'o')	{
				delay(delayPulsacion);
				teclaPulsada = leerTeclado();
				if((teclaPulsada == 'u') && (minutoOffc1<59)){		//minutos ++
					minutoOffc1++;
					lcd.setCursor(14,3);
					imprimirDigitosLCD(minutoOffc1);
					lcd.setCursor(14,3);
				}
				else if ((teclaPulsada =='d') && (minutoOffc1>0)){		//minutos --
					minutoOffc1--;
					lcd.setCursor(14,3);
					imprimirDigitosLCD(minutoOffc1);
					lcd.setCursor(14,3);
				}
			}
	
			mdiarioC1=(horaOffc1*60)+minutoOffc1;	
	}
			
	//--------------- salimos -----------------------
	teclaPulsada='0';
	delay(delayPulsacion);
	guardarProgramacionEnEEPROM();
	
	lineas();
	Serial.println("Programacion Modificada");
	siHayInterrupcion();		//comprobamos si hay que actuar sobre alguna salida con la nueva programacion
	teclaPulsada='0';

	lcd.blink_off();
		
}



//sin desarrollar
void cambiarCoordenadasGeograficas(void){
	

}



//sin desarrollar
void establecerCiudad(void){

}

//sin desarrollar
void cambiarZonaHoraria(void){

}




