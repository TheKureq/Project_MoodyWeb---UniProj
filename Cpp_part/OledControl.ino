/*
 * Title:         "MOODY" ESP8266 (WeMosD1) WiFi Controled Robotic Arm
 * Authors:       Michał Kurek & Samir Abu Safieh
 * Purpose:       University project - educational robot 
 * Desctiption:   Moody is a robotic 5-axis robotic arm toy, controled by website MoodyWeb.com
 * File Version:  1.01v
 * Date:          06.11.2022
*/


/*
  Universal 8bit Graphics Library (https://github.com/olikraus/u8g2/)

  Copyright (c) 2016, olikraus@gmail.com
  All rights reserved.

  Redistribution and use in source and binary forms, with or without modification, 
  are permitted provided that the following conditions are met:

  * Redistributions of source code must retain the above copyright notice, this list 
    of conditions and the following disclaimer.
    
  * Redistributions in binary form must reproduce the above copyright notice, this 
    list of conditions and the following disclaimer in the documentation and/or other 
    materials provided with the distribution.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND 
  CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, 
  INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF 
  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE 
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR 
  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT 
  NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; 
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER 
  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, 
  STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF 
  ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.  

*/

#include <Arduino.h>
#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif



  

void OledControlSetup(void) {
  u8g2.begin();
  u8g2.setFont(u8g2_font_smart_patrol_nbp_tf);	// choose a suitable font
  u8g2.setDrawColor(2);
  u8g2.setFontMode(0);
  u8g2.clearBuffer();					// clear the internal memory
}

void OledControlLoop(void) {
  u8g2.setFont(u8g2_font_smart_patrol_nbp_tf);	// choose a suitable font
  u8g2.drawStr(0,10,"Local IP:");	
  u8g2.setCursor(0,21); // set cursor position  
  u8g2.print(WiFi.localIP());
  u8g2.drawStr(0,32,"Kurek & Samir");	
  u8g2.sendBuffer();					// transfer internal memory to the display
  delay(1000);  
}

