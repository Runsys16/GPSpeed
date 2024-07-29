#ifndef SCREEN_GPS_INFO_H
#define SCREEN_GPS_INFO_H
//---------------------------------------------------------------------------------------------------------------------------------------------------
#include "screens_manager.h"
//---------------------------------------------------------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------------------------------------------------------
class ScreenGPSInfo : public Screen
{
  private:
    uint32_t              date;
    String                sDate;
    uint32_t              time;
    String                sTime;
    float                 hdop;

    bool                  bDate;
    bool                  bTime;
    bool                  bHdop;

    TFT_eSprite*          pImgDate;
    TFT_eSprite*          pImgTime;
    TFT_eSprite*          pImgHdop;

  public:
              // Constructeur
                          ScreenGPSInfo(TFT_eSPI*);

      void                setDate(uint32_t);
      uint32_t            getDate()                      { return date; }
      String              getDateString()                { return sDate; }
      void                setTime(uint32_t);
      uint32_t            getTime()                      { return time; }
      String              getTimeString()                { return sTime; }
      void                setHdop(float);
      float               getHdop()                      { return hdop; }

              // Fonctions virtueles
    virtual   void        print(void);
    virtual   void        update(void);
};
#endif
