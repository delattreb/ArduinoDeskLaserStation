

// Visual Micro is in vMicro>General>Tutorial Mode
// 
/*
	Name:       reception.ino
	Created:	09/10/2018 13:57:02
	Author:     LINKT\thomasc
*/

// Define User Types below here or use a .h file
//
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// Define Function Prototypes that use User Types below here or use a .h file
//


// Define Functions below here or use other .ino or cpp files
//
//Reception

#define SERIALBAUDS 9600
static int const C_AVANT = 5;
static int const C_EPAULE = 6;
static int const C_PISTOLET = 7;
int i = 0;
bool tab[13] = { 1,1,1,1,1,1,1,0,0,0,0,0,0 };
String text = "";

//laser
#define PULSE 50;
static int const LASER = 4;
static int const TIME = 4000;
int j = 0;
bool tabID[13] = { 1,1,1,1,1,1,1,0,0,0,1,1,0 };



//lcd
#define BACKLIGHT_PIN 13
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address



// The setup() function runs once each time the micro-controller starts
void setup()
{
	lcd.begin(16, 2);
	;	pinMode(int(LASER), OUTPUT);
	j = 0;


	// Print a message to the LCD.

	Serial.begin(9600);
	while (!Serial) {
		;
	}
	i = 0;
	pinMode(int(C_AVANT), INPUT);


}
void zero()
{
	digitalWrite(int(LASER), LOW);

}

void one()
{
	digitalWrite(int(LASER), HIGH);

}
// Add the main program code into the continuous loop() function
void loop()
{
	//search entete
	if (i < 7) {
		if (digitalRead(int(C_AVANT))) {
			//si 1 increment
			i++;
		}
		else {
			//si 0 retour
			i = 0;
		}
	}//si find entete
	else {
		//ecriture dans le tableau du resultat
		tab[i] = digitalRead(int(C_AVANT));
		i++;
	}


	if (i == 13) {
		//si ensemble trouve affichage

		for (size_t i = 0; i < 13; i++)
		{
			//concat entete +id en string
			text.concat(String(tab[i]));
		}
		//ecriture log
		lcd.home();                   // go home
		lcd.print(text);
		text = "";
		i = 0;
		zero();
		delay(int(TIME));
		lcd.home();                   // go home
		lcd.print("");
		delay(int(TIME));
	}
	else {
		if (j > 12) { j = 0; }
		if (tabID[j] == 1) {
			one();
		}
		else {
			zero();
		}
		j++;
	}
}
