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

  public:
                        ScreenRecherche(TFT_eSPI*);

    virtual   void      print(void);
    virtual   void      update(void);
};
#endif
