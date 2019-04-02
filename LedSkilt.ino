#include <Adafruit_NeoPixel.h>
Adafruit_NeoPixel rim = Adafruit_NeoPixel(4, 19, NEO_RGB + NEO_KHZ800);
Adafruit_NeoPixel txt = Adafruit_NeoPixel(4, 18, NEO_RGB + NEO_KHZ800);

uint8_t rimIndex = 0;
uint8_t redT = 255;
uint8_t bluT = 0;
uint8_t grnT = 0;

int redR = 0;
int bluR = 0;
int grnR = 250;
int redStig;    //Stigning
int bluStig;
int grnStig;
static int redDir = 1;  //Retning
static int bluDir = 1;
static int grnDir = 1;


int redRL = 5;    //Nedre grense
int bluRL = 0;
int grnRL = 5;
int redRH = 250;  //Øvre grense
int bluRH = 0;
int grnRH = 250;

byte bands = 2;    //Antall bånd

byte rimLeds;
byte txtLeds;

void setup() {  
  rim.begin();
  rim.show();
  rim.setBrightness(32);

  txt.begin();
  txt.show();
  txt.setBrightness(32);

  rimLeds = rim.numPixels();      //Antall leds langs kanten
  txtLeds = txt.numPixels();      //Antall leds i text-delen
  txtLeds = txtLeds / 2;
  rimIndex = 0;

  redStig = abs((redRH - redRL) * bands / rimLeds);
  bluStig = abs((bluRH - bluRL) * bands / rimLeds);
  grnStig = abs((grnRH - grnRL) * bands / rimLeds);
  
  delay(100);
}

void loop() {

  //Sett leds i rim
  redR = PingPong(redR, &redDir, 1, redRL, redRH);
  //bluR = PingPong(bluR, &bluDir, 1, bluRL, bluRH);
  grnR = PingPong(grnR, &grnDir, 1, grnRL, grnRH);

  for(int a = 0; a < rimLeds; a++){
    redR = PingPong(redR, &redDir, redStig, redRL, redRH);
    //bluR = PingPong(bluR, &bluDir, bluStig, bluRL, bluRH);
    grnR = PingPong(grnR, &grnDir, grnStig, grnRL, grnRH);
    rim.setPixelColor(a, grnR, redR, bluR);
  }
  rim.show();
/*
  //Sett leds i text
  redT = redT + 4;
  bluT = bluT + 16;
  grnT = grnT + 1;
  
  for(int b = 0; b < txtLeds; b++){
    txt.setPixelColor(txtLeds-b-1, grnT - b*16, redT - b*4, bluT - b*64);
    txt.setPixelColor(txtLeds+b, grnT - b*16, redT - b*4, bluT - b*64);
  }
  txt.show();
  */
  delay(50);
}

//Lar en verdi sprette mellom to grenser
int PingPong(int naaVerdi, int *dir, int magnitude, int low, int high){
  if(*dir < 0){
    if((naaVerdi - low) >  magnitude){
      return (naaVerdi + (*dir * magnitude));
    } else {
      *dir = -*dir;
      return (low + (*dir * magnitude) - naaVerdi);
    }
  } else if (*dir > 0){
    if(naaVerdi < (high - magnitude)){
      return naaVerdi + (*dir * magnitude);
    } else {
      *dir = -*dir;
      return (2*high + (*dir * magnitude) - naaVerdi);
    }
  }
  return naaVerdi;
}
