
void printDigits(int digits){
  // utility function for digital clock display: prints preceding colon and leading 0
  Serial.print(":");
  if(digits < 10)
    Serial.print('0');
  Serial.print(digits);

}




void ponerEnHora(uint8_t dia, uint8_t mes, uint8_t ano, uint8_t hora, uint8_t minutos, uint8_t segundos)
{
  tmElements_t tmSet;
  tmSet.Year = ano - 1970;
  tmSet.Month = mes;
  tmSet.Day = dia;
  tmSet.Hour = hora;
  tmSet.Minute = minutos;
  tmSet.Second = 0;

  RTC.set(makeTime(tmSet), CLOCK_ADDRESS); // set the clock

  RTC.freqSelect(1);  // set the squarewave freq on alarm pin b to 4.096kHz


}



void ponerHoraAlarma(uint8_t dia, uint8_t mes, uint8_t ano, uint8_t hora, uint8_t minutos, uint8_t segundos)
{
	tmElements_t tmSet;
	tmSet.Year = ano - 1970;
	tmSet.Month = mes;
	tmSet.Day = dia;
	tmSet.Hour = hora;
	tmSet.Minute = minutos;
	tmSet.Second = 0;

	RTC.set(makeTime(tmSet), ALARM1_ADDRESS); // set the alarm for 4 seconds later

	RTC.enableAlarm(ALARM1_ADDRESS);
}



void leerHora()
{
  time_t clock = RTC.get(CLOCK_ADDRESS);
  time_t alarm = RTC.get(ALARM1_ADDRESS);  // get the time the alarm is set for
  tmElements_t clockSet;
  tmElements_t alarmSet;
  breakTime(clock, clockSet);
  breakTime(alarm, alarmSet);

  //print the time using Time.h
  Serial.print((int)clockSet.Day);
  Serial.print(" ");
  Serial.print((int)clockSet.Month);//monthName[month() - 1]);
  Serial.print(" ");
  Serial.print((int)(1970+clockSet.Year));//year());
  Serial.print(" ");
  Serial.print((int)clockSet.Hour);//hour());
  printDigits(clockSet.Minute);//minute());
  printDigits(clockSet.Second);//second());
  Serial.println("\t");

  lcd.clear();
  imprimirEloy(clockSet.Day, clockSet.Month, clockSet.Year, clockSet.Hour, clockSet.Minute);

}




void leerAlarma(void)
{

	time_t clock = RTC.get(CLOCK_ADDRESS);
	time_t alarm = RTC.get(ALARM1_ADDRESS);  // get the time the alarm is set for
	tmElements_t clockSet;
	tmElements_t alarmSet;
	breakTime(clock, clockSet);
	breakTime(alarm, alarmSet);
	

	// print the alarm time
	Serial.print("ALARM1: ");
	Serial.print((int)alarmSet.Day);
	Serial.print(" ");
	Serial.print((int)alarmSet.Hour);
	printDigits(alarmSet.Minute);
	printDigits(alarmSet.Second);
	Serial.print("\t");
  
	if(digitalRead(alarmPin) == HIGH)		//pin is set low when alarm is triggered
	{  
	Serial.println("ALARM off");
	}
	else
	{
	Serial.println("ALARM on");
	RTC.resetAlarms();
	}
  
}







void imprimirEloy(uint8_t dia, uint8_t mes,uint8_t ano, uint8_t hora, uint8_t minutos)
{
	////imprimimos la fecha
	lcd.setCursor(3,0);
	//imprime dia
	if(dia<10)
	{	lcd.print("0" + (String)dia + ":");	}
	else
	{	lcd.print((String)dia + ":"); }
	
	//imprime mes
	if(mes<10)
	{	lcd.print("0" + (String)mes + ":");	}
	else
	{	lcd.print((String)mes + ":"); }
	
	//imprime año
	if(ano<10)
	{	lcd.print("0" + (String)ano);	}
	else
	{	lcd.print((String)ano); }
	

	////imprimimos la hora
	lcd.setCursor(4,1);
	//imprime hora
	if(hora<10)
	{	lcd.print("0" + (String)hora + ":");	}
	else
	{	lcd.print((String)hora + ":"); }
	
	//imprime minutos
	if(minutos<10)
	{	lcd.print("0" + (String)minutos);	}
	else
	{	lcd.print((String)minutos); }



}
