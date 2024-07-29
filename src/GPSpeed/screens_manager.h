#ifndef SCREENS_MANAGER_H
#define SCREENS_MANAGER_H
//---------------------------------------------------------------------------------------------------------------------------------------------------
#define NULL 0 
//---------------------------------------------------------------------------------------------------------------------------------------------------
#include <TFT_eSPI.h>
//---------------------------------------------------------------------------------------------------------------------------------------------------
// CLASS Screen
// -------------
//   "Class" parent des ecrans affiché par l'ESP32
//   La "class" definie comme virtuelle les fonctions update() print() et isUpdate()
//   Ces fonctions sont nécessaires pour le mécanisme d'appel des fonctions d'affichage.
//   La fonction print() est appellé lorsque l'écran doit être effacé et tout le contenu doit être affiché.
//   La fonction update() est appelé si un changement doit se faire ... (nouvelle donnée par exemple)
//   En général lorsque l'écran précédant est le même, l'affiche est partiel
//
//---------------------------------------------------------------------------------------------------------------------------------------------------
// Ordre d'appels des fonctions:
//------------------------------0
//        arduino loop() 
//   =>   screens_manager.loop() 
//   =>   appel de print() ou update() de la fenetre active
//---------------------------------------------------------------------------------------------------------------------------------------------------
// Exemple:
//----------
//   Le programme reçois une nouvelle donnée du GPS (ex: nouvele vitesse)
//   la fenetre GPS (class screen_gps) est mis à jour (setSpe()) la donnée est sauvegardé. Puis invalide son écran
//   Deux cas:
//      1- la fenêtre GPS est active alors la fonction update() sera appelé (Affichage des changements seulement)
//      2- la fenêtre GPS n'est pas active alors la fenêtre reste "invalide"
//         lorsque l'utilisateur affichera la fenêtre GPS le screen_manager appelle fonction print()
//         et tout l'ecran sera affiché.
//   
//---------------------------------------------------------------------------------------------------------------------------------------------------
class Screen
{
  protected:
    bool              bUpdate = false;
    TFT_eSPI*         tft;

  public:
                      Screen(TFT_eSPI*);
    virtual   void    update(void)            {};
    virtual   void    print(void)             {};
    virtual   bool    isUpdate(void)          {return bUpdate;};
              void    setUpdate(bool b)       {bUpdate = b;};
};
//---------------------------------------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------------------------------------
#ifndef MAX_SCREENS
  #define MAX_SCREENS           5
#endif
//---------------------------------------------------------------------------------------------------------------------------------------------------
class ScreensManager
{
  private:
    TFT_eSPI*         tft;
    int               uNbScreens;
    int               iActiveScreen;
    int               iPreviousActive;
    unsigned long     uTimeElapsed;
    int               iScreenReturn;
    Screen*           screens[MAX_SCREENS];

  public:
                      ScreensManager(TFT_eSPI*);
    void              setup();
    void              clear();
    void              reDraw();
    int               addScreen( Screen* );
    void              delScreen( Screen* );
    void              setActive( int );
    void              setActiveTime( int, int );
    int               getActive()                       { return iActiveScreen; }
    void              loop(void);
  
};
//---------------------------------------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------------------------------------
#endif
