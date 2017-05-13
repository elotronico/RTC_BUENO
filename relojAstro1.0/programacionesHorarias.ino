

void revisaProgramaciones(){

	//--------------------------------------
	//		circuito astronomico
	//--------------------------------------
	if(mdiarioAmanece>mdiarioHora || mdiarioHora>=mdiarioAnochece){
		activarSalida(1);					
	}		
	else{
		desactivarSalida(1);
	}

	//--------------------------------------
	//	circuito voluntario 1 (ocaso - hora)
	//--------------------------------------
	if(enC1==1){
		//el circuito apaga pasada medianoche
		if(mdiarioC1<mdiarioAnochece){
			
			//si es pasado el ocaso y antes de medianoche
			if(mdiarioHora>=mdiarioAnochece){
				activarSalida(2);
			}
			//si es de madrugada
			else{ 
				//y antes del amanecer
				if(mdiarioHora<mdiarioAmanece){
					if(mdiarioHora<mdiarioC1){
						activarSalida(2);
					
					}
					else{
						desactivarSalida(2);
					}
				
				}
				else{
					desactivarSalida(2);
				}			
			}
		}

		//el circuito apaga antes de medianoche
		else{
			if(mdiarioC1 > mdiarioAnochece){
				if(mdiarioHora>=mdiarioAnochece){
					if(mdiarioHora<mdiarioC1){
						activarSalida(2);
					}
					else{
						desactivarSalida(2);
					}				
				}
				else{
					desactivarSalida(2);
				}
			}
		}
		
		
		
		
		
		
	}
	else{
	desactivarSalida(2);
	}
	


	//--------------------------------------
	//	circuito voluntario 2 (hora - orto)
	//--------------------------------------
	//si esl programa esta habilitado
	if(enC2==1){

		//si sel circuito enciente antes de medianoche
		if(mdiarioC2>mdiarioAmanece){
			
			//si la hora actual es desde las 00:00 hasta el amanecer--> activa la salida, ya que enciende el dia anterior
			if(mdiarioHora<mdiarioAmanece){
				activarSalida(3);			
			}

			//si estamos en el dia anterior
			else{
				//y  la hora actual es mayor que la hora programada de encendido
				if(mdiarioHora>=mdiarioC2){
					
					//y es despues del anochecer
					if(mdiarioHora>=mdiarioAnochece){
						activarSalida(3);
					}
				}
				else{
					desactivarSalida(3);
				}			
			}
		}

		//si el circuito enciende despues de medianoche
		else{
			if(mdiarioHora>=mdiarioC2){
				if(mdiarioHora<mdiarioAmanece){
					activarSalida(3);
				}
				else{
					desactivarSalida(3);
				}
			}
			else{
				desactivarSalida(2);
			}		
		}	
	}

	//si el programa esta deshabilitado
	else{
		desactivarSalida(3);
	}


	//actualiza el estado de las salidas
	refrescarSalidas();

}



//bueno
//comprobamos si es despues del ocas
//si esdespues del ocaso devuelve 1
// sino devuelve 0
bool esDespuesOcaso(void){
	
	if(mdiarioHora>=mdiarioAnochece){
		return true;
	}
	else {
		return false;
	}


	//otro metodo
	/*
	//si es cualquier hora mayor que la hora de anochecer
	if(horaActual>(horaAnochece+1)){
		return true;
	}

	//si es la misma hora que la de anochecer
	else if(horaActual==horaAnochece){

		//y si el minuto es igual o mayor al de ocaso
		if(minutoActual >= minutoAnochece){
			return true;
		}
		//si la hora es igual pero el minuto es distinto
		else {
			return false;
		}
	}

	//si la hora actual es menor que la de anochecer
	else {
		return false;
	}
	*/

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

	if(mdiarioHora<mdiarioAmanece){
		return true;
	}
	else
	{
		return false;
	}



	//otro metodo
	/*
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
	*/


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




