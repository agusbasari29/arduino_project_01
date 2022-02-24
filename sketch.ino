/**
 * @file sketch.ino
 * @author agus basari (agusbasari29@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-02-22
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>
#include <EEPROM.h>
#include <MD_DS3231.h>
#include <Wire.h>

#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 12
#define NUM_ZONES 3
#define CLK_PIN 13
#define DATA_PIN 11
#define CS_PIN 10

#define PRINTS(s) Serial.print(F(s))
#define PRINT(s, v)         \
    {                       \
        Serial.print(F(s)); \
        Serial.print(v);    \
    }

MD_Parola P = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

/** ********************************
 * constants and variables
 ******************************** **/
const char shiftText[3][10] =
    {
        "Shift 1",
        "Shift 2",
        "Shift 3",
};
const int eeadrTarget[] = {0, 20, 40};
const int eeadrShiftTime[] = {60, 61, 62, 63, 64, 65};
int currentShift = 0;
int counter = 0;
int buttonState = 0;
int lastButtonState = 0;
int resetButton = 0;
int lastButtonReset = 0;
int state = 0;
int target1, target2, target3;
byte ha, hb, hc, ma, mb, mc;
char buffer[3][10];

/** ********************************
 * functions
 ******************************** **/
void setup()
{
    Serial.begin(38400);
    while (!Serial)
    {
        ;
    }

    bool eepStatus = getEepromStatus();
    if (!eepStatus)
    {
        setEeprom();
    }
    else
    {
        getEeprom();
    }
    usage();

    P.begin(NUM_ZONES);
    P.setZone(0, 0, 3);
    P.setZone(1, 4, 7);
    P.setZone(2, 8, 11);

    pinMode(2, INPUT_PULLUP);
    pinMode(3, INPUT_PULLUP);

    getCurrentShift();
    displayZone0();
    itoa(target1, buffer[1], 10);
    itoa(counter, buffer[2], 10);
    P.displayZoneText(0, buffer[0], PA_CENTER, 10, 2000, PA_OPENING_CURSOR, PA_OPENING_CURSOR);
    P.displayZoneText(1, buffer[1], PA_RIGHT, 25, 1000, PA_NO_EFFECT, PA_NO_EFFECT);
    P.displayZoneText(2, buffer[2], PA_RIGHT, 25, 1000, PA_NO_EFFECT, PA_NO_EFFECT);
}

void usage(void)
{
    PRINTS("\n");
    PRINTS("\n/********************************************************");
    PRINTS("\n * [XJX TECH | 0856 9439 9449 | agusbasari29@gmail.com] *");
    PRINTS("\n ********************************************************/");
    PRINTS("\n? ======================== help - this message");
    PRINTS("\ntw yyyymmdd hhmmss dw ==== write the current date, time and day of week (1-7)");
    PRINTS("\ntr ======================= read the current time");
    PRINTS("\ni ======================== init all data");
    PRINTS("\ne ======================== get eeprom data");
    PRINTS("\nce nnnnnn ================ edit counter value");
    PRINTS("\ncr ======================= reset counter to 0.");
    PRINTS("\nst aaaaaa bbbbbb cccccc == set target for each shift");
    PRINTS("\nss hhmm hhmm hhmm ======== set shift time");
}

void addCounter(void)
{
    counter++;
    itoa(counter, buffer[2], 10);
    P.setTextBuffer(2, buffer[2]);
    P.displayReset(2);
    PRINT("\nCounter : ", counter);
}

void resetCounter(void)
{
    counter = 0;
    itoa(counter, buffer[2], 10);
    P.setTextBuffer(2, buffer[2]);
    P.displayReset(2);
    PRINTS("\nReset Counter to 0.");
    PRINTS("\n");
}

void editCounter(void)
{
    counter = i2dig(DEC) * 10000 + i2dig(DEC) * 100 + i2dig(DEC);
    itoa(counter, buffer[2], 10);
    P.setTextBuffer(2, buffer[2]);
    P.displayReset(2);
    PRINT("\nEdit Counter to ", counter);
    PRINTS("\n");
}

void setEeprom(void)
{
    target1 = 700;
    EEPROM.put(eeadrTarget[0], target1);
    delay(10);
    target2 = 600;
    EEPROM.put(eeadrTarget[1], target2);
    delay(10);
    target3 = 500;
    EEPROM.put(eeadrTarget[2], target3);
    delay(10);
    ha = 7;
    EEPROM.put(eeadrShiftTime[0], ha);
    delay(10);
    ma = 30;
    EEPROM.put(eeadrShiftTime[1], ma);
    delay(10);
    hb = 15;
    EEPROM.put(eeadrShiftTime[2], hb);
    delay(10);
    mb = 30;
    EEPROM.put(eeadrShiftTime[3], mb);
    delay(10);
    hc = 23;
    EEPROM.put(eeadrShiftTime[4], hc);
    delay(10);
    mc = 30;
    EEPROM.put(eeadrShiftTime[5], mc);
    PRINTS("\nSuccessfully set data to EEPROM");
    getEeprom();
}

