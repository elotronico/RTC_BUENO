#include <Wire.h>
#include <LiquidCrystal_I2C.h>


/*
*				PARA MANEJAR EL MENU, SE UTILIZAN DOS COORDENADAS (X,Y) QUE SE VAN INCREMENTANDO O 
*				DECREMENTADO CON LOS PULSADORES.
*				
*				VARIABLES:
*				- unsigned int menuPosX = 0;
*				- unsigned int menuPosY = 0;
*				- const int longMenuPpal=4;								//en realidad son 5 elementos (0,1,2,3,4)
*				- int largoSubmenus[(longMenuPpal+1)]={4,6,5,6,4};		//valor [0]=4 pero en realidad son 5 elementos(0.0  0.1  0.2  0.3  0.4)
*																
*																			
*																			
*					
*
*		Menu 0.0 -------- Menu 1.0 -------- Menu 2.0 -------- Menu 3.0 -------- Menu 4.0		<------ MENU PRINCIPAL															
*			|				  |					|				  |					|			
*			|				  |					|				  |					|		    \
*		Menu 0.1 		  Menu 1.1 		   Menu 2.1 		  Menu 3.1 			 Menu 4.1		 |
*			|				  |					|				  |					|			 |
*			|				  |					|				  |					|			 |
*		Menu 0.2 		  Menu 1.3 		   Menu 2.3 		  Menu 3.3			 Menu 4.3		 |
*			|				  |					|				  |					|			 |
*			|				  |					|				  |					|			 |  <-- SUBMENUS
*		Menu 0.3 		  Menu 1.4 		   Menu 2.4 		  Menu 3.4			 Menu 4.4		 |
*			|				  |					|				  |								 |
*			|				  |					|				  |								 |
*		Menu 0.4 		  Menu 1.5 		   Menu 2.5 		  Menu 3.5							 |
*							  |									  |								 |
*							  |									  |								 |
						  Menu 1.6							  Menu 3.6	  						 |
*							  									  								/
*																			
*		
*/

unsigned int menuPosX = 0;
unsigned int menuPosY = 0;

const int longMenuPpal=4;
int largoSubmenus[(longMenuPpal+1)]={2,3,2,2,3};
char teclaPulsada = '0';


#define btnUp 22			//'u'
#define btnDown 23			//'d'
#define btnOK 24			//'o'
#define btnCancel 25		//'c'




LiquidCrystal_I2C lcd(0x27,16,2);


void setup()
{ 

	pinMode(btnCancel,INPUT);
	pinMode(btnOK,INPUT);
	pinMode(btnUp,INPUT);
	pinMode(btnDown,INPUT);
	lcd.begin();
	actualizarMenuLcd();
	
}

void loop()
{
	delay(200);
	teclaPulsada = leerTeclado();

	if(teclaPulsada != '0')
	{	
		Serial.println();
		Serial.println("TelcaPulsada: " + (String)teclaPulsada);
		actualizarPosicionMenu();
		teclaPulsada = '0';
	}


}

void actualizarPosicionMenu()
{

	Serial.println("Cursor antes: " + (String)menuPosX + "," + (String)menuPosY);
	
	//estamos en el menu principal
	if(menuPosY==0)
	{
		if(teclaPulsada== 'd' && (menuPosX<longMenuPpal))
		{
			Serial.println("posx++");
			menuPosX++;	
		}
	
		else if(teclaPulsada== 'u' && (menuPosX>0))
		{
			Serial.println("posx--");
			menuPosX--;
		}

		else if(teclaPulsada =='c')
		{
			menuPosX=0;
		}

		else if (teclaPulsada == 'o')
		{
			menuPosY++;
		}
	}

	//estamos en el submenu
	else		
	{
		if(teclaPulsada=='d' && menuPosY < largoSubmenus[menuPosX])
		{
			menuPosY++;
		}

		else if (teclaPulsada=='u' && menuPosY > 1)
		{
			menuPosY--;
		}

		else if (teclaPulsada == 'c')
		{
			menuPosY=0;
		}
		
		else if (teclaPulsada == 'o')
		{
		accionMenu();
		}
	
	
	}

	Serial.println("Cursor despues: " + (String)menuPosX + "," + (String)menuPosY);
	

	actualizarMenuLcd();

}

