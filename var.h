#pragma once
#define SERIALBAUDS 9600

#define ESP_RX 8
#define ESP_TX 9
#define ESP_START 12

//Led
#define PINCOLOR 3
#define NUMPIXELS 16
#define BRIGHTNESS 55

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
#define PULSE 50
#define LASER 4
int TIME = 500;
bool tabID[13] = { 1,1,1,1,1,1,1,0,0,0,1,1,0 };

//lcd
#define BACKLIGHT_PIN 13
#define LCDADDR 0x27

#define CMD_START "_"
#define CMD_TEAM "T"
#define CMD_PARTY "P"
#define CMD_GAME "G"
String dialog = "";