void getEeprom(void)
{
    EEPROM.get(eeadrTarget[0], target1);
    EEPROM.get(eeadrTarget[1], target2);
    EEPROM.get(eeadrTarget[2], target3);
    EEPROM.get(eeadrShiftTime[0], ha);
    EEPROM.get(eeadrShiftTime[1], ma);
    EEPROM.get(eeadrShiftTime[2], hb);
    EEPROM.get(eeadrShiftTime[3], mb);
    EEPROM.get(eeadrShiftTime[4], hc);
    EEPROM.get(eeadrShiftTime[5], mc);
    PRINTS("\nSuccessfully get data from EEPROM");
    PRINT("\nTarget Shift 1 : ", target1);
    PRINT("\nTarget Shift 2 : ", target2);
    PRINT("\nTarget Shift 3 : ", target3);
    PRINT("\nTime Shift 1 hour : ", ha);
    PRINT("\nTime Shift 1 minute : ", ma);
    PRINT("\nTime Shift 2 hour : ", hb);
    PRINT("\nTime Shift 2 minute : ", mb);
    PRINT("\nTime Shift 3 hour : ", hc);
    PRINT("\nTime Shift 3 minute : ", mc);
}

bool getEepromStatus(void)
{
    for (int i = 0; i < 6; i++)
    {
        int check;
        EEPROM.get(i * 64, check);
        if (check == 0)
        {
            PRINT("\nEeprom is empty in address 0x", i * 32);
            PRINT(" : ", check);
            return false;
        }
        else
        {
            PRINT("\n Eeprom is exists in address 0x%", i * 32);
            PRINT(":", check);
            return true;
        }
    }
}

void saveTarget(void)
{
    for (int i = 0; i < 3; i++)
    {
        int num = i2dig(DEC) * 10000 + i2dig(DEC) * 100 + i2dig(DEC);
        EEPROM.put(eeadrTarget[i], num);
        PRINT("\nInput new target with value : ", num);
        PRINT(" | on address : ", eeadrTarget[i]);
    }
}

void saveShiftTime(void)
{
    for (int i = 0; i < 6; i++)
    {
        int num = i2dig(DEC);
        EEPROM.put(eeadrShiftTime[i], num);
        PRINT("\nInput new shift time with value : ", num);
        PRINT(" | on address : ", eeadrShiftTime[i]);
    }
}

void getTargetShift(void)
{
    char target[8];

    switch (currentShift)
    {
    case 0:
        itoa(target1, target, 10);
        // PRINTS("\nGet target shift 0");
        break;
    case 1:
        itoa(target2, target, 10);
        // PRINTS("\nGet target shift 1");
        break;
    case 2:
        itoa(target3, target, 10);
        // PRINTS("\nGet target shift 2");
        break;
    default:
        break;
    }
    // PRINT("\nCurrent Target : ", target);
    strcpy(buffer[1], target);
    P.setTextBuffer(1, buffer[1]);
    P.displayReset(1);
}

void getCurrentShift(void)
{
    RTC.readTime();
    if (RTC.h < ha)
    {
        currentShift = 2;
    }
    else if (RTC.h >= ha)
    {
        if (RTC.h == ha && RTC.m < ma)
        {
            currentShift = 2;
        }
        else if (RTC.h == ha && RTC.m == ma)
        {
            if (currentShift != 0)
            {
                resetCounter();
            }
            currentShift = 0;
        }
        else if (RTC.h < hb)
        {
            currentShift = 0;
        }
        else if (RTC.h >= hb)
        {
            if (RTC.h == hb && RTC.m < mb)
            {
                currentShift = 0;
            }
            else if (RTC.h == hb && RTC.m == mb)
            {
                if (currentShift != 1)
                {
                    resetCounter();
                }
                currentShift = 1;
            }
            else if (RTC.h < hc)
            {
                currentShift = 1;
            }
            else if (RTC.h >= hc)
            {
                if (RTC.h == hc && RTC.m < mc)
                {
                    currentShift = 1;
                }
                else if (RTC.h == hc && RTC.m == mc)
                {
                    if (currentShift != 2)
                    {
                        resetCounter();
                    }
                    currentShift = 2;
                }
                else
                {
                    currentShift = 2;
                }
            }
        }
    }
    // PRINT("\nCurrent Shift : ", currentShift);
    // PRINT("\nTime : ", RTC.h);
    // PRINT(":", RTC.m);
    // delay(500);
}

const char *dow2String(uint8_t code)
{
    static const char *str[] = {" ---", " Sun", " Mon", " Tue", " Wed", " Thu", " Fri", " Sat"};

    if (code > 7)
        code = 0;
    return (str[code]);
}

