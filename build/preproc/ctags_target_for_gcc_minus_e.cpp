# 1 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino"
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
# 12 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino"
# 13 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino" 2

# 15 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino" 2
# 16 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino" 2
# 17 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino" 2
# 18 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino" 2
# 33 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino"
MD_Parola P = MD_Parola(MD_MAX72XX::FC16_HW, 10, 12);

/** ********************************

 * constants and variables

 ******************************** **/
# 38 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino"
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
# 60 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino"
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

    P.begin(3);
    P.setZone(0, 0, 3);
    P.setZone(1, 4, 7);
    P.setZone(2, 8, 11);

    pinMode(2, 0x2);
    pinMode(3, 0x2);

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
    Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 98 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino" 3
   (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 98 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino"
   "\n"
# 98 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino" 3
   ); &__c[0];}))
# 98 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino"
   )));
    Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 99 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino" 3
   (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 99 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino"
   "\n/********************************************************"
# 99 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino" 3
   ); &__c[0];}))
# 99 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino"
   )));
    Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 100 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino" 3
   (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 100 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino"
   "\n * [XJX TECH | 0856 9439 9449 | agusbasari29@gmail.com] *"
# 100 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino" 3
   ); &__c[0];}))
# 100 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino"
   )));
    Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 101 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino" 3
   (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 101 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino"
   "\n ********************************************************/"
# 101 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino" 3
   ); &__c[0];}))
# 101 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino"
   )));
    Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 102 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino" 3
   (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 102 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino"
   "\n? ======================== help - this message"
# 102 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino" 3
   ); &__c[0];}))
# 102 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino"
   )));
    Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 103 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino" 3
   (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 103 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino"
   "\ntw yyyymmdd hhmmss dw ==== write the current date, time and day of week (1-7)"
# 103 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino" 3
   ); &__c[0];}))
# 103 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino"
   )));
    Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 104 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino" 3
   (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 104 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino"
   "\ntr ======================= read the current time"
# 104 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino" 3
   ); &__c[0];}))
# 104 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino"
   )));
    Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 105 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino" 3
   (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 105 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino"
   "\ni ======================== init all data"
# 105 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino" 3
   ); &__c[0];}))
# 105 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino"
   )));
    Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 106 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino" 3
   (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 106 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino"
   "\ne ======================== get eeprom data"
# 106 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino" 3
   ); &__c[0];}))
# 106 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino"
   )));
    Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 107 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino" 3
   (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 107 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino"
   "\nce nnnnnn ================ edit counter value"
# 107 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino" 3
   ); &__c[0];}))
# 107 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino"
   )));
    Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 108 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino" 3
   (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 108 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino"
   "\ncr ======================= reset counter to 0."
# 108 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino" 3
   ); &__c[0];}))
# 108 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino"
   )));
    Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 109 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino" 3
   (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 109 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino"
   "\nst aaaaaa bbbbbb cccccc == set target for each shift"
# 109 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino" 3
   ); &__c[0];}))
# 109 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino"
   )));
    Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 110 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino" 3
   (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 110 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino"
   "\nss hhmm hhmm hhmm ======== set shift time"
# 110 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino" 3
   ); &__c[0];}))
# 110 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino"
   )));
}

void addCounter(void)
{
    counter++;
    itoa(counter, buffer[2], 10);
    P.setTextBuffer(2, buffer[2]);
    P.displayReset(2);
    { Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 119 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino" 3
   (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 119 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino"
   "\nCounter : "
# 119 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino" 3
   ); &__c[0];}))
# 119 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino"
   ))); Serial.print(counter); };
}

void resetCounter(void)
{
    counter = 0;
    itoa(counter, buffer[2], 10);
    P.setTextBuffer(2, buffer[2]);
    P.displayReset(2);
    Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 128 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino" 3
   (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 128 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino"
   "\nReset Counter to 0."
# 128 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino" 3
   ); &__c[0];}))
# 128 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino"
   )));
    Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 129 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino" 3
   (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 129 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino"
   "\n"
# 129 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino" 3
   ); &__c[0];}))
# 129 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino"
   )));
}

void editCounter(void)
{
    counter = i2dig(10) * 10000 + i2dig(10) * 100 + i2dig(10);
    itoa(counter, buffer[2], 10);
    P.setTextBuffer(2, buffer[2]);
    P.displayReset(2);
    { Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 138 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino" 3
   (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 138 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino"
   "\nEdit Counter to "
# 138 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino" 3
   ); &__c[0];}))