void accionMenu()
{
	if(menuPosX==1 && menuPosY==1)		//poner en hora el reloj
	{
		RTCponerEnHoraLCD();
	}

}

void RTCponerEnHoraLCD()
{
	unsigned int ano = 2016,mes=1,dia=1,hora=00,minutos=00;


	lcd.clear();
	//lcd.cursor_on();
	lcd.blink_on();
	lcd.print("Anho: " + (String)ano );
	delay(2000);
	lcd.blink_off();

}

void avisoError(int codigoError)
{

}

void actualizarMenuLcd()
{
	lcd.clear();

	//--------------MENU 0---------------------------
	if(menuPosX == 0)	//menu ppal
	{
		if		(menuPosY==0)							//menu 0.0
		{
			lcd.print("Menu 0.0");
		}

		else if(menuPosY==1)					//menu 0.1
		{
			lcd.print("Menu 0.1");
		}
		else if(menuPosY==2)					//menu 0.1
		{
			lcd.print("Menu 0.2");
		}
		else
		{
			avisoError(1);
		}
	}

	//--------------MENU 1---------------------------
	else if(menuPosX == 1)	//menu ppal
	{
		if(menuPosY==0)						//menu 1.0
		{
			lcd.print("Reloj");
		}
		
		else if(menuPosY==1)				//menu 1.1
		{
			lcd.print("Poner en hora");
		}
		
		else if(menuPosY==2)				//menu 1.2
		{
			lcd.print("vacio");
		}

		else if(menuPosY==3)				//menu 1.3
		{
			lcd.print("vacio");
		}

		else
		{
			avisoError(1);
		}

	}

	//--------------MENU 2---------------------------
	else if(menuPosX == 2)	//menu ppal
	{
		if		(menuPosY==0)			//menu 2.0
		{
			lcd.print("Menu 2.0");		
		}
		
		else if(menuPosY==1)			//menu 2.1
		{
			lcd.print("Menu 2.1");
		}
		
		else if(menuPosY==2)			//menu 2.2
		{
			lcd.print("Menu 2.2");
		}

		else
		{
			avisoError(1);
		}
	}

	//--------------MENU 3---------------------------
	else if(menuPosX == 3)	//menu ppal
	{
		if(menuPosY==0)					//menu 3.0
		{
			lcd.print("Menu 3.0");
		}
		
		else if(menuPosY==1)			//menu 3.1
		{
			lcd.print("Menu 3.1");
		}
		
		else if(menuPosY==2)			//menu 3.2
		{
			lcd.print("Menu 3.2");
		}
		
		else
		{
			avisoError(1);
		}
	}

	//--------------MENU 4---------------------------
	else if(menuPosX == 4)	//menu ppal
	{
		if	   (menuPosY==0)			//menu 4.0
		{
			lcd.print("Menu 4.0");
		}
		
		else if(menuPosY==1)			//menu 4.1
		{
			lcd.print("Menu 4.1");
		}

		else if(menuPosY==2)			//menu 4.2
		{
			lcd.print("Menu 4.2");
		}

		else if(menuPosY==3)			//menu 4.3
		{
			lcd.print("Menu 4.3");
		}

		else
		{
			avisoError(1);
		}
	}

	else
	{
		avisoError(1);
	}



}


char leerTeclado(void)
{
	if		(digitalRead(btnUp) == HIGH)
	{
		return 'u';
	}

	else if (digitalRead(btnDown)==HIGH)
	{
		return 'd';
	}


	else if (digitalRead(btnOK)==HIGH)
	{
		return 'o';
	}


	else if (digitalRead(btnCancel)==HIGH)
	{
		return 'c';	
	}

	// no se ha pulsado tecla o se han pulsado dos teclas
	else
	{
		return '0';
	}


}