uint8_t htoi(char c)
{
    c = toupper(c);

    if (c >= '0' && c <= '9')
        return (c - '0');
    else if (c >= 'A' && c <= 'F')
        return (c - 'A' + 10);
    else
        return (0);
}

uint8_t i2dig(uint8_t mode)
{
    uint8_t v = 0;
    char c[3] = "00";

    c[0] = readNext();
    c[1] = readNext();

    switch (mode)
    {
    case DEC:
        v = atoi(c);
        break;
    case HEX:
        v = (htoi(c[0]) << 4) + htoi(c[1]);
        ;
        break;
    }

    return (v);
}

char *p2dig(uint8_t v, uint8_t mode)
{
    static char s[3];
    uint8_t i = 0;
    uint8_t n = 0;

    switch (mode)
    {
    case HEX:
        n = 16;
        break;
    case DEC:
        n = 10;
        break;
    }

    if (v < n)
        s[i++] = '0';
    itoa(v, &s[i], n);

    return (s);
}

void displayZone0(void)
{
    if (P.getZoneStatus(0))
    {
        char clock[8];
        RTC.readTime();
        strcpy(&clock[0], p2dig(RTC.h, DEC));
        strcpy(&clock[2], ":");
        strcpy(&clock[3], p2dig(RTC.m, DEC));
        if (state == 0)
        {
            strcpy(buffer[0], shiftText[currentShift]);
            state = 1;
        }
        else
        {
            strcpy(buffer[0], clock);
            state = 0;
        }
        P.setTextBuffer(0, buffer[0]);
        P.displayReset(0);
    }
}

char readNext()
{
    char c;
    do
    {
        while (!Serial.available())
        {
            play();
        }
        c = Serial.read();
    } while (isspace(c));
    return (c);
}

void showTime()
{
    RTC.readTime();
    PRINTS("\nTime - ");
    printTime();
}

void printTime()
{
    PRINT("", RTC.yyyy);
    PRINT("-", p2dig(RTC.mm, DEC));
    PRINT("-", p2dig(RTC.dd, DEC));
    PRINT(" ", p2dig(RTC.h, DEC));
    PRINT(":", p2dig(RTC.m, DEC));
    PRINT(":", p2dig(RTC.s, DEC));
    if (RTC.status(DS3231_12H) == DS3231_ON)
        PRINT("", RTC.pm ? " pm" : " am");
    PRINT("", dow2String(RTC.dow));
}

void inputTime(void)
{
    RTC.yyyy = i2dig(DEC) * 100 + i2dig(DEC);
    RTC.mm = i2dig(DEC);
    RTC.dd = i2dig(DEC);

    RTC.h = i2dig(DEC);
    RTC.m = i2dig(DEC);
    RTC.s = i2dig(DEC);

    RTC.dow = i2dig(DEC);
}

void play(void)
{
    buttonState = digitalRead(2);
    resetButton = digitalRead(3);
    if (buttonState != lastButtonState)
    {
        if (!buttonState == HIGH)
        {
            addCounter();
        }
        delay(50);
    }
    lastButtonState = buttonState;
    if (resetButton != lastButtonReset)
    {
        if (!resetButton == HIGH)
        {
            resetCounter();
        }
        delay(50);
    }
    lastButtonReset = resetButton;
    getCurrentShift();
    getTargetShift();
    if (P.displayAnimate())
    {
        displayZone0();

        for (int i = 0; i < NUM_ZONES; i++)
        {
            if (P.getZoneStatus(i))
            {
                P.setTextBuffer(i, buffer[i]);
                P.displayReset(i);
            }
        }
    }
}

void loop()
{
    char c;
    PRINTS("\n");
    c = readNext();
    switch (toupper(c))
    {
    case '?':
        usage();
        break;
    case 'I':
        setEeprom();
        break;
    case 'E':
        getEeprom();
        break;
    case 'T':
        c = readNext();
        switch (toupper(c))
        {
        case 'R':
            showTime();
            break;
        case 'W':
            inputTime();
            RTC.writeTime();
            showTime();
            break;
        default:
            goto no_good;
        }
        break;
    case 'C':
        c = readNext();
        switch (toupper(c))
        {
        case 'R':
            resetCounter();
            break;
        case 'E':
            editCounter();
            break;
        default:
            goto no_good;
        }
        break;
    case 'S':
        c = readNext();
        switch (toupper(c))
        {
        case 'T':
            saveTarget();
            getEeprom();
            break;
        case 'S':
            saveShiftTime();
            getEeprom();
            break;
        default:
            goto no_good;
        }
        break;
    default:
    no_good:
    {
        PRINT("\nBad parameter '", c);
        PRINTS("'");
        while (Serial.available())
            c = readNext();
    }
    break;
    }
}