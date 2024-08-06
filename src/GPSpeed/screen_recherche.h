#ifndef SCREEN_RECHERCHE_H
#define SCREEN_RECHERCHE_H
//---------------------------------------------------------------------------------------------------------------------------------------------------
#include "screens_manager.h"
//---------------------------------------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------------------------------------
class ScreenRecherche : public Screen
{
  private:
    unsigned long       uTime;
    bool                bAff;
    bool                bEff;
    bool                bFindSat;
    bool                bAffFindSat;
    TFT_eSprite*        pImgNbs;
    int                 nbs;


  public:
                        ScreenRecherche(TFT_eSPI*);

    virtual   void      print(void);
    virtual   void      update(void);
    
    void                setNbSat(int);
    void                setFindSat(bool);
    void                updateNbSat();
    void                updateFindSat();

};
#endif
