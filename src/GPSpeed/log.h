#ifndef LOG_H
#define LOG_H
//-----------------------------------------------------------------------------------------------------------------------------------------
#if defined(DEBUG_GPS) || defined(DEBUG_GPS_INFO) || defined(DEBUG_REQ) || defined(DEBUG_INO) || defined(DEBUG_SATS) || defined(DEBUG_RECH)
  #define DEBUG
#endif

#ifndef DEBUG
  #define log(s)
#else
  #if defined(GPSPEED_INO)
    void log(String s)        { Serial.println(s); }
  #else
    void log(String);
  #endif
#endif



#endif