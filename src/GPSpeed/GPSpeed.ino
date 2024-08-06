#ifndef GPSPEED_INO
#define GPSPEED_INO
//-----------------------------------------------------------------------------------------------------------------------------------------
//          GPSpeed
//-----------------------------------------------------------------------------------------------------------------------------------------
//
// Alimentation ESP32    +5V  - GND           (5V d'un recepteur)
//              GPS      +3V3 - GND           (3V3 de l'ESP32)
//
//
//    ---------------------------------------
//   |     ESP32         |       GPS         |
//   |-------------------|-------------------|
//   | pin-26  GPIO26 RX |    (Blanc) TX     |
//   | pin-27  GPIO27 TX |    (Vert)  RX     |
//   | GND               |    (Noir)  GND    |
//   | 3V3               |    (Rouge) VCC    |
//    ---------------------------------------
//
//    ---------------------------------------
//   |     ESP32         |       Recepteur   |   Prise JR futaba
//   |-------------------|-------------------|
//   | GND               |    (Noir)  GND    |
//   | 5V                |    (Rouge) VCC    |
//    ---------------------------------------
//
//
//-----------------------------------------------------------------------------------------------------------------------------------------
//
//  Configuration de de la librairie TFT_eSPI 2.5.43
//-------------------------------------------------------------------------------------------------------------
//    Sur le model LilyGO ttgo T-Display achete sur ...express 
//      https://www.lilygo.cc/products/lilygo%C2%AE-ttgo-t-display-1-14-inch-lcd-esp32-control-board
//    Le chipset graphique est le ST7789
//-------------------------------------------------------------------------------------------------------------
//    
//  Dans le repertoire d'installation de la librairie
//-----------------------------------------------------
//  - Ouvrir le fichier "User_Setup_Select.h" et décommenter 
//     Ligne 58
//       //#include <User_Setups/Setup25_TTGO_T_Display.h>    // Setup file for ESP32 and TTGO T-Display ST7789V SPI bus TFT
//     devient
//       #include <User_Setups/Setup25_TTGO_T_Display.h>    // Setup file for ESP32 and TTGO T-Display ST7789V SPI bus TFT
//
//                       -------------------
//  - Ouvrir le fichier "User_Setup.h" 
//    Ligne 44 il est dit : 1 seule ligne "#define" pour le driver
//    
//    Changer les lignes 44 et 45
//      // Only define one driver, the other ones must be commented out
//      #define ILI9341_DRIVER       // Generic driver for common displays
//    en
//      // Only define one driver, the other ones must be commented out
//      //#define ILI9341_DRIVER       // Generic driver for common displays
//
//                       --- Puis ---
//     Changer la ligne 55
//       //#define ST7789_DRIVER      // Full configuration option, define additional parameters below for this display
//     en
//       #define ST7789_DRIVER      // Full configuration option, define additional parameters below for this display
//
//--  18/07/2024  --
//  - Dans le fichier TFT_eSPI_ESP32.h 
//      Une erreur de compilation est apparue dans les denieres versions de l'IDE
//      Source ( https://github.com/Bodmer/TFT_eSPI/issues/3346 )
//      Ajouter en ligne 15
//        #include "driver/gpio.h"
//
//-----------------------------------------------------------------------------------------------------------------------------------------
//#define DEBUG_INO
//#define SIMU
//#define DEBUG_REQ                   // Info de debogage des requetes client<->serveur
//-------------------------------------
#include <Wire.h>
#include <TFT_eSPI.h> 
#include <HardwareSerial.h>
#include <TinyGPSPlus.h>
//-------------------------------------
#include "screens_manager.h"
#include "screen_gps.h"
#include "screen_gps_info.h"
#include "screen_splash.h"
#include "screen_sats.h"
#include "screen_net_info.h"
#include "screen_recherche.h"
//-------------------------------------
#include "Button2.h"
//-------------------------------------
#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>
//----------- Page HTML
#include "html.h"
//-------------------------------------
#include "log.h"
//---------------------------------------------------------------------------------------------------------------------------------------------------
//                                             DATA du programme
//---------------------------------------------------------------------------------------------------------------------------------------------------
//
//                                       DDDDD     AAA    TTTTT    AAA
//                                       D    D   A   A     T     A   A
//                                       D    D   AAAAA     T     AAAAA
//                                       D    D   A   A     T     A   A
//                                       DDDDD    A   A     T     A   A
//
//---------------------------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------
// Screen TFT   T-tft
//
TFT_eSPI                tft      = TFT_eSPI();
//------- Screen objet ----------------------------------
ScreensManager          sm       = ScreensManager(&tft);
ScreenGPS               sGps     = ScreenGPS(&tft);
ScreenGPSInfo           sGpsInfo = ScreenGPSInfo(&tft);
ScreenSplash            sSplash  = ScreenSplash(&tft);
ScreenSats              sSats    = ScreenSats(&tft);
ScreenNetInfo           sNetInfo = ScreenNetInfo(&tft);
ScreenRecherche         sRecherc = ScreenRecherche(&tft);
//-------------------------------------------------------
int                     iGps;
int                     iGpsInfo;
int                     iSplash;
int                     iSats;
int                     iNetInfo;
int                     iRecherc;
//-------------------------------------------------------
//   Bouton poussoir
//-------------------------------------------------------
#define GPIO0           0
#define GPIO35          35
#define BUTTONL         GPIO0
#define BUTTONR         GPIO35
//------- Button objet ----------------------------------
Button2                 btnL(BUTTONL);
Button2                 btnR(BUTTONR);
//-------------------------------------------------------
// GPS
//-------------------------------------------------------
#define GPSBaud         9600
#define RXPin           26
#define TXPin           27
TinyGPSPlus             gps;
HardwareSerial          gpsSerial = HardwareSerial(1);
TinyGPSCustom           tgpscNorth;
TinyGPSCustom           tgpscEast;
TinyGPSCustom           tgpscAlt;
//-------------------------------------------------------
TinyGPSCustom           startSats(gps, "GNGGA", 1);           // $GPGSV sentence, first element
//TinyGPSCustom           totalGPGSVMessages(gps, "GPGSV", 1);  // $GPGSV sentence, first element
//TinyGPSCustom           messageNumber(gps, "GPGSV", 2);       // $GPGSV sentence, second element
//TinyGPSCustom           satsInView(gps, "GPGSV", 3);          // $GPGSV sentence, third element
#define                 NB_TRAME_GSV      8
TinyGPSCustom           satNumber[NB_TRAME_GSV];              // to be initialized later
TinyGPSCustom           elevation[NB_TRAME_GSV];
TinyGPSCustom           azimuth[NB_TRAME_GSV];
TinyGPSCustom           snr[NB_TRAME_GSV];
//-------------------------------------------------------
unsigned long           uElapsedGPSActif;
#define TIMEGPSACTIF    5000

