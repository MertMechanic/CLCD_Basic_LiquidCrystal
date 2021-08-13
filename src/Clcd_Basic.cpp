#include "Clcd_Basic.h"
#include "Defines.h"

// #define debug 1

Clcd_Basic::Clcd_Basic()
{
}

Clcd_Basic::~Clcd_Basic()
{
}

void Clcd_Basic::init()
{

    m_pLcd = new LiquidCrystal_I2C(0x27, this->m_CountOfSignsPerRows, this->m_CountOfRows);

    // If Multiple I2C Devices - Init it in General!
    // REMOVED START
    // Wire.begin(PIN_SDA, PIN_SCL); //SDA //SCL
    // Wire.begin(_sda_pin, _scl_pin); //SDA //SCL
    // REMOVED END

    m_pLcd->init();
    m_pLcd->backlight();
    this->m_pLcd->setCursor(0, 1);
    m_pLcd->print("Setup is running...");
    this->m_pLcd->setCursor(0, 0);

    for (int line = 0; line < m_CountOfRows; line++)
    {
        for (int row = 0; row < m_CountOfSignsPerRows; row++)
        {
            this->m_pLcd->setCursor(row, line);
            this->m_pLcd->print(".");
            delay(50);
        }
    }

    for (int row = 0; row < m_CountOfRows; row++)
    {
        for (int col = 0; col < m_CountOfSignsPerRows; col++)
        {
            this->m_Line[row][col] = ' ';
        }
    }
}

void Clcd_Basic::setLineUpdate(String *_pText, int _lineNumber)
{

    char staticLengthCharNewTxt[m_CountOfSignsPerRows];
    int lenghtTxt = _pText->length();
    for (int i = 0; i < m_CountOfSignsPerRows; i++)
    {

        if (i < lenghtTxt)
        {
            staticLengthCharNewTxt[i] = _pText->charAt(i);
        }
        else
        {
            staticLengthCharNewTxt[i] = ' ';
        }
    }
    //
    this->turnOnBacklightAndTurnOffLater();
    for (int i = 0; i < m_CountOfSignsPerRows; i++)
    {
        if (this->m_Line[_lineNumber][i] != staticLengthCharNewTxt[i])
        {
            m_pLcd->setCursor(i, _lineNumber); // Cursor0 , Linea0
            m_pLcd->print(staticLengthCharNewTxt[i]);

#ifdef debug
            Serial.print("CLCD::BASIC:: REPLACING : ");
            Serial.print(this->m_Line[_lineNumber][i]);
            Serial.print(" <<---- ");
            Serial.print(staticLengthCharNewTxt[i]);
            Serial.println();
#endif
            this->m_Line[_lineNumber][i] = staticLengthCharNewTxt[i];
        }
    }
}
void Clcd_Basic::setLine(String *_pText, int _lineNumber)
{
    //Copy Text to char Array
#ifdef debug
    Serial.print("Clcd_Basic::setLine:: is called with:");
    Serial.print("_pText: [");
    Serial.print(*_pText);
    Serial.print("], _lineNumber: [");
    Serial.print(_lineNumber);
    Serial.print("]");
    Serial.println();
#endif

    //Fix Length
    int lenghtTxt = _pText->length();
    char staticCharArray[m_CountOfSignsPerRows];
    for (int i = 0; i < m_CountOfSignsPerRows; i++)
    {

        if (i < lenghtTxt)
        {
            staticCharArray[i] = _pText->charAt(i);
        }
        else
        {
            staticCharArray[i] = ' ';
        }
    }
    //

    //Check something changed
    if (memcmp_P(this->m_Line[_lineNumber], staticCharArray, m_CountOfSignsPerRows-1) != 0)
    {
        this->turnOnBacklightAndTurnOffLater();
        m_pLcd->setCursor(0, _lineNumber); // Cursor0 , Linea0
        m_pLcd->print(mClearLineStr);
        m_pLcd->setCursor(0, _lineNumber);

        memcpy_P(this->m_Line[_lineNumber], staticCharArray, m_CountOfSignsPerRows);

#ifdef debug
        Serial.print("Clcd_Basic: printing:");
#endif

        //Print Each Sign to out
        for (int i = 0; i < m_CountOfSignsPerRows; i++)
        {
#ifdef debug
            Serial.print(this->m_Line[_lineNumber][i]);
#endif
            m_pLcd->print(this->m_Line[_lineNumber][i]);
        }

#ifdef debug
        Serial.println();
#endif
    }
}

void Clcd_Basic::setLine(const char *_pText, int _lineNumber)
{
    String str(_pText);
    setLine(&str, _lineNumber);
}

void Clcd_Basic::setDisplayTextAndClear(String *_pTextA, String *_pTextB)
{
    this->setLine(_pTextA, 0);
    this->setLine(_pTextB, 1);
}

void Clcd_Basic::setDisplayText(char *_pTextA, char *_pTextB)
{
    String a(*_pTextA);
    String b(*_pTextB);
    this->setDisplayTextAndClear(&a, &b);
}

LiquidCrystal_I2C *Clcd_Basic::getLCDInstance()
{
    return this->m_pLcd;
}

void Clcd_Basic::showMessageWithValue(String *_pText, int _value, int _lineNumber)
{
    String givenText = *_pText + String(_value);

    Serial.println(givenText);
    this->setLineUpdate(&givenText, _lineNumber);
}

void Clcd_Basic::showMessageWithValueAndUnit(String *_pText, int _value, String *_pUnitText, int _lineNumber)
{
    String givenText = *_pText + String(_value);
    givenText = givenText + *_pUnitText;

#ifdef debug
    Serial.println(givenText);
#endif
    this->setLineUpdate(&givenText, _lineNumber);
}

void Clcd_Basic::turnOnBacklightAndTurnOffLater()
{
    this->m_pLcd->backlight();
    this->attachTimerToBackLightTurnoff();
}

void Clcd_Basic::attachTimerToBackLightTurnoff()
{
    Clcd_Basic::getInstance().getLCDBacklightTicker()->attach_ms(5000, Clcd_Basic::turnOffBackLight);
}

void Clcd_Basic::turnOffBackLight()
{
    Clcd_Basic::getInstance().getLCDInstance()->noBacklight();
    Clcd_Basic::getInstance().getLCDBacklightTicker()->detach();
}

Ticker *Clcd_Basic::getLCDBacklightTicker()
{
    return &this->m_LCDBackLightTicker;
}

void Clcd_Basic::showTurnLoadingRoutine(int _delay, const char *_ploadingSign, bool _direction, String *_pText)
{
    String Sign = String(*_ploadingSign);

    Clcd_Basic::getLCDInstance()->clear();

    String lineA = String(*_pText);
    setLine(&lineA, 0);

    if (_direction)
    {
        for (int i = 0; i < m_CountOfSignsPerRows; i++)
        {
            Clcd_Basic::getLCDInstance()->setCursor(i, 1);
            Clcd_Basic::getLCDInstance()->print(Sign);
            delay(_delay);
        }
    }
    else
    {
        for (int i = m_CountOfSignsPerRows - 1; i >= 0; i--)
        {
            Clcd_Basic::getLCDInstance()->setCursor(i, 1);
            Clcd_Basic::getLCDInstance()->print(Sign);
            delay(_delay);
        }
    }
}
