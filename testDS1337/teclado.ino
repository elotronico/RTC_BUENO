//int botonPulsado = '0';


char leerTeclado(void){
	if	(digitalRead(btnUp) == HIGH){
		return 'u';
	}

	else if (digitalRead(btnDown)==HIGH){	
		return 'd';
	}


	else if (digitalRead(btnOk)==HIGH){	
		return 'o';
	}


	else if (digitalRead(btnCancel)==HIGH){
		return 'c';	
	}

	// no se ha pulsado tecla o se han pulsado dos teclas
	else{	
		return '0';
	}


}
