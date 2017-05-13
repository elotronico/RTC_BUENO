

//desactiva la salida del valor que recibe
void activarSalida(uint8_t salida){
	if(salida <=8){
		digitalWrite(salida,HIGH);
		//Serial.println("salida " + (String)salida + " actviada");
		
		if(salida==1)
			StateS1=HIGH;
		else if(salida==2)
			StateS2=HIGH;
		else if(salida==3)
			StateS3=HIGH;
		else if(salida==4)
			StateS4=HIGH;
		else if(salida==5)
			StateS5=HIGH;
		else if(salida==6)
			StateS6=HIGH;
		else if(salida==7)
			StateS7=HIGH;
		else if(salida==8)
			StateS8=HIGH;

	}
}


//activa la salida del valor que recibe
void desactivarSalida(uint8_t salida){
		if(salida <=8){
		digitalWrite(salida,LOW);
		//Serial.println("salida " + (String)salida + " desactviada");

		if(salida==1)
			StateS1=LOW;
		else if(salida==2)
			StateS2=LOW;
		else if(salida==3)
			StateS3=LOW;
		else if(salida==4)
			StateS4=LOW;
		else if(salida==5)
			StateS5=LOW;
		else if(salida==6)
			StateS6=LOW;
		else if(salida==7)
			StateS7=LOW;
		else if(salida==8)
			StateS8=LOW;
	}
}


void enviaSerialEstadoSalidas(void){


	Serial.println("--------------------------");
	Serial.println("       ESTADO DE SALIDAS   ");
	Serial.println("--------------------------");


		Serial.print("Salida 1: ");
		if(StateS1==HIGH){
			Serial.println("Activa");
		}
		else{
			Serial.println("Inactiva");
		}

		//------------
		Serial.print("Salida 2: ");
		if(StateS2==HIGH){
			Serial.println("Activa");
		}
		else{
			Serial.println("Inactiva");
		}

		//------------
		Serial.print("Salida 3: ");
		if(StateS3==HIGH){
			Serial.println("Activa");
		}
		else{
			Serial.println("Inactiva");
		}

		//------------
		Serial.print("Salida 4: ");
		if(StateS4==HIGH){
			Serial.println("Activa");
		}
		else{
			Serial.println("Inactiva");
		}

		//------------
		Serial.print("Salida 5: ");
		if(StateS5==HIGH){
			Serial.println("Activa");
		}
		else{
			Serial.println("Inactiva");
		}

		//------------
		Serial.print("Salida 6: ");
		if(StateS6==HIGH){
			Serial.println("Activa");
		}
		else{
			Serial.println("Inactiva");
		}

		//------------
		Serial.print("Salida 7: ");
		if(StateS7==HIGH){
			Serial.println("Activa");
		}	
		else{
			Serial.println("Inactiva");
		}

		//------------
		Serial.print("Salida 8: ");
		if(StateS8==HIGH){
			Serial.println("Activa");
		}
		else{
			Serial.println("Inactiva");
		}


		Serial.println("--------------------------");
		Serial.println("");

}