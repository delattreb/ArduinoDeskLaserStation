

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
#include <Adafruit_NeoPixel.h>
#include "var.h"


Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PINCOLOR, NEO_GRB + NEO_KHZ800);
int j = 0;
String text = "";
LiquidCrystal_I2C lcd(LCDADDR, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address
void setup()
{
	lcd.begin(16, 2);
	lcd.home();// go home
	lcd.print("DEBUT");
	pixels.begin();
	pixels.setBrightness(BRIGHTNESS);
	ledColor(60, 180, 150, 0);
	ledColor(0, 0, 0, 0);
	delay(50);
	ledColor(0, 180, 150, 0);
	delay(100);
	ledColor(0, 0, 0, 0);
	delay(100);
	ledColor(0, 180, 150, 0);

	pinMode(int(LASER), OUTPUT);
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
void ledColor(int time, int r, int v, int b) {
	for (int i = 0;i < NUMPIXELS;i++) {
		pixels.setPixelColor(i, pixels.Color(r, v, b)); // Moderately bright green color.

		pixels.show();
		delay(time);
	}
}
void zero()
{
	digitalWrite(int(LASER), LOW);

}

void one()
{
	digitalWrite(int(LASER), HIGH);

}

int recepteur(int i, int cible, bool tab[13]) {
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
void ecriture(bool tab[13], String cible, int j) {
	//si ensemble trouve affichage
	for (size_t i = 0; i < 13; i++)
	{
		//Serial.println(char(tab[i]));
		//concat entete +id en string
		text.concat(String(tab[i]));
	}

	//ecriture log
	lcd.home();// go home
	lcd.print(text);
	lcd.setCursor(0, 1);
	lcd.print(cible);
	text = "";
	zero();
	ledColor(0, 0, 0, 0);
	ledColor(int(TIME), 180, 150, 0);
	lcd.clear();
	
}
// Add the main program code into the continuous loop() function
void loop()
{
	i_C_AVANT = recepteur(i_C_AVANT, int(C_AVANT), tab_C_AVANT);
	i_C_EPAULE = recepteur(i_C_EPAULE, int(C_EPAULE), tab_C_EPAULE);
	i_C_PISTOLET = recepteur(i_C_PISTOLET, int(C_PISTOLET), tab_C_PISTOLET);

	if (i_C_AVANT == 13) {
		ecriture(tab_C_AVANT, " cible avant", i_C_AVANT);
		i_C_AVANT = 0;
	}
	else if (i_C_EPAULE == 13) {
		ecriture(tab_C_EPAULE, " cible epaule", i_C_EPAULE);
		i_C_EPAULE = 0;
	}
	else if (i_C_PISTOLET == 13) {
		ecriture(tab_C_PISTOLET, " cible pistolet", i_C_PISTOLET);
		i_C_PISTOLET = 0;
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
