#ifndef SCREEN_SATS_H
#define SCREEN_SATS_H
//---------------------------------------------------------------------------------------------------------------------------------------------------
#include "screens_manager.h"
//---------------------------------------------------------------------------------------------------------------------------------------------------
#define MAX_SATELLITES          100
//---------------------------------------------------------------------------------------------------------------------------------------------------
typedef struct
{
  struct  {
    bool    active    :1;
    bool    displayed :1;
    bool    change    :1;
  } state;

  int     elevation;
  int     azimuth;
  int     snr;
  int     x;
  int     y;
}sat_t; 
//---------------------------------------------------------------------------------------------------------------------------------------------------
class ScreenSats : public Screen
{
  private:
    sat_t                 sats[MAX_SATELLITES]; 

    int                   width;
    int                   height;

    int                   nbs;
    int                   nTotalSats;
    int                   nOldTotalSats;
    bool                  bNbs;
    TFT_eSprite*          pImgNbs;

  public:
              // Constructeur
                          ScreenSats(TFT_eSPI*);
              //
    void                  setSat(int, int, int, int, bool);
    void                  resetSats();
    void                  drawBackground();
    void                  drawSat(int);
    void                  clearSats();
    void                  setNbSat(int);
    void                  updateNbSat();
    int                   getNbSat()                                        { return nbs; }
    sat_t*                getSats()                                         { return sats; }
              // Fonctions virtueles
    virtual   void        print(void);
    virtual   void        update(void);
};
#endif
