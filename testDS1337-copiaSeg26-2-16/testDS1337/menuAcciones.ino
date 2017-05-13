
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
						if((teclaPulsada == 'u') && (tablaHorarioEncendidos[menuPosY][horarioHora]<23)){		//hora ++
							tablaHorarioEncendidos[menuY][horarioHora]++;
							lcd.setCursor(13,3);
							imprimirDigitosLCD(tablaHorarioEncendidos[menuY][horarioHora]);
							lcd.setCursor(13,3);
						}
						else if ((teclaPulsada =='d') && (tablaHorarioEncendidos[menuY][horarioHora]>0)){		//hora --
							tablaHorarioEncendidos[menuPosY][horarioHora]--;
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




