// 
// 
// 

//#include "menus.h"






int versubmenu(){
	if(menuPosicionActualX < submenuLongitud[menuTamanoMatrizY])
	{
		menuPosicionActualY++;	
	}



}


void menuActualizar(void)
{
	Serial.println("X:" + (String)menuPosicionActualX + "  Y:" + (String)menuPosicionActualY);

	lcd.clear();
	lcd.print(menuLista[0][menuPosicionActualY][menuPosicionActualX]);
	
	lcd.setCursor(1,1);
	lcd.print(menuLista[1][menuPosicionActualY][menuPosicionActualX]);

}







