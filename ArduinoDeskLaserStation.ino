

// Visual Micro is in vMicro>General>Tutorial Mode
// 
/*
Name:       reception.ino
Created:	09/10/2018 13:57:02
Author:     LINKT\thomasc
*/

// Define User Types below here or use a .h file
//
#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_NeoPixel.h>
#include "var.h"
#include <SoftwareSerial.h>





Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PINCOLOR, NEO_GRB + NEO_KHZ800);
int j = 0;
String text = "";
int r = 0;
int g = 0;
int b = 0;
int lumi = 0;
String pseudo = "";
String id = "";
int tempo = 10000;
LiquidCrystal_I2C lcd(LCDADDR, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address
SoftwareSerial esp8266(ESP_RX, ESP_TX);

void setup()
{
	lcd.begin(16, 2);
	lcd.home();// go home
	lcd.print("Initialisation");
	pixels.begin();
	pixels.setBrightness(BRIGHTNESS);
	/*ledColor(255, 255, 255, 0);
	delay(1000);
	ledColor(0, 0, 0, 0);
	delay(1000);
	ledColor(255, 255, 255, 0);
	delay(1000);
	ledColor(0, 0, 0, 0);
	delay(1000);
	*/ledColor(255, 255, 255, 0);
	lcd.clear();
	lcd.home();
	lcd.print("Config Cible");
	pinMode(LASER, OUTPUT);
	pinMode(int(C_AVANT), INPUT);
	pinMode(int(C_EPAULE), INPUT);
	pinMode(int(C_PISTOLET), INPUT);
	pinMode(ESP_START, INPUT);
	j = 0;

	Serial.begin(SERIALBAUDS);
	while (!Serial) {
		;
	}
	esp8266.begin(SERIALBAUDS);
	while (!esp8266) {
		;
	}

	i_C_AVANT = 0;
	i_C_EPAULE = 0;
	i_C_PISTOLET = 0;

	lcd.clear();
	lcd.home();
	lcd.print("Pret");

}
void ledColor(int r, int v, int b, int time) {
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
	ledColor(r, g, b, int(TIME));
	lcd.clear();
	
}

String message(String msg) {
	dialog = msg.substring(msg.indexOf(";") + 1, msg.length());

	msg = dialog.substring(0, dialog.indexOf(";"));
	return msg;
}
// Add the main program code into the continuous loop() function
void loop()
{
	if(digitalRead(ESP_START) == 1) {
		if (tempo > 0) {
			lcd.clear();
			lcd.home();
			lcd.print("Demarrage !!");
			ledColor(0, 0, 0, 0);
			ledColor(r, g, b, tempo / 16);
			lcd.clear();
			lcd.home();
			lcd.print("Go");
			tempo = 0;
		}
		
		//call reception capteur
		i_C_AVANT = recepteur(i_C_AVANT, int(C_AVANT), tab_C_AVANT);
		i_C_EPAULE = recepteur(i_C_EPAULE, int(C_EPAULE), tab_C_EPAULE);
		i_C_PISTOLET = recepteur(i_C_PISTOLET, int(C_PISTOLET), tab_C_PISTOLET);
		
		//si cible avant touch
		if (i_C_AVANT == 13) {
			ecriture(tab_C_AVANT, " cible avant", i_C_AVANT);
			i_C_AVANT = 0;
		}
		//sinon si cible epaule touch
		else if (i_C_EPAULE == 13) {
			ecriture(tab_C_EPAULE, " cible epaule", i_C_EPAULE);
			i_C_EPAULE = 0;
		}
		//sinon si cible pistolet touch
		else if (i_C_PISTOLET == 13) {
			ecriture(tab_C_PISTOLET, " cible pistolet", i_C_PISTOLET);
			i_C_PISTOLET = 0;
		}//sinon shoot
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
	if (digitalRead(ESP_START) == 0) {
		if (esp8266.available()){
			//Serial.println("available");
			dialog = esp8266.readString();
			Serial.println(dialog);
			
			if (dialog.startsWith(String(CMD_START), 0)){
				if (dialog.substring(1, 2) == CMD_TEAM) {
					while(dialog.indexOf(";") > 0) {
						r = message(dialog).toInt();
						g = message(dialog).toInt();
						b = message(dialog).toInt();
						lumi = message(dialog).toInt();
						pseudo = message(dialog);
						id = message(dialog);
						dialog = "";
						ledColor(r, g, b, 0);
						lcd.clear();
						lcd.home();
						lcd.print(String(pseudo));
					}
				}
				else if (dialog.substring(1, 2) == CMD_PARTY) {
					while (dialog.indexOf(";") > 0) {
						TIME = (message(dialog).toInt() * 1000) / 16;
						tempo = message(dialog).toInt() * 1000;
					}
				}
				else if (dialog.substring(1, 2) == CMD_TEAM) {
					while (dialog.indexOf(";") > 0) {

					}
				}
			}
			else {
				dialog = "";
			}
		}
	}
}
