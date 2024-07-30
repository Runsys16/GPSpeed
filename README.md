

# GPSpeed
## Introduction

GPSpeed est un petit montage à l'aide d'un ESP32 LilyGO T-Display et un GPS BN-220.
Il permet de mesurer la vitesse d'un avion RC en vol. La visualisation de la vitesse max se fait via une interface web ou par lecture de l'écran. La connexion sera sur un réseau Wifi, la page a visualiser possède un menu affichant 3 écrans.

### Config Réseau
|SSID|GPSpeed|
|---:|---:|
|**Page**|**http://127.16.9.1**|

### Pages affichées

![VIT](https://raw.githubusercontent.com/Runsys16/GPSpeed/main/images/ecran-vit.png)
![GPS](https://raw.githubusercontent.com/Runsys16/GPSpeed/main/images/ecran-gps.png)
![SAT](https://raw.githubusercontent.com/Runsys16/GPSpeed/main/images/ecran-sat.png)


## Matériel nécessaire

![ESP32](https://raw.githubusercontent.com/Runsys16/GPSpeed/main/images/esp32-bn220.jpg)

![mat0](https://raw.githubusercontent.com/Runsys16/GPSpeed/main/images/ecran-02.png)

![mat1](https://raw.githubusercontent.com/Runsys16/GPSpeed/main/images/ecran-01.png)

![mat2](https://raw.githubusercontent.com/Runsys16/GPSpeed/main/images/ecran-00.png)

[Lien constructeur ESP32](https://www.lilygo.cc/products/lilygo%C2%AE-ttgo-t-display-1-14-inch-lcd-esp32-control-board)

[Lien Beitian BN-220 GPS](https://store.beitian.com/products/beitian-ubx-m8030-g-mouse-supports-gps-qzss-and-sbas-fixed-wing-traversing-aircraft-gps-module-antenna-bn-180-220-280-357-880-880q?_pos=1&_sid=5e89e94dd&_ss=r&variant=46694929989919)

## Bibliotheques
Actuellement la verion de l'IDE arduino est 2.3.2. La configuration du board de l'IDE arduino sera : **ESP32 Dev Module**
### Liste des bibliotheques
  |bibliothèque|version|
  |---:|---:|
  |TFT_eSPI|2.5.43|
  |TinyGPSPlus|1.0.3|

Les bibliothèques Wire.h, HardwareSerial.h, WiFi.h, WiFiClient.h, WiFiAP.h font parties du package ESP32

### Modification
Il faudra modifier les fichiers de configuration de la bibliothèque TFT_eSPI. Dans le fichier GPSpeed.ino line 25+++ se trouve la description de la modification.
```
//-----------------------------------------------------------------------------------------------------------------------------------------
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

```