# 138 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino"
   ))); Serial.print(counter); };
    Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 139 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino" 3
   (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 139 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino"
   "\n"
# 139 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino" 3
   ); &__c[0];}))
# 139 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino"
   )));
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
    Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 170 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino" 3
   (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 170 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino"
   "\nSuccessfully set data to EEPROM"
# 170 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino" 3
   ); &__c[0];}))
# 170 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino"
   )));
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
    Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 185 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino" 3
   (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 185 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino"
   "\nSuccessfully get data from EEPROM"
# 185 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino" 3
   ); &__c[0];}))
# 185 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino"
   )));
    { Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 186 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino" 3
   (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 186 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino"
   "\nTarget Shift 1 : "
# 186 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino" 3
   ); &__c[0];}))
# 186 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino"
   ))); Serial.print(target1); };
    { Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 187 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino" 3
   (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 187 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino"
   "\nTarget Shift 2 : "
# 187 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino" 3
   ); &__c[0];}))
# 187 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino"
   ))); Serial.print(target2); };
    { Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 188 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino" 3
   (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 188 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino"
   "\nTarget Shift 3 : "
# 188 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino" 3
   ); &__c[0];}))
# 188 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino"
   ))); Serial.print(target3); };
    { Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 189 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino" 3
   (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 189 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino"
   "\nTime Shift 1 hour : "
# 189 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino" 3
   ); &__c[0];}))
# 189 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino"
   ))); Serial.print(ha); };
    { Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 190 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino" 3
   (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 190 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino"
   "\nTime Shift 1 minute : "
# 190 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino" 3
   ); &__c[0];}))
# 190 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino"
   ))); Serial.print(ma); };
    { Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 191 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino" 3
   (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 191 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino"
   "\nTime Shift 2 hour : "
# 191 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino" 3
   ); &__c[0];}))
# 191 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino"
   ))); Serial.print(hb); };
    { Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 192 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino" 3
   (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 192 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino"
   "\nTime Shift 2 minute : "
# 192 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino" 3
   ); &__c[0];}))
# 192 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino"
   ))); Serial.print(mb); };
    { Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 193 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino" 3
   (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 193 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino"
   "\nTime Shift 3 hour : "
# 193 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino" 3
   ); &__c[0];}))
# 193 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino"
   ))); Serial.print(hc); };
    { Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 194 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino" 3
   (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 194 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino"
   "\nTime Shift 3 minute : "
# 194 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino" 3
   ); &__c[0];}))
# 194 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino"
   ))); Serial.print(mc); };
}

bool getEepromStatus(void)
{
    for (int i = 0; i < 6; i++)
    {
        int check;
        EEPROM.get(i * 64, check);
        if (check == 0)
        {
            { Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 205 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino" 3
           (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 205 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino"
           "\nEeprom is empty in address 0x"
# 205 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino" 3
           ); &__c[0];}))
# 205 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino"
           ))); Serial.print(i * 32); };
            { Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 206 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino" 3
           (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 206 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino"
           " : "
# 206 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino" 3
           ); &__c[0];}))
# 206 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino"
           ))); Serial.print(check); };
            return false;
        }
        else
        {
            { Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 211 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino" 3
           (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 211 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino"
           "\n Eeprom is exists in address 0x%"
# 211 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino" 3
           ); &__c[0];}))
# 211 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino"
           ))); Serial.print(i * 32); };
            { Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 212 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino" 3
           (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 212 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino"
           ":"
# 212 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino" 3
           ); &__c[0];}))
# 212 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino"
           ))); Serial.print(check); };
            return true;
        }
    }
}

void saveTarget(void)
{
    for (int i = 0; i < 3; i++)
    {
        int num = i2dig(10) * 10000 + i2dig(10) * 100 + i2dig(10);
        EEPROM.put(eeadrTarget[i], num);
        { Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 224 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino" 3
       (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 224 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino"
       "\nInput new target with value : "
# 224 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino" 3
       ); &__c[0];}))
# 224 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino"
       ))); Serial.print(num); };
        { Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 225 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino" 3
       (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 225 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino"
       " | on address : "
# 225 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino" 3
       ); &__c[0];}))
# 225 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino"
       ))); Serial.print(eeadrTarget[i]); };
    }
}

void saveShiftTime(void)
{
    for (int i = 0; i < 6; i++)
    {
        int num = i2dig(10);
        EEPROM.put(eeadrShiftTime[i], num);
        { Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 235 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino" 3
       (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 235 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino"
       "\nInput new shift time with value : "
# 235 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino" 3
       ); &__c[0];}))
# 235 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino"
       ))); Serial.print(num); };
        { Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 236 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino" 3
       (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 236 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino"
       " | on address : "
# 236 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino" 3
       ); &__c[0];}))
# 236 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino"
       ))); Serial.print(eeadrShiftTime[i]); };
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
    if (RTC.h < ha){
        currentShift = 2;
    }else if (RTC.h >= ha)
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
    case 10:
        v = atoi(c);
        break;
    case 16:
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
    case 16:
        n = 16;
        break;
    case 10:
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
        strcpy(&clock[0], p2dig(RTC.h, 10));
        strcpy(&clock[2], ":");
        strcpy(&clock[3], p2dig(RTC.m, 10));
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
    Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 442 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino" 3
   (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 442 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino"
   "\nTime - "
# 442 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino" 3
   ); &__c[0];}))
# 442 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino"
   )));
    printTime();
}

void printTime()
{
    { Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 448 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino" 3
   (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 448 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino"
   ""
# 448 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino" 3
   ); &__c[0];}))
# 448 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino"
   ))); Serial.print(RTC.yyyy); };
    { Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 449 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino" 3
   (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 449 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino"
   "-"
# 449 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino" 3
   ); &__c[0];}))
# 449 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino"
   ))); Serial.print(p2dig(RTC.mm, 10)); };
    { Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 450 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino" 3
   (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 450 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino"
   "-"
# 450 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino" 3
   ); &__c[0];}))
# 450 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino"
   ))); Serial.print(p2dig(RTC.dd, 10)); };
    { Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 451 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino" 3
   (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 451 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino"
   " "
# 451 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino" 3
   ); &__c[0];}))
# 451 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino"
   ))); Serial.print(p2dig(RTC.h, 10)); };
    { Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 452 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino" 3
   (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 452 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino"
   ":"
# 452 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino" 3
   ); &__c[0];}))
# 452 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino"
   ))); Serial.print(p2dig(RTC.m, 10)); };
    { Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 453 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino" 3
   (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 453 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino"
   ":"
# 453 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino" 3
   ); &__c[0];}))
# 453 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino"
   ))); Serial.print(p2dig(RTC.s, 10)); };
    if (RTC.status(DS3231_12H) == DS3231_ON)
        { Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 455 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino" 3
       (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 455 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino"
       ""
# 455 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino" 3
       ); &__c[0];}))
# 455 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino"
       ))); Serial.print(RTC.pm ? " pm" : " am"); };
    { Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 456 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino" 3
   (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 456 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino"
   ""
# 456 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino" 3
   ); &__c[0];}))
# 456 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino"
   ))); Serial.print(dow2String(RTC.dow)); };
}

void inputTime(void)
{
    RTC.yyyy = i2dig(10) * 100 + i2dig(10);
    RTC.mm = i2dig(10);
    RTC.dd = i2dig(10);

    RTC.h = i2dig(10);
    RTC.m = i2dig(10);
    RTC.s = i2dig(10);

    RTC.dow = i2dig(10);
}

void play(void)
{
    buttonState = digitalRead(2);
    resetButton = digitalRead(3);
    if (buttonState != lastButtonState)
    {
        if (!buttonState == 0x1)
        {
            addCounter();
        }
        delay(50);
    }
    lastButtonState = buttonState;
    if (resetButton != lastButtonReset)
    {
        if (!resetButton == 0x1)
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

        for (int i = 0; i < 3; i++)
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
    Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 514 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino" 3
   (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 514 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino"
   "\n"
# 514 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino" 3
   ); &__c[0];}))
# 514 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino"
   )));
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
        { Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 576 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino" 3
       (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 576 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino"
       "\nBad parameter '"
# 576 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino" 3
       ); &__c[0];}))
# 576 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino"
       ))); Serial.print(c); };
        Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 577 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino" 3
       (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 577 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino"
       "'"
# 577 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino" 3
       ); &__c[0];}))
# 577 "/home/jabrix/projects/Arduino/Daihatsu/final/arduino_project_01/sketch.ino"
       )));
        while (Serial.available())
            c = readNext();
    }
    break;
    }
}
