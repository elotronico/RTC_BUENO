

//desactiva la salida del valor que recibe
void activarSalida(uint8_t salida){

	if(salida <=8){
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


//-----------------------------------------------
//actualiza el estado de las salidas
//escribe 0 o 1 segun corresponda
//-----------------------------------------------
void refrescarSalidas(){

		if(StateS1==HIGH){
			digitalWrite(salida1,HIGH);
		}
		else{
			digitalWrite(salida1,LOW);
		}
//----------------		
		if(StateS2==HIGH){
			digitalWrite(salida2,HIGH);
		}
		else{
			digitalWrite(salida2,LOW);
		}
//----------------
		if(StateS3==HIGH){
			digitalWrite(salida3,HIGH);
		}
		else{
			digitalWrite(salida3,LOW);
		}
//----------------
		if(StateS4==HIGH){
			digitalWrite(salida4,HIGH);
		}
		else{
			digitalWrite(salida4,LOW);
		}
//----------------
		if(StateS5==HIGH){
			digitalWrite(salida5,HIGH);
		}
		else{
			digitalWrite(salida5,LOW);
		}
//----------------
		if(StateS6==HIGH){
			digitalWrite(salida6,HIGH);
		}
		else{
			digitalWrite(salida6,LOW);
		}
//----------------
		if(StateS7==HIGH){
			digitalWrite(salida7,HIGH);
		}
		else{
			digitalWrite(salida7,LOW);
		}
//----------------
		if(StateS8==HIGH){
			digitalWrite(salida8,HIGH);
		}
		else{
			digitalWrite(salida8,LOW);
		}

}


void enviaSerialEstadoSalidas(void){


	lineas();
	Serial.println("       ESTADO DE SALIDAS   ");
	lineas();


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


		lineas();
		Serial.println("");

}