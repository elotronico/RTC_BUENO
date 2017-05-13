#define led 13
//-----------------------------------------------------
//---	    		TECLAS DEL TECLADO				---
//-----------------------------------------------------
#define delayPulsacion 160

#define btnUp 35
#define btnDown 39
#define btnOk 45
#define btnCancel 47



//-----------------------------------------------------
//---	    			astronomico.ino				---
//-----------------------------------------------------
// what is our longitude (west values negative) and latitude (south values negative)
float const LATITUDE = 42.22;
float const LONGITUDE = -8.81;
int zonaHoraria = 1;

uint8_t tablaOrtoOcaso[4] = {0,0,0,0};

#define horaAmanece tablaOrtoOcaso[0]
#define minutoAmanece tablaOrtoOcaso[1]

#define minutoAnochece tablaOrtoOcaso[2]
#define horaAnochece tablaOrtoOcaso[3]



//-----------------------------------------------------
//---		tabla de horarios de encendidos		    ---
//-----------------------------------------------------


/*
*	0 -> enable/disable [On(1),Off(0)] - indica si el programa esta habilitado o deshabilitado
*	1 -> Salida [1~8]- indica la salida sobre la que actua
*	2 -> Accion [On(1), Off(0)] - indica si activa o desactiva la salida indicada
*	3 -> Tipo horario [astronomico(1), Hora fija(2)] - indica si funciona con el horario astronomico o por horario fijo
*	4 -> On_Hora [00~23] - Hora de encendido para este circuito
*	5 -> On_Minuto [00~59]- minuto de encendido
*	6 -> On_Adelanto/Atraso - adelanto atraso para el encendido de este circuito
*	7 -> Off_Hora - Hora de apagado para este circuito
*	8 -> Off_Minuto - minuto de apagado
*	9 -> Off_Adelanto/Atraso - adelanto atraso para el apagado de este circuito
*	
*/



//-----------------------------

#define horarioEnable  (volatile uint8_t)0				//indica si esta habilitado o no
		#define progHabilitado  (volatile uint8_t)1
		#define progDeshabilitado (volatile uint8_t)0

#define horarioCircuito (volatile uint8_t)1				//indica sobre que circuito actua

#define horarioTipo (volatile uint8_t)2					//indica el funcionamiento [Orto][Ocaso][Hora]
		#define astro (volatile uint8_t)0
		#define orto (volatile uint8_t)1
		#define ocaso (volatile uint8_t)2
		#define horaFija (volatile uint8_t)3

#define horarioAdelanto (volatile uint8_t)3		//adelanto-atraso sobre el orto/ocaso

#define horarioHora (volatile uint8_t)4			//hora en la que enciende

#define horarioMinuto (volatile uint8_t)5			//minuto en el que enciende

#define horarioAccion (volatile uint8_t)6
		#define activar (volatile uint8_t)1
		#define desactivar (volatile uint8_t)2




//un total de 180 posiciones
//y,x
volatile uint8_t tablaHorarioEncendidos[][20]={
		{1, 1, 1, 1, 1, 1, 1, 1, 1},		//1
		{1, 2, 1, 1, 1, 1, 2, 1, 1},		//2
		{1, 3, 1, 1, 1, 1, 2, 1, 1},		//3
		{1, 4, 1, 1, 1, 1, 1, 1, 1},		//4
		{1, 5, 1, 1, 1, 1, 1, 1, 1},		//5
		{1, 6, 1, 1, 1, 1, 1, 1, 1},		//6
		{1, 7, 1, 1, 1, 1, 1, 1, 1},		//7
		{1, 8, 1, 1, 1, 1, 1, 1, 1},		//8
		{1, 9, 1, 1, 1, 1, 1, 1, 1},		//9
		{1, 10, 2, 1, 1, 1, 1, 1, 1},		//11
		{1, 11, 3, 1, 1, 1, 1, 1, 1},		//11
		{1, 12, 1, 1, 1, 1, 1, 1, 1},		//12
		{1, 13, 1, 1, 1, 1, 1, 1, 1},		//13
		{1, 14, 1, 1, 1, 1, 1, 1, 1},		//14
		{1, 15, 1, 1, 1, 1, 1, 1, 1},		//15
		{1, 16, 1, 1, 1, 1, 1, 1, 1},		//16
		{1, 17, 1, 1, 1, 1, 1, 1, 1},		//17
		{1, 18, 1, 1, 1, 1, 1, 1, 1},		//18
		{1, 19, 1, 1, 1, 1, 1, 1, 1},		//19
		{1, 20, 1, 1, 1, 1, 1, 1, 1}		//20
								
};

//aqui guardamos temporalmente las horas fijas de actuacion de los 20 programas (se usen o no)
int mdiarioProgramacionDesord[20]={};

//aqui gurdamos la programacion de horas fijas ordenado.
 int mdiarioC1ordenado[20]={};
 int mdiarioC2ordenado[20]={};
 int mdiarioC3ordenado[20]={};
 int mdiarioC4ordenado[20]={};
 int mdiarioC5ordenado[20]={};
 int mdiarioC6ordenado[20]={};
 int mdiarioC7ordenado[20]={};
 int mdiarioC8ordenado[20]={};


//-----------------------------------------------------
//---		fecha y hora actual. leido de RTC	    ---
//-----------------------------------------------------

volatile uint8_t tablaHoraActual[5]={00,00,1,1,1};

#define horaActual tablaHoraActual[0]
#define minutoActual tablaHoraActual[1]
#define diaDeSemana tablaHoraActual[2]
#define mesActual tablaHoraActual[3]
#define diaActual tablaHoraActual[4]


int anoActual = 2016;

//minutos dek dia a los que suceden [0-1440]
int mdiarioAmanece=0;
int mdiarioAnochece=0;
int mdiarioHora=0;		//este es el minuto dek dia en el que estamos en cada instante


//-----------------------------------------------------
//---			definiciones para el menu			---
//-----------------------------------------------------

unsigned int menuPosX = 0;
unsigned int menuPosY = 0;

const int longMenuPpal=4;
int largoSubmenus[(longMenuPpal+1)]={0,2,20,3,4};
char teclaPulsada = '0';

uint8_t numeroDiasMes[14]={0,31,28,31,30,31,30,31,31,30,31,30,31,29};
uint8_t minutoAnterior;




//-----------------------------------------------------
//---					MISCELANEA					---
//-----------------------------------------------------
//#define alarmPin 12

LiquidCrystal_I2C lcd(0X27,20,4);

char *monthName[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

enum diasSemana
{Lu,Ma,Mi,Ju,Vi,Sa,Do
};
char botonPulsado = '0';

#define RTCpinInt 2			//pin al que esta conectado la interrupcion del RTC




//-----------------------------------------------------
//---					E/S					---
//-----------------------------------------------------




bool StateS1 = LOW;
bool StateS2 = LOW;
bool StateS3 = LOW;
bool StateS4 = LOW;
bool StateS5 = LOW;
bool StateS6 = LOW;
bool StateS7 = LOW;
bool StateS8 = LOW;


#define salida1 PF0
#define salida2 PF1
#define salida3 PF2
#define salida4 PF3
#define salida5 PF4
#define salida6 PF5
#define salida7 PF6
#define salida8 PF7









