    /*******************************************************************************
     * Project  : Grainv Dryer                                                     *
     * Compiler : Arduino 1.0.2                                                    *
     * Board    : Arduino Mega 2560                                                *
     * Shield   : D.I.Y LED Shield 4x3                                             *
     * Module   : LCD 16x2 Module                                                  *
     *          : RTC DS1307                                                       *
     *          :                                                                  *
     * Author   : Bavensky :3                                                      *
     * E-Mail   : Aphirak_Sang-ngenchai@hotmail.com                                *
     * Date     : 27/07/2014 [dd/mm/yyyy]                                          *
    *******************************************************************************/  
  /************ Connect *****************************
    LCD : Vcc to +5v  
          GND to Ground  
          R/W to Ground  
          10K potentiometer to pin VO
    DS1307 :
          Vcc to +5v
          GND to Ground
          SDA to pin 20
          SCL to pin 21
   *************************************************/
     
  #include <LiquidCrystal.h>
  #include <Wire.h>
  #include "RTClib.h"
 
  #define RS 12
  #define EN 11
  #define D4 5
  #define D5 4
  #define D6 3
  #define D7 2
  
  #define DELAY_TIME 500
  #define DELAY_LCD 2000
  
  
  LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);
  RTC_DS1307 rtc;
  String message[] = {"Welcome", "Grain Dryer"};
  
  int rtc_second=0, rtc_minute=0, rtc_hour=0, rtc_day=0, rtc_month=0, rtc_year=0;
  
  void setup() 
  {
    Serial.begin(57600);
    Wire.begin();
    rtc.begin();
    lcd.begin(16, 2);
    
    while(! rtc.isrunning()) 
    {
      lcd.setCursor(0,0);
      lcd.print("RTC is");
      lcd.setCursor(0,1);
      lcd.print("    NOT running!");
      rtc.adjust(DateTime(__DATE__, __TIME__));
      delay(DELAY_TIME);
    }

    startup();
  }
  
  void loop() 
  {
    realtimeclock();
    lcd.setCursor(0,0);
    lcd.print(message[0]);
    lcd.setCursor(0,1);
    lcd.print("Clock ");
    lcd.print(rtc_hour);
    lcd.print(":");
    lcd.print(rtc_minute);
    lcd.print(":");
    lcd.print(rtc_second);
    lcd.print(" m "); 
 
  }
  
  void startup()
  {
    lcd.clear();
    lcd.home();
    lcd.print(message[0]);
    delay(DELAY_LCD);
    lcd.setCursor(2,1);
    lcd.print(message[1]);
    delay(DELAY_LCD);
  }
  
  void realtimeclock()
  {
    DateTime now = rtc.now();
    rtc_second = now.second();
    rtc_minute = now.minute();
    rtc_hour   = now.hour();
    rtc_day    = now.day();
    rtc_month  = now.month();
    rtc_year   = now.year();
    DateTime future (now.unixtime() + 7 * 86400L + 30);
  }
   

