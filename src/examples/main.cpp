#include <Arduino.h>


#include "Clcd_Basic.h"


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  
  Clcd_Basic::getInstance().init();
  
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Running!");
  delay(500);

  String str1 = "Seems ok";
  String str2 = "Yeah";
  String value1;
  String value2;
  String out1;
  String out2;

  Clcd_Basic::getInstance().setDisplayTextAndClear(&str1, &str2);

  String str1setDisplayTextAndClear = "Nice, Nice";
  String str2setDisplayTextAndClear = "Well Done!";
  String str3setDisplayTextAndClear = "If you see it";
  String str4setDisplayTextAndClear = "you can kill it!";
  str1 = "Value:";
  str2 = "Messung:";

  String unit1 = "mm";
  String unit2 = "°C";

  delay(500);

  Clcd_Basic::getInstance().setDisplayTextAndClear(&str1setDisplayTextAndClear, &str2setDisplayTextAndClear);


  delay(500);

  Clcd_Basic::getInstance().setDisplayTextAndClear(&str3setDisplayTextAndClear, &str4setDisplayTextAndClear);

  for(int i = 0 ; i < 100; i++)
  {
  
    Clcd_Basic::getInstance().showMessageWithValueAndUnit(&str1, i, &unit1, 0);
    Clcd_Basic::getInstance().showMessageWithValueAndUnit(&str2, i, &unit2,  1);
    
  }

Clcd_Basic::getInstance().setDisplayTextAndClear(&str1, &str2);



  for(int i = 0 ; i < 100; i++)
  {
  
    Clcd_Basic::getInstance().showMessageWithValue(&str1, i, 0);
    Clcd_Basic::getInstance().showMessageWithValue(&str2, i, 1);
    
  }

  for(int i = 0 ; i < 100; i++)
  {
    value1 = String(i);
    value2 = String(i++);
  
    out1 = str1 + value1;
    out2 = str2 + value2;
    Clcd_Basic::getInstance().setLineUpdate(&out1, 0);
    Clcd_Basic::getInstance().setLineUpdate(&out2, 1);
  }

  delay(500);

  Clcd_Basic::getInstance().setDisplayTextAndClear(&str3setDisplayTextAndClear, &str4setDisplayTextAndClear);

  for(int i = 100 ; i > 0; i--)
  {
    value1 = String(i);
    value2 = String(i--);

    out1 = str1 + value1;
    out2 = str2 + value2;
    Clcd_Basic::getInstance().setLineUpdate(&out1, 0);
    Clcd_Basic::getInstance().setLineUpdate(&out2, 1);
  }






}