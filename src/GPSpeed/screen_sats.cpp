#ifndef SCREEN_SATS_CPP
#define SCREEN_SATS_CPP
//---------------------------------------------------------------------------------------------------------------------------------------------------
//
// Affichage des satellites
//-----------------------
// Ordre d'appels des fonctions:
//        arduino loop() 
//   =>   screens_manager.loop() 
//   =>   si la fenetre est active appel de print() ou update()
//
//  Appelle de la fonction setSat pour mettre a jour les
//  infos satellites :
//    - numero satellites
//    - elevation
//    - azimuth
//    - snr : niveau du signal    0<rouge<10    10<orange<20    20<vert
//
//---------------------------------------------------------------------------------------------------------------------------------------------------
//define DEBUG_SATS
#define DIAM_SAT          3
//---------------------------------------------------------------------------------------------------------------------------------------------------
#include "screen_sats.h"
#include "Free_Fonts.h"
#include "log.h"
//---------------------------------------------------------------------------------------------------------------------------------------------------
#define DX_NBS            60
#define DY_NBS            20
//----------------------------------------------------------------
#define ORANGE_LEVEL      5
#define GREEN_LEVEL       25
//---------------------------------------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------------------------------------
ScreenSats::ScreenSats(TFT_eSPI* _tft) : Screen::Screen(_tft)
{
  nbs = -1;
  pImgNbs = new TFT_eSprite(tft);
  delay(1);
  pImgNbs->createSprite(DX_NBS, DY_NBS);
  nTotalSats = 0;
  nOldTotalSats = 0;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------------------------------------
void ScreenSats::setSat(int no, int ele, int azi, int snr, bool bActive )
{
  if ( 0>no || no>=MAX_SATELLITES)          return;
  if ( no==0 && ele==0 && azi==0 )          return;
  #ifdef DEBUG_SATS
    Serial.println( "ScreenSats::setSat("+String(no)+","+String(ele)+","+String(azi)+","+String(snr)+")" );
  #endif

  sats[no].state.active    = bActive;
  
  if ( snr != sats[no].snr )                          { sats[no].snr       = snr; sats[no].state.change = false; }      // pas besoin d'effacer
  if ( ele != sats[no].elevation )                    { sats[no].elevation = ele; sats[no].state.change = true; }
  if ( azi != sats[no].azimuth )                      { sats[no].azimuth   = azi; sats[no].state.change = true; }
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------------------------------------
void ScreenSats::resetSats()
{
  //update();
  for( int i=0; i<MAX_SATELLITES; i++)      sats[i].state.active = false;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------------------------------------
void ScreenSats::clearSats()
{

  for (int i=0; i<MAX_SATELLITES; i++)  
  {
    if (      ( sats[i].state.displayed && sats[i].state.change )           // changement de position
          ||  ( sats[i].state.displayed && !sats[i].state.active ) )        // disparait
    {
      tft->fillCircle( sats[i].x, sats[i].y, DIAM_SAT, TFT_BLACK );
      sats[i].state.displayed = false;
      //sats[i].bActive = false;                                            // remis à jour par resetSats()
    }
  }
  nTotalSats = 0;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------------------------------------
void ScreenSats::drawSat(int id )
{
  int ele = sats[id].elevation;
  int azi = sats[id].azimuth;
  int snr = sats[id].snr;

  float alpha = float(azi) / 360.0 * 2 * M_PI;
  float r = (90.0-float(ele))/90.0 * height/2;

  float x = r * cos(alpha) + width/2;
  float y = r * sin(alpha) + height/2;

  int color = TFT_RED;
  if ( snr >ORANGE_LEVEL )            color = TFT_ORANGE;
  if ( snr >GREEN_LEVEL )             color = TFT_GREEN;

  sats[id].x = x;
  sats[id].y = y;

  tft->fillCircle( x, y, DIAM_SAT, color );

  nTotalSats++;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------------------------------------
void ScreenSats::drawBackground(void)
{
  int r = height/2;

  tft->drawCircle( width/2, height/2, r-1,   TFT_BLUE );
  tft->drawCircle( width/2, height/2, r/3,   TFT_BLUE );
  tft->drawCircle( width/2, height/2, 2*r/3, TFT_BLUE );
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------------------------------------
void ScreenSats::setNbSat(int n)
{
  log( "ScreenSats::setNbs("+ String(n) +")" );
  if ( n == nbs )       return;

  nbs = n;
  bNbs = true;//bUpdate = true;

}
//---------------------------------------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------------------------------------
void ScreenSats::updateNbSat()
{

  pImgNbs->fillSprite(TFT_BLACK);
  pImgNbs->setFreeFont(FSS9);
  pImgNbs->setTextDatum(TR_DATUM);
  pImgNbs->setTextColor(TFT_GOLD);

  String str = String(nbs) + "/" + String(nTotalSats);

  pImgNbs->drawString(str, DX_NBS, 0);

}
//---------------------------------------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------------------------------------
void ScreenSats::update(void)
{
  //tft->fillScreen(TFT_BLACK);
  clearSats();
  
  #ifdef DEBUG_SATS
    Serial.println(F("-----------------"));
    for (int i=0; i<MAX_SATELLITES; i++)  {
      if (sats[i].state.active)
      {
        Serial.print(i);
        Serial.print(F(") "));

        Serial.print(F("Ele="));
        Serial.print(sats[i].elevation);
        Serial.print(F(" "));

        Serial.print(F(" Azi="));
        Serial.print(sats[i].azimuth);
        Serial.print(F(" "));

        Serial.print(F(" SNR="));
        Serial.print(sats[i].snr);
        Serial.print(F(" "));
        Serial.println();
      }
    }
  #endif

  drawBackground();

  for (int i=0; i<MAX_SATELLITES; i++)  {
    if (sats[i].state.active)
    {
      drawSat(i);
      sats[i].state.displayed = true;
    }
    else
      sats[i].state.displayed = false;

    sats[i].state.change = false;
  }

  if ( bNbs || (nTotalSats!=nOldTotalSats) )
  {
    nOldTotalSats = nTotalSats;
    updateNbSat();
    pImgNbs->pushSprite(240-2-DX_NBS, 10);
  }
  
  //pImgNbs->pushSprite(20, 10);

  bNbs = bUpdate = false;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------------------------------------
void ScreenSats::print(void)
{
  width  = tft->getViewportWidth();
  height = tft->getViewportHeight();

  bNbs = true;
  update();
  bUpdate = false;
}
#endif