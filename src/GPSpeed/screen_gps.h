#ifndef SCREEN_GPS_H
#define SCREEN_GPS_H
//---------------------------------------------------------------------------------------------------------------------------------------------------
#include "screens_manager.h"
//---------------------------------------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------------------------------------
class ScreenGPS : public Screen
{
  private:
    float                 lon;
    float                 lat;
    float                 speed;
    float                 max;
    int                   nbs;
    String                sNorth;
    String                sEast;
    float                 alt;

    bool                  bLon;
    bool                  bLat;
    bool                  bSpe;
    bool                  bMax;
    bool                  bNbs;
    bool                  bNorth;
    bool                  bEast;
    bool                  bAlt;

    TFT_eSprite*          pImgLon;
    TFT_eSprite*          pImgLat;
    TFT_eSprite*          pImgSpe;
    TFT_eSprite*          pImgMax;
    TFT_eSprite*          pImgNbs;

  public:
              // Constructeur
                          ScreenGPS(TFT_eSPI*);

      void                printHMS(TFT_eSprite*, float, int, int);
      void                printHMS(TFT_eSprite* p, float f)         { printHMS(p, f, TFT_WHITE, TFT_WHITE); }

      void                tab(int);

      void                setLon(float);
      void                setLat(float);
      void                setSpe(float);
      void                setMax(float);
      void                setNbs(int);
      void                setNorth(String);
      void                setEast(String);
      void                setAlt(float);
      float               getLon()                      { return lon; }
      float               getLat()                      { return lat; }
      float               getSpe()                      { return speed; }
      float               getMax()                      { return max; }
      int                 getNbs()                      { return nbs; }
      String              getNorth()                    { return sNorth; }
      String              getEast()                     { return sEast; }
      float               getAlt()                      { return alt; }

              // Fonctions virtueles
    virtual   void        print(void);
    virtual   void        update(void);
};
#endif
