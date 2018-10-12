

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
#include "var.h"

void setup()
{
	lcd.begin(16, 2);
	;	pinMode(int(LASER), OUTPUT);
	j = 0;

	Serial.begin(SERIALBAUDS);
	while (!Serial) {
		;
	}
	i_C_AVANT = 0;
	i_C_EPAULE = 0;
	i_C_PISTOLET = 0;
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
int recepteur(int i, int cible, bool tab[]) {
	if (i < 7) {
		if (digitalRead(cible)) {
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
		tab[i] = digitalRead(cible);
		i++;
	}
	return i;

}

// Add the main program code into the continuous loop() function
void loop()
{

	i_C_AVANT = recepteur(i_C_AVANT, int(C_AVANT), tab_C_AVANT);
	i_C_EPAULE = recepteur(i_C_EPAULE, int(C_EPAULE), tab_C_EPAULE);
	i_C_PISTOLET = recepteur(i_C_PISTOLET, int(C_PISTOLET), tab_C_PISTOLET);

	if (i_C_AVANT == 13) {
		//si ensemble trouve affichage

		for (size_t i = 0; i < 13; i++)
		{
			//concat entete +id en string
			text.concat(String(tab_C_AVANT[i]));
		}
		//ecriture log
		lcd.home();                   // go home
		lcd.print(text);
		text = "";
		i_C_AVANT = 0;
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
	//delay(0);
}
