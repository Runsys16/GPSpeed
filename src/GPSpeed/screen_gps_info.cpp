#ifndef SCREEN_GPS_INFO_CPP
#define SCREEN_GPS_INFO_CPP
//---------------------------------------------------------------------------------------------------------------------------------------------------
//
// Affichage des mesures
//-----------------------
// Ordre d'appels des fonctions:
//        arduino loop() 
//   =>   screens_+manager.loop() 
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
//#define DEBUG_GPS_INFO
//---------------------------------------------------------------------------------------------------------------------------------------------------
#include "screen_gps_info.h"
#include "Free_Fonts.h"
#include "log.h"
//---------------------------------------------------------------------------------------------------------------------------------------------------
#define DX_DATE        155
#define DY_DATE        20
#define DX_TIME        DX_DATE
#define DY_TIME        DY_DATE
//---------------------------------------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------------------------------------
ScreenGPSInfo::ScreenGPSInfo(TFT_eSPI* _tft) : Screen::Screen(_tft)
{
  date        = 0;
  time        = 0;
  hdop        = 0.0;
  sDate       = "";
  sTime       = "";

  pImgDate = new TFT_eSprite(tft);
  pImgTime = new TFT_eSprite(tft);
  pImgHdop = new TFT_eSprite(tft);
  
  pImgDate->createSprite(DX_DATE, DY_DATE);
  pImgTime->createSprite(DX_TIME, DY_TIME);
  pImgHdop->createSprite(DX_TIME, DY_TIME);

  bHdop = bDate = bTime = true;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------------------------------------
void ScreenGPSInfo::setDate(uint32_t u)
{
  if ( u == date )       return;

  date = u;
  bDate = bUpdate = true;

  pImgDate->fillSprite(TFT_BLACK);
  pImgDate->setFreeFont(FSS12);
  pImgDate->setTextDatum(TL_DATUM);
  pImgDate->setTextColor(TFT_WHITE);

  uint32_t    d = date;
  uint32_t    y = (d % 100) + 2000;       d /= 100;
  uint32_t    m = (d % 100);              d /= 100;
  uint32_t    j = (d % 100);

  char scDate[12];
  snprintf(scDate, sizeof(scDate), "%02d/%02d/%04d", j, m, y);
  pImgDate->drawString(scDate, 0, 0);
  sDate = String(scDate);

  log( "Date : " + String(date) );

}
//---------------------------------------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------------------------------------
void ScreenGPSInfo::setTime(uint32_t u)
{
  #ifdef DEBUG_GPS_INFO
    Serial.println( "ScreenGPSInfo::setTime("+String(u)+")" );
  #endif
  if ( u == time )       return;

  time = u;
  bTime = bUpdate = true;

  pImgTime->fillSprite(TFT_BLACK);
  pImgTime->setFreeFont(FSS12);
  pImgTime->setTextDatum(TL_DATUM);
  pImgTime->setTextColor(TFT_WHITE);

  uint32_t    t = time/100;
  uint32_t    s = (t % 100);        t /= 100;
  uint32_t    m = (t % 100);        t /= 100;
  uint32_t    h = (t % 100);

  char scTime[10];
  snprintf(scTime, sizeof(scTime), "%02d:%02d:%02d", h, m, s);
  pImgTime->drawString(scTime, 0, 0);
  sTime = String(scTime);


  log( "Time : " + String(time) );
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------------------------------------
void ScreenGPSInfo::setHdop(float f)
{
  if ( f == hdop )       return;

  hdop = f;
  bHdop = bUpdate = true;

  pImgHdop->fillSprite(TFT_BLACK);
  pImgHdop->setFreeFont(FSS12);
  pImgHdop->setTextDatum(TL_DATUM);
  pImgHdop->setTextColor(TFT_WHITE);

  char sHdop[10];
  snprintf(sHdop, sizeof(sHdop), "%0.2f", hdop);
  pImgHdop->drawString(sHdop, 0, 0);


  log( "HDOP : " + String(hdop) );
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------------------------------------
void ScreenGPSInfo::update(void)
{
  int x=80, y=4, dy = 30;

  if ( bDate)      pImgDate->pushSprite(x, y);
  y+=dy;
  if ( bTime)      pImgTime->pushSprite(x, y);
  y+=dy;
  if ( bHdop)      pImgHdop->pushSprite(x, y);

  bUpdate = bDate = bTime = bHdop = false;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------------------------------------
void ScreenGPSInfo::print(void)
{
  log("ScreenGPSInfo::print()");
  log("   bDate"+String(bDate));

  int x=4, y=20, dy = 30;
  int color = TFT_SKYBLUE;    //TFT_DARKGREY

  tft->setTextDatum(TL_DATUM);
  tft->setTextColor(color);
  tft->setFreeFont(FSS12);
  tft->setCursor(x, y);
  tft->print("Date: ");
  tft->setTextColor(TFT_WHITE);

  y += dy;
  tft->setCursor(x, y);
  tft->setTextColor(color);
  tft->print("Time: ");
  tft->setTextColor(TFT_WHITE);

  y += dy;
  tft->setCursor(x, y);
  tft->setTextColor(color);
  tft->print("hdop: ");
  tft->setTextColor(TFT_WHITE);
  
  bDate = bTime = bHdop = true;
  update();

  bUpdate = false;
}
#endif