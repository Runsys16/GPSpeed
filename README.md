# GPSpeed

GPSpeed est un petit montage à l'aide d'un ESP32 lilyGO et un GPS BN-220.
Il permet de mesurer la vitesse d'un avion RC en vole. La visualisation de la vitesse max se fait via le web. La page a visualiser est http://127.16.9.1 

![ESP32](https://github.com/Runsys16/GPSpeed/blob/main/images/esp32-bn220.jpg)


Il faudra modifier les fichiers de configuration de la bibliothèque TFT_eSPI. Dans le fichier GPSpeed.ino line 25+++ se trouve la description de la modification.
```
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
```

Actuellement la verion de l'IDE arduino est 2.3.2.
### Liste des bibliotheques
|bibliothèque|version|
|---:|---:|
|TFT_eSPI|2.5.43|
|TinyGPSPlus|1.0.3|

Les bibliothèques Wire.h, HardwareSerial.h, WiFi.h, WiFiClient.h, WiFiAP.h font parties du package ESP32
