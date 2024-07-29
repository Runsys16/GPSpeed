#ifndef SCREEN_SPLASH_CPP
#define SCREEN_SPLASH_CPP
//---------------------------------------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------------------------------------
#include "screen_splash.h"
#include "Free_Fonts.h"
//---------------------------------------------------------------------------------------------------------------------------------------------------
TFT_eSPI*   pTft;
//---------------------------------------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------------------------------------
ScreenSplash::ScreenSplash(TFT_eSPI* _tft) : Screen::Screen(_tft)
{
}
//====================================================================================
void ScreenSplash::print(void)
{
  int x=50, y=40;
  tft->setFreeFont(FSS18);
  tft->setTextDatum(TL_DATUM);
  tft->setTextColor(TFT_WHITE); /*OLED screen text color*/
  tft->drawString("GPSpeed", x, y);  /*String to represent on OLED tft*/

  x-=2; y-=2;
  tft->setFreeFont(FSS18);
  tft->setTextDatum(TL_DATUM);
  tft->setTextColor(TFT_CYAN); /*OLED screen text color*/
  tft->drawString("GPSpeed", x, y);  /*String to represent on OLED tft*/

  x+=120; y+=35;
  tft->setFreeFont(FSS9);
  tft->setCursor(x, y); /*tft static text*/
  tft->drawString("v2.0", x, y);  /*String to represent on OLED tft*/

  bUpdate = false;
}

#endif