//-------------------------------------------------------
#ifdef SIMU
  unsigned long           uCurrentTime;
  unsigned long           uElapsedTime;
  unsigned long           uElapsedLon;
  unsigned long           uElapsedLat;
  unsigned long           uElapsedSpe;
  #define TIME500MILLI    500;
  #define MILLILON        1400;
  #define MILLILAT        1900;
  #define MILLISPE        300;
#endif 
//-------------------------------------------------------
//    Wifi
//-------------------------------------------------------
#define WIFI_SSID       "GPSpeed"
#define WIFI_IP         "172.16.9.1"
#define IP              172,16,9,1
//-------------------------------------------------------
WiFiServer              server(80);
IPAddress               local_IP(IP);
IPAddress               gateway(IP);
IPAddress               subnet(255,255,255,0);
bool                    bClient = false;
String                  sJson;
//---------------------------------------------------------------------------------------------------------------------------------------------------
//                                            CORPS DU PROGRAMME
//---------------------------------------------------------------------------------------------------------------------------------------------------
//
//                                           PPPPP   RRRRR    GGGG
//                                           P   P   R    R  G
//                                           PPPPP   RRRRR   G  GG
//                                           P       R  R    G    G
//                                           P       R   R    GGGG
//
//---------------------------------------------------------------------------------------------------------------------------------------------------
//
//  Configuration WIFI
//
//---------------------------------------------------------------------------------------------------------------------------------------------------
void setup_wifi( void )
{
  log("setup_wifi()");
  /* Wifi */
  WiFi.softAPConfig( local_IP, gateway, subnet );
  WiFi.softAP( WIFI_SSID );
  server.begin();
  //delay( DELAY_STEPS );
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
//
//  Reponse de getLiveSats=1
//
//---------------------------------------------------------------------------------------------------------------------------------------------------
bool json_live_sats()
{
  sat_t*  sats = sSats.getSats();
  
  sJson = "{ \"err\":false, \"sats\":[";

  for( int i=0; i<MAX_SATELLITES; i++)
  {
    sJson += "{\"ele\":"+String(sats[i].elevation,DEC);
    sJson += ",\"azi\":"+String(sats[i].azimuth,DEC);
    sJson += ",\"snr\":"+String(sats[i].snr,DEC);
    sJson += "}";
    if ( (i+1) != MAX_SATELLITES )          sJson += ",";
  }

  sJson += "]}";

  return true;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
//
//  Reponse de getLiveGps=1
//
//---------------------------------------------------------------------------------------------------------------------------------------------------
bool json_live_gps()
{
  sJson = String( "{ \"err\":false")+
                  ",\"gpscoord\":\""+String(sGps.getLat(),6)+sGps.getNorth()+", "+String(sGps.getLon(),6)+sGps.getEast()+"\""+
                  ",\"gpslongitude\":\""+String(sGps.getLon(),6)+sGps.getEast()+"\""+
                  ",\"gpslatitude\":\""+String(sGps.getLat(),6)+sGps.getNorth()+"\""+
                  ",\"gpsvitesse\":\""+String(sGps.getSpe(),1)+" km/h"+"\""+
                  ",\"gpsaltitude\":\""+String(sGps.getAlt())+" m"+"\""+
                  ",\"gpsnbsats\":"+String(sGps.getNbs())+
                  ",\"gpsdate\":\""+sGpsInfo.getDateString()+"\""+
                  ",\"gpstime\":\""+sGpsInfo.getTimeString()+"\""+
                  ",\"gpshdop\":"+String(sGpsInfo.getHdop())+
            "}";
  return true;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
//
//  Reponse de getLiveVitesse=1
//
//---------------------------------------------------------------------------------------------------------------------------------------------------
bool json_live_vitesse()
{
  sJson = String( "{ \"err\":false")+
                  ",\"vitesse\":"+String(sGps.getSpe(),1)+
                  ",\"vitessemax\":"+String(sGps.getMax(),1)+
            "}";

  return true;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
//
//  Reponse de resetMax=1
//
//---------------------------------------------------------------------------------------------------------------------------------------------------
bool json_resetMax()
{
  sGps.setMax(0.0);
  sJson = String( "{\"err\":false}" );
  
  return true;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
//
// Decodage de l'entete de message HTML
//
//---------------------------------------------------------------------------------------------------------------------------------------------------
int uri_get( String r, String p, char *b )
{
  int pos, end, end2;

  pos = r.indexOf( "&"+p+"=" );
  if (pos<0) {
    pos = r.indexOf( "?"+p+"=" );
    
    if (pos<0)                      return 0;
  }
  pos   += p.length()+2;
  end   = r.indexOf("&", pos);
  end2  = r.indexOf(" ", pos);
  
  if (end<0 || (end2>0 && end2<end))        end = end2;

  r = (end<0) ? r.substring(pos) : r.substring(pos, end);

  if (b)
    r.toCharArray( b, 128 );

  return r.length();
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
//
// Dialogue HTML via le wifi
//-------------------------------
//
// liste des infos envoyé par le serveur WEB  (voir page HTML et les fonctions javascript)
// les reponses se font au format JSON
//
//        "getLiveVitesse"      // Page de la vitesse max
//        "getLiveGps",         // Page des infos GPS
//        "getLiveSats"         // Page des satellites
//        "resetMax"            // Appui sur le bouton reset vitesse max
//
//---------------------------------------------------------------------------------------------------------------------------------------------------
void processWifiClient( )
{
  WiFiClient client = server.available();

  if (!client || !client.connected() ) { 
    //if ( bScreen )      {sm.setActive(uScreenNet);bScreen = false;}
    if (bClient)       log( "CLIENT FIN");
    bClient = false;
    return; 
  }
  String req = "";
  String currentLine = "";                // make a String to hold incoming data from the client

  while (client.connected()) {            // loop while the client's connected
    if (client.available()) {             // if there's bytes to read from the client,
      char c = client.read();             // read a byte, then
      req += c;

      if (c == '\n') {                    // if the byte is a newline character
        // if the current line is blank, you got two newline characters in a row.
        // that's the end of the client HTTP request, so send a response:
        if (currentLine.length() == 0) {
          bool bJson = false;

          #ifdef DEBUG_REQ
            log( "<-Client  : "+req.substring(0, req.indexOf("\n")) );    // premiere ligne requete
          #endif

          //-----------------------------------------------------
          //           getLiveVitesse
          //-----------------------------------------------------
          if (uri_get(req, "getLiveVitesse", NULL))             bJson = json_live_vitesse();
          //-----------------------------------------------------
          //           getLiveGps
          //-----------------------------------------------------
          else if (uri_get(req, "getLiveGps", NULL))            bJson = json_live_gps();
          //-----------------------------------------------------
          //           getLiveSats
          //-----------------------------------------------------
          else if (uri_get(req, "getLiveSats", NULL))           bJson = json_live_sats();
          //-----------------------------------------------------
          //           resetMax
          //-----------------------------------------------------
          else if (uri_get(req, "resetMax", NULL))              bJson = json_resetMax();
          //-----------------------------------------------------
          // Protocole HTTP
          // Envoi de la page html ou de la réponse JSON
          //
          // ENTETE HTML
          //
          client.println("HTTP/1.1 200 OK");
          client.println("Connection: Keep-Alive");
          client.println("Content-Length: "+ String(((bJson)?sJson.length():strlen(HTML))));
          client.println("Content-type: "+ ((bJson)?String("application/json") :String("text/html")));
          client.println();
          if (bJson) {
            #ifdef DEBUG_REQ
              log( "->Serveur : " + sJson );
            #endif
            client.print( sJson );
          }
          else {
            #ifdef DEBUG_REQ
              log( "   Envoi de la page HTML" );
            #endif
            client.print( HTML );
          }
          break;
        } 
        else      //         if (currentLine.length() == 0) {
        {
          currentLine = "";
        }
      }           //     if (c == '\n') {                    // if the byte is a newline character
      else if (c != '\r') {
        currentLine += c;
      }
    }
  }
  // close the connection:
  client.stop();
}
#ifdef SIMU
//-----------------------------------------------------------------------------------------------------------------------------------------
//
// Simulation des données gps
// uniquement lattitude, longitude et vitesse
//
//-----------------------------------------------------------------------------------------------------------------------------------------
void simu()
{
  uCurrentTime = millis();
  if ( uCurrentTime > uElapsedLon )
  {
    uElapsedLon = uCurrentTime + MILLILON;
    sGps.setLon( (float)random(0, 4500000)/100000.0 );
  }
  if ( uCurrentTime > uElapsedLat )
  {
    uElapsedLat = uCurrentTime + MILLILAT;
    sGps.setLat( (float)random(0, 1000000)/100000.0 );
  }
  if ( uCurrentTime > uElapsedSpe )
  {
    uElapsedSpe = uCurrentTime + MILLISPE;
    sGps.setSpe( (float)random(0, 20000)/100.0 );
  }
}
#endif 
//---------------------------------------------------------------------------------------------------------------------------------------------------
//
// Callback boutons  sur (GPIO0 et GPIO35)
// simple click
//
//---------------------------------------------------------------------------------------------------------------------------------------------------
void cb_click(Button2& pBtn)
{
  //---------------------------------- Affiche les infos de connexion WIFI
  if (pBtn == btnL)
  {
    if ( sm.getActive() != iNetInfo )     sm.setActiveTime(iNetInfo, 10000);        // 10 secondes
    else                                  sm.setActiveTime(iGps, 1);              // retour iNetInfo iRecherc
  }
  //---------------------------------- Rotation des écrans
  if (pBtn == btnR)
  {
    if      ( sm.getActive() == iSats )               sm.setActive(iGpsInfo);
    else if ( sm.getActive() == iGps )                sm.setActive(iSats);
    else if ( sm.getActive() == iGpsInfo )            sm.setActive(iGps);
  
  }
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
//
// Callback boutons  sur (GPIO0 et GPIO35)
// long click
//
//---------------------------------------------------------------------------------------------------------------------------------------------------
void cb_long_click(Button2& pBtn)
{
  //---------------------------------- Remise à zéro de la vitesse max
  sGps.setMax(0);
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
//
// setup GPS
//
//---------------------------------------------------------------------------------------------------------------------------------------------------
void setup_gps()
{
  gpsSerial.begin(GPSBaud, SERIAL_8N1, RXPin, TXPin);
  tgpscNorth.begin(gps, "GNGGA", 3);
  tgpscEast.begin(gps, "GNGGA", 5);
  tgpscAlt.begin(gps, "GNGGA", 9);
  for (int i=0; i<4; i++)
  {
    satNumber[i].begin(gps, "GLGSV", 4 + 4 * i); // offsets 4, 8, 12, 16
    elevation[i].begin(gps, "GLGSV", 5 + 4 * i); // offsets 5, 9, 13, 17
    azimuth[i].begin(  gps, "GLGSV", 6 + 4 * i); // offsets 6, 10, 14, 18
    snr[i].begin(      gps, "GLGSV", 7 + 4 * i); // offsets 7, 11, 15, 19
  }
  for (int i=0, j=4; i<4; i++, j++)
  {
    satNumber[j].begin(gps, "GPGSV", 4 + 4 * i); // offsets 4, 8, 12, 16
    elevation[j].begin(gps, "GPGSV", 5 + 4 * i); // offsets 5, 9, 13, 17
    azimuth[j].begin(  gps, "GPGSV", 6 + 4 * i); // offsets 6, 10, 14, 18
    snr[j].begin(      gps, "GPGSV", 7 + 4 * i); // offsets 7, 11, 15, 19
  }
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
//
// print sat GPS
//
//---------------------------------------------------------------------------------------------------------------------------------------------------
void print_gps(void)
{
  startSats.value();        //update=false
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
//
// read GPS
//
//---------------------------------------------------------------------------------------------------------------------------------------------------
void read_gps(void)
{
  for (int i=0; i<NB_TRAME_GSV; i++)
  {
    if (satNumber[i].isUpdated())
    {
      int no = atoi(satNumber[i].value());
      int e = atoi(elevation[i].value());
      int a = atoi(azimuth[i].value());
      int s = atoi(snr[i].value());
      sSats.setSat(no, e, a, s, true);
    }
  }  
}
//-----------------------------------------------------------------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------------------------------------------------------------
//
//        SETUP() de l'arduino
//
//-----------------------------------------------------------------------------------------------------------------------------------------
void setup() {
  //-----------------------------Init serial pour le DEBUG
  #ifdef DEBUG
    Serial.begin(115200); 
  #endif
  //-----------------------------Init des du BN-220 et du wifi
  #ifdef DEBUG_INO
    Serial.println("Init GPS"); 
  #endif
  setup_gps();

  #ifdef DEBUG_INO
    Serial.println("Init Wifi"); 
  #endif
  setup_wifi();
  //-----------------------------Gestion des ecrans T-Display (tft)
  #ifdef DEBUG_INO
    Serial.println("Init Screen"); 
  #endif
  sm.setup();
  iGps      = sm.addScreen( &sGps );
  iSplash   = sm.addScreen( &sSplash );
  iSats     = sm.addScreen( &sSats );
  iGpsInfo  = sm.addScreen( &sGpsInfo );
  iNetInfo  = sm.addScreen( &sNetInfo );
  iRecherc  = sm.addScreen( &sRecherc );

  sm.setActive(iRecherc);
  sm.setActiveTime(iSplash, 4000);
  //-----------------------------Init des boutons
  pinMode( BUTTONL, INPUT );
  pinMode( BUTTONR, INPUT );
  //-----------------------------Fonctions "callback" des boutons
  btnL.setClickHandler(cb_click);
  btnR.setClickHandler(cb_click);
  btnL.setLongClickHandler(cb_long_click);
  btnR.setLongClickHandler(cb_long_click);
  //-----------------------------
  uElapsedGPSActif = millis();
}
//-----------------------------------------------------------------------------------------------------------------------------------------
//
//        LOOP() de l'arduino
//
//-----------------------------------------------------------------------------------------------------------------------------------------
void loop() {
  #ifdef SIMU
    simu();
  #endif 

  //---------------------------------- Dialogue Wifi
  processWifiClient();
  //---------------------------------- 
  unsigned long  uCurrentTime = millis();
  //---------------------------------- Si dispo met à jour les données GPS
  while (gpsSerial.available() > 0) {
    if (gps.encode(gpsSerial.read())) {

      if ( gps.location.isUpdated() )
      {
        sGps.setLon( gps.location.lng() );
        sGps.setLat( gps.location.lat() );
      }

      if ( gps.speed.isUpdated() )  
      {
        if ( sm.getActive() == iRecherc )     sm.setActive(iGps);
        uElapsedGPSActif = millis();
      }

      if ( gps.date.isUpdated() )               sGpsInfo.setDate( gps.date.value() );
      if ( gps.time.isUpdated() )               { 
        uint32_t t = gps.time.value();
        sGpsInfo.setTime( t );
        if ( t != 0 )     sRecherc.setFindSat(true);
        else              sRecherc.setFindSat(false);
      }
      if ( gps.hdop.isUpdated() )               sGpsInfo.setHdop( gps.hdop.hdop() );
      if ( gps.speed.isUpdated() )              sGps.setSpe( gps.speed.kmph() );
      if ( gps.satellites.isUpdated() )         { int n=gps.satellites.value();sGps.setNbs(n); sSats.setNbSat(n); sRecherc.setNbSat(n); }
      if ( tgpscNorth.isUpdated() )             sGps.setNorth( String(tgpscNorth.value()) );
      if ( tgpscEast.isUpdated() )              sGps.setEast( String(tgpscEast.value()) );
      if ( tgpscAlt.isUpdated() )               sGps.setAlt( atof(tgpscAlt.value()) );

      //------------------------------ Affichage des satellites (uniquement les changements)
      if ( startSats.isUpdated() && sm.getActive()==iSats )             
      {
        sSats.setUpdate(true);      // invalide l'affichge
        sm.loop();                  // Rafraichit l'affichage
        sSats.resetSats();          // Reset la mise a jour des satellites
        startSats.value();          // force updated à false (voir code TinyGPS++.cpp)
      }

      //------------------------------ Lit les trames GSV
      read_gps(); 
    }
  }


  if ( uCurrentTime > (uElapsedGPSActif + TIMEGPSACTIF) )
  {
      if ( sm.getActive() != iRecherc && sm.getActive() != iNetInfo )     sm.setActive(iRecherc);
  }

  //---------------------------------- Mise à jour de l'affichage
  sm.loop();
  //---------------------------------- Gestion des boutons
  btnL.loop();
  btnR.loop();
}
//-----------------------------------------------------------------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------------------------------------------------------------
#endif