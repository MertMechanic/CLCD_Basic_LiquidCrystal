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

  str1 = "Nice, Nice";
  str2 = "Well Done!";

  delay(500);

  Clcd_Basic::getInstance().setDisplayTextAndClear(&str1, &str2);

  str1 = "Value:";
  str2 = "Messung:";


  for(int i = 0 ; i < 100; i++)
  {
  
    Clcd_Basic::getInstance().showMessageWithValue(&str1, i, 0);
    Clcd_Basic::getInstance().showMessageWithValue(&str2, i, 1);
    
  }

  for(int i = 0 ; i < 2000000; i++)
  {
    value1 = String(i);
    value2 = String(i++);
  
    out1 = str1 + value1;
    out2 = str2 + value2;
    Clcd_Basic::getInstance().setLineUpdate(&out1, 0);
    Clcd_Basic::getInstance().setLineUpdate(&out2, 1);
  }

  for(int i = 2000000 ; i > 0; i--)
  {
    value1 = String(i);
    value2 = String(i--);

    out1 = str1 + value1;
    out2 = str2 + value2;
    Clcd_Basic::getInstance().setLineUpdate(&out1, 0);
    Clcd_Basic::getInstance().setLineUpdate(&out2, 1);
  }






}