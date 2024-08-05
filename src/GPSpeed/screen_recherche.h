#ifndef SCREEN_RECHERCHE_H
#define SCREEN_RECHERCHE_H
//---------------------------------------------------------------------------------------------------------------------------------------------------
#include "screens_manager.h"
#include "Free_Fonts.h"
#include "log.h"
//---------------------------------------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------------------------------------
class ScreenRecherche : public Screen
{
  private:
    TFT_eSprite*        pImgNbs;
    int                 nbs;

    unsigned long       uTime;
    bool                bAff;
    bool                bEff;

  public:
                        ScreenRecherche(TFT_eSPI*);

    virtual   void      print(void);
    virtual   void      update(void);

    void                setNbSat(int);
    void                updateNbSat();
};
#endif
