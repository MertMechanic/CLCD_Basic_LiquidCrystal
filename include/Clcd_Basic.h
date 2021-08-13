#pragma once


#include <LiquidCrystal_I2C.h>
#include "Arduino.h"
#include "Ticker.h"

class Clcd_Basic
{
    
//BASIC SINGLETON START
public:
    static Clcd_Basic &getInstance()
    {
        static Clcd_Basic S;
        return S;
    }

    Clcd_Basic(const Clcd_Basic &) = delete;
    void operator=(Clcd_Basic const &) = delete;

private:
    Clcd_Basic();
    ~Clcd_Basic();
//BASIC SINGLETON END


private:
    //Init LCD Display
    LiquidCrystal_I2C *m_pLcd;
    
    static const int m_CountOfRows = 2;
    static const int m_CountOfSignsPerRows = 16;


    //Storarge of the current showing strings
    char m_Line[m_CountOfRows][m_CountOfSignsPerRows];

    const String mClearLineStr = "                ";
    Ticker m_LCDBackLightTicker;
public:

    LiquidCrystal_I2C *getLCDInstance();
    
    void init();
    void setLine(String *_pText, int _lineNumber);
    void setLine(const char *_pText, int _lineNumber);
    void setLineUpdate(String *_pText, int _lineNumber);
    void setDisplayTextAndClear(String *_pTextA, String *_pTextB);
    void setDisplayText(char *_pTextA, char *_pTextB);
    void showMessageWithValue(String *_pText, int _value, int _lineNumber);
    void showMessageWithValueAndUnit(String *_pText, int _value,String *_pUnitText, int _lineNumber);

    static void attachTimerToBackLightTurnoff();
    static void turnOffBackLight();
    void turnOnBacklightAndTurnOffLater();


    void showTurnLoadingRoutine(int _delay, const char *_ploadingSign, bool _direction, String *_pText);
    Ticker* getLCDBacklightTicker();
};
