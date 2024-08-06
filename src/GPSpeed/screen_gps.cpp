#ifndef SCREEN_GPS_CPP
#define SCREEN_GPS_CPP
//---------------------------------------------------------------------------------------------------------------------------------------------------
//
// Affichage des mesures
//-----------------------
// Ordre d'appels des fonctions:
//        arduino loop() 
//   =>   screens_manager.loop() 
//   =>   si la fenetre est active appel de print() ou update()
//
// Pour mettre a jour les variables (Valeurs mesurées)
// Appel de set/get pour les variables
//
//  Wf :  Poids avant    (Weight Front)
//  Wr :  Poids arrière  (Weight Rear)
//  Wt :  Poids total
//  CG :  Position du centre de gravité
//
//---------------------------------------------------------------------------------------------------------------------------------------------------
//#define DEBUG_GPS
//---------------------------------------------------------------------------------------------------------------------------------------------------
#include "screen_gps.h"
#include "Free_Fonts.h"
#include "log.h"
//---------------------------------------------------------------------------------------------------------------------------------------------------
#define DX_LON        155
#define DY_LON        20
#define DX_LAT        DX_LON
#define DY_LAT        DY_LON
#define DX_SPE        130
#define DY_SPE        DY_LON
#define DX_MAX        130
#define DY_MAX        DY_LON
#define DX_NBS        28
#define DY_NBS        DY_LON
//---------------------------------------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------------------------------------
ScreenGPS::ScreenGPS(TFT_eSPI* _tft) : Screen::Screen(_tft)
{
  lon = 0;
  lat = 0;
  speed = 0;
  max = 0;
  nbs = 0;

  pImgLon = new TFT_eSprite(tft);
  pImgLat = new TFT_eSprite(tft);
  pImgSpe = new TFT_eSprite(tft);
  pImgMax = new TFT_eSprite(tft);
  pImgNbs = new TFT_eSprite(tft);
  
  pImgLon->createSprite(DX_LON, DY_LON);
  pImgLat->createSprite(DX_LAT, DY_LAT);
  pImgSpe->createSprite(DX_SPE, DY_SPE);
  pImgMax->createSprite(DX_MAX, DY_MAX);
  pImgNbs->createSprite(DX_NBS, DY_NBS);
  //45.900002 Y: 0.01667 
  /*
  setLon(45.900002);
  setLat(0.01667);
  setSpe(0.01);
  setMax(max);
  */
  bLon = bLat = bSpe = bMax = bUpdate = bNbs = true;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------------------------------------
void ScreenGPS::setLon(float f)
{
  if ( f == lon )       return;

  lon = f;
  bLon = bUpdate = true;

  printHMS(pImgLon, lon, TFT_YELLOW, TFT_SKYBLUE );
  log( "Longitude : " + String(lon, 8) );

}
//---------------------------------------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------------------------------------
void ScreenGPS::setLat(float f)
{
  if ( f == lat )       return;

  lat = f;
  bLat = bUpdate = true;

  printHMS(pImgLat, lat, TFT_YELLOW, TFT_SKYBLUE );
  log( "Lattitude : " + String(lat, 8) );
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------------------------------------
void ScreenGPS::setSpe(float f)
{
  if ( f == speed )       return;

  speed = f;
  bSpe = bUpdate = true;
  if ( speed > max )    setMax(f);

  pImgSpe->fillSprite(TFT_BLACK);
  pImgSpe->setFreeFont(FSS12);
  pImgSpe->setTextDatum(TL_DATUM);
  pImgSpe->setTextColor(TFT_YELLOW);
  pImgSpe->setCursor(0,16);
  pImgSpe->print(String(speed,2));
  pImgSpe->setTextColor(TFT_SKYBLUE);
  pImgSpe->setFreeFont(FSS12);
  pImgSpe->print(" km/h");


  log( "Speed : " + String(speed) );
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------------------------------------
void ScreenGPS::setMax(float f)
{
  if ( f == max )       return;

  max = f;
  bMax = bUpdate = true;

  pImgMax->fillSprite(TFT_BLACK);
  pImgMax->setFreeFont(FSS12);
  pImgMax->setTextDatum(TL_DATUM);
  pImgMax->setTextColor(TFT_RED);
  pImgMax->setCursor(0,16);
  pImgMax->print(String(max,2));
  pImgMax->setTextColor(TFT_SKYBLUE);
  pImgMax->setFreeFont(FSS12);
  pImgMax->print(" km/h");


  log( "SpeedMax : " + String(max) );
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------------------------------------
void ScreenGPS::setNbs(int n)
{
  if ( n == nbs )       return;

  nbs = n;
  bNbs = bUpdate = true;

  pImgNbs->fillSprite(TFT_BLACK);
  pImgNbs->setFreeFont(FSS12);
  pImgNbs->setTextDatum(TR_DATUM);
  pImgNbs->setTextColor(TFT_GOLD);
  //pImgNbs->setCursor(0,0);
  pImgNbs->drawString(String(nbs), DX_NBS, 0);

  log( "Nb Satellite : " + String(nbs) );
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------------------------------------
void ScreenGPS::setNorth(String s)
{
  if ( s == sNorth )       return;

  sNorth = s;
  bNorth = bUpdate = true;


  log( "North : " + sNorth );
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------------------------------------
void ScreenGPS::setEast(String s)
{
  if ( s == sEast )       return;

  sEast = s;
  bEast = bUpdate = true;


  log( "East : " + sEast );
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------------------------------------
void ScreenGPS::setAlt(float f)
{
  if ( f == alt )       return;

  alt = f;
  bAlt = bUpdate = true;

  log( "Alt : " + String(alt) );
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------------------------------------
void ScreenGPS::printHMS(TFT_eSprite* pSprite, float f, int color, int colorUnit)
{
  pSprite->fillSprite(TFT_BLACK);
  pSprite->setFreeFont(FSS12);
  pSprite->setTextDatum(TL_DATUM);
  pSprite->setTextColor(color);

  int d, m, s, c;
  bool n=false;

  if ( f<0.0 )    { n=true; f=-f; }


  d = f;
  f = f - float(d);
  f *= 60.0;
  m = f;
  f = f - float(m);
  f *= 60.0;
  s = f;
  f = f - float(s);
  f *= 100.0;
  c = f;

  // affichage
  int x, y;
  pSprite->setCursor(0,16);
  if (n)    pSprite->print("-");
  pSprite->print(d);
  
  x = pSprite->getCursorX();
  y = pSprite->getCursorY();
  pSprite->setCursor(x,y-5);

  pSprite->setTextColor(colorUnit);
  pSprite->print("o ");
  
  x = pSprite->getCursorX();
  y = pSprite->getCursorY();
  pSprite->setCursor(x,y+5);
  
  pSprite->setTextColor(color);
  pSprite->print(m);
  pSprite->setTextColor(colorUnit);
  pSprite->print(" ' ");
  pSprite->setTextColor(color);
  pSprite->print(s);
  pSprite->setTextColor(colorUnit);
  pSprite->print(".");
  pSprite->setTextColor(color);
  pSprite->print(c);
  pSprite->setTextColor(colorUnit);
  pSprite->print("\"");
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------------------------------------
void ScreenGPS::tab(int tab)
{
  tft->setCursor(tab, tft->getCursorY());
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------------------------------------
void ScreenGPS::update(void)
{
  int x=40, y=4, dy = 30;
  if ( bLon)      pImgLon->pushSprite(x, y);
  if ( bNbs)      pImgNbs->pushSprite(240-DX_NBS, y);

  y+=dy;
  if ( bLat)      pImgLat->pushSprite(x, y);

  y+=dy;  x=95;
  if ( bSpe)      pImgSpe->pushSprite(x, y);

  y+=dy;  x=45;
  if ( bMax)      pImgMax->pushSprite(x, y);

  bUpdate = bLon = bLat = bSpe = bMax = bNbs = false;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------------------------------------
void ScreenGPS::print(void)
{
  log("ScreenGPS::print()");
  log("   bLon"+String(bLon));

  int x=4, y=20, dy = 30;
  int color = TFT_SKYBLUE;    //TFT_DARKGREY

  tft->setTextDatum(TL_DATUM);
  tft->setTextColor(color);
  tft->setFreeFont(FSS12);
  tft->setCursor(x, y);
  tft->print("Lo: ");
  tft->setTextColor(TFT_WHITE);

  y += dy;
  tft->setCursor(x, y);
  tft->setTextColor(color);
  tft->print("La: ");
  tft->setTextColor(TFT_WHITE);
  tab(80);
  //tft->print(lat, 6);

  y += dy;
  tft->setCursor(x, y);
  tft->setTextColor(color);
  tft->print("Vitesse: ");

  bLon = bLat = bSpe = bMax = bNbs = true;
  update();

  bUpdate = false;
}
#endif
