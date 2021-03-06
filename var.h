#pragma once
#define SERIALBAUDS 9600


//cible avant
static int const C_AVANT = 5;
int i_C_AVANT = 0;
bool tab_C_AVANT[13] = { 1,1,1,1,1,1,1,0,0,0,0,0,0 };
//cible epaule
static int const C_EPAULE = 6;
int i_C_EPAULE = 0;
bool tab_C_EPAULE[13] = { 1,1,1,1,1,1,1,0,0,0,0,0,0 };
//cible pistolet
static int const C_PISTOLET = 7;
int i_C_PISTOLET = 0;
bool tab_C_PISTOLET[13] = { 1,1,1,1,1,1,1,0,0,0,0,0,0 };



//laser
#define PULSE 50;
static int const LASER = 4;
static int const TIME = 4000;
int j = 0;
bool tabID[13] = { 1,1,1,1,1,1,1,0,0,0,1,1,0 };



//lcd
String text = "";
#define BACKLIGHT_PIN 13
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address