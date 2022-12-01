#include <Arduino.h>
#include <TM1637TinyDisplay.h>
#include <EEPROM.h>

#define CLK 3
#define DIO 2

TM1637TinyDisplay display(CLK, DIO);

const uint8_t anim[17][4] PROGMEM =
{
    { 0x00, 0x00, 0x00, 0x00 },
    { 0x00, 0x00, 0x00, 0x00 },
    { 0x00, 0x06, 0x30, 0x00 },
    { 0x00, 0x36, 0x36, 0x00 },
    { 0x06, 0x36, 0x36, 0x30 },
    { 0x36, 0x36, 0x36, 0x36 },
    { 0x7f, 0x7f, 0x7f, 0x7f },
    { 0x7f, 0x7f, 0x7f, 0x7f },
    { 0x7f, 0x7f, 0x7f, 0x7f },
    { 0x7f, 0x7f, 0x7f, 0x7f },
    { 0x7f, 0xff, 0x7f, 0x7f },
    { 0x7f, 0xff, 0x7f, 0x7f },
    { 0x7f, 0xff, 0x7f, 0x7f },
    { 0x7f, 0xff, 0x7f, 0x7f },
    { 0x7f, 0xff, 0x7f, 0x7f },
    { 0x00, 0x00, 0x00, 0x00 },
    { 0x00, 0x00, 0x00, 0x00 },
};

const uint8_t anim2[32][4] PROGMEM =
{
    { 0x20, 0x00, 0x00, 0x00 },  // Frame 0
    { 0x21, 0x00, 0x00, 0x00 },  // Frame 1
    { 0x21, 0x01, 0x00, 0x00 },  // Frame 2
    { 0x21, 0x01, 0x01, 0x00 },  // Frame 3
    { 0x21, 0x01, 0x01, 0x01 },  // Frame 4
    { 0x21, 0x01, 0x01, 0x03 },  // Frame 5
    { 0x21, 0x01, 0x01, 0x07 },  // Frame 6
    { 0x21, 0x01, 0x01, 0x0f },  // Frame 7
    { 0x21, 0x01, 0x09, 0x0f },  // Frame 8
    { 0x21, 0x09, 0x09, 0x0f },  // Frame 9
    { 0x29, 0x09, 0x09, 0x0f },  // Frame 10
    { 0x39, 0x09, 0x09, 0x0f },  // Frame 11
    { 0x79, 0x09, 0x09, 0x0f },  // Frame 12
    { 0x79, 0x49, 0x09, 0x0f },  // Frame 13
    { 0x79, 0x49, 0x49, 0x0f },  // Frame 14
    { 0x79, 0x49, 0x49, 0x4f },  // Frame 15
    { 0x79, 0x49, 0x49, 0x6f },  // Frame 16
    { 0x79, 0x49, 0x49, 0x7f },  // Frame 17
    { 0x79, 0x49, 0x4b, 0x7f },  // Frame 18
    { 0x79, 0x49, 0x4f, 0x7f },  // Frame 19
    { 0x79, 0x49, 0x6f, 0x7f },  // Frame 20
    { 0x79, 0x49, 0x7f, 0x7f },  // Frame 21
    { 0x79, 0x4b, 0x7f, 0x7f },  // Frame 22
    { 0x79, 0x4f, 0x7f, 0x7f },  // Frame 23
    { 0x79, 0x6f, 0x7f, 0x7f },  // Frame 24
    { 0x79, 0x7f, 0x7f, 0x7f },  // Frame 25
    { 0x7b, 0x7f, 0x7f, 0x7f },  // Frame 26
    { 0x7f, 0x7f, 0x7f, 0x7f },  // Frame 27
    { 0x7f, 0x7f, 0x7f, 0x7f },  // Frame 28
    { 0x7f, 0x7f, 0x7f, 0x7f },  // Frame 29
    { 0x7f, 0x7f, 0x7f, 0x7f },  // Frame 30
    { 0x00, 0x00, 0x00, 0x00 },  // Frame 31
};

const uint8_t animHour[28][4] PROGMEM =
{
    { 0x00, 0x00, 0x00, 0x00 },  // Frame 0
    { 0x00, 0x08, 0x08, 0x00 },  // Frame 1
    { 0x08, 0x00, 0x00, 0x08 },  // Frame 2
    { 0x10, 0x00, 0x00, 0x04 },  // Frame 3
    { 0x20, 0x00, 0x00, 0x02 },  // Frame 4
    { 0x01, 0x00, 0x00, 0x01 },  // Frame 5
    { 0x00, 0x01, 0x01, 0x00 },  // Frame 6
    { 0x00, 0x02, 0x20, 0x00 },  // Frame 7
    { 0x00, 0x04, 0x10, 0x00 },  // Frame 8
    { 0x00, 0x08, 0x08, 0x00 },  // Frame 9
    { 0x08, 0x08, 0x08, 0x08 },  // Frame 10
    { 0x18, 0x08, 0x08, 0x0c },  // Frame 11
    { 0x38, 0x08, 0x08, 0x0e },  // Frame 12
    { 0x39, 0x08, 0x08, 0x0f },  // Frame 13
    { 0x39, 0x09, 0x09, 0x0f },  // Frame 14
    { 0x39, 0x0b, 0x29, 0x0f },  // Frame 15
    { 0x39, 0x0f, 0x39, 0x0f },  // Frame 16
    { 0x79, 0x4f, 0x79, 0x4f },  // Frame 17
    { 0x7f, 0x7f, 0x7f, 0x7f },  // Frame 18
    { 0x7f, 0x7f, 0x7f, 0x7f },  // Frame 19
    { 0x7f, 0x7f, 0x7f, 0x7f },  // Frame 20
    { 0x7f, 0x7f, 0x7f, 0x7f },  // Frame 21
    { 0x00, 0x00, 0x00, 0x00 },  // Frame 22
    { 0x7f, 0x7f, 0x7f, 0x7f },  // Frame 23
    { 0x7f, 0x7f, 0x7f, 0x7f },  // Frame 24
    { 0x7f, 0x7f, 0x7f, 0x7f },  // Frame 25
    { 0x7f, 0x7f, 0x7f, 0x7f },  // Frame 26
    { 0x00, 0x00, 0x00, 0x00 },  // Frame 27
};

#include <DS3231.h>
#include <Wire.h>

DS3231 rtc;

#define TIME_UPDATE_INTERVAL 100
unsigned long timeToUpdate;

#define SHOW_TIME_INTERVAL 17000
#define SHOW_TEMP_INTERVAL 3000
unsigned long timeToChangeShow;

enum SHOW_MODE
{
    SHOW_TEMP,
    SHOW_HOUR_MIN,
    SHOW_MIN_SEC,
};

uint8_t prevHour = 0xff;

SHOW_MODE showMode = SHOW_HOUR_MIN;

float temperature = 0;

int EEPROM_ADDR_BRIGHTNESS = 0xb;
uint8_t bright = 0;

void startup_animation()
{
    // online tools for 7-seg leds
    // http://www.uize.com/examples/seven-segment-display.html
    // https://jasonacox.github.io/TM1637TinyDisplay/examples/7-segment-animator.html

    display.clear();
    display.setBrightness(7);
    display.showAnimation_P(anim2, FRAMES(anim2), TIME_MS(60));
    display.setBrightness(bright);
    delay(100);
}

void print_temperature()
{
    int t = int(temperature);
    display.showNumber(t, false, 2, 0);
    char s[3] = { 176, 67, 0 };
    display.showString(s, 2, 2);
}

void print_date_time()
{
    DateTime now = RTClib::now();

    if (prevHour != now.hour())
    {
        display.showAnimation_P(animHour, FRAMES(animHour), TIME_MS(80));
    }
    prevHour = now.hour();

    // int d = 100 * now.minute() + now.second();
    int d = 100 * now.hour() + now.minute();
    uint8_t dots = ((now.second() & 1) == 0) ? 0x40 : 0;

    if (rtc.oscillatorCheck())
    {
        display.showNumberDec(d, dots, true);
    }
    else
    {
        uint8_t segs[] = { 0x49, 0x3f, 0x6d, 0x71 };
        display.setSegments(segs, 4, 0);
    }
}

void setupTimeFromSerial()
{
    // Wait $2211301830453$
    //       YYMMDDHHMMSSbrightness 1..7
    Serial.println("CMD waiting...");
    bool cmdReady = false;
    unsigned long timeToBreak = millis() + 10000;
    char str[20];
    int cmdLen = 15;
    int i = 0;
    while (!cmdReady)
    {
        if (millis() > timeToBreak)
        {
            break;
        }
        if (Serial.available())
        {
            byte c = Serial.read();
            str[i] = c;
            i++;
            if (i == cmdLen)
            {
                Serial.println("CMD read Ok");
                cmdReady = true;
            }
        }
    }

    if (cmdReady && (str[0] == '$') && (str[cmdLen - 1] == '$'))
    {
        byte year = ((byte)str[1] - 48) * 10 + (byte)str[2] - 48;
        byte month = ((byte)str[3] - 48) * 10 + (byte)str[4] - 48;
        byte date = ((byte)str[5] - 48) * 10 + (byte)str[6] - 48;
        byte hour = ((byte)str[7] - 48) * 10 + (byte)str[8] - 48;
        byte minute = ((byte)str[9] - 48) * 10 + (byte)str[10] - 48;
        byte second = ((byte)str[11] - 48) * 10 + (byte)str[12] - 48;

        bright = (byte)str[13] - 48;
        if (bright > 7)
        {
            bright = 7;
        }
        EEPROM.update(EEPROM_ADDR_BRIGHTNESS, bright);

        rtc.setClockMode(false);  // set to 24h
        rtc.setYear(year);
        rtc.setMonth(month);
        rtc.setDate(date);
        rtc.setHour(hour);
        rtc.setMinute(minute);
        rtc.setSecond(second);

        Serial.println("RTC set Ok");

        uint8_t segs[] = { 0x3e, 0x6d, 0x79, 0x5e };
        display.setSegments(segs, 4, 0);
        display.setBrightness(bright);
        delay(2000);
    }
    else
    {
        Serial.println("NO CMD");
    }
}

void setup()
{
    Serial.begin(115200);
    Wire.begin();
    display.clear();
    display.setBrightness(0);
    bright = EEPROM.read(EEPROM_ADDR_BRIGHTNESS);
    if (bright > 7)
    {
        bright = 7;  // яркость, 0 - 7 (минимум - максимум)
    }
    startup_animation();
    timeToUpdate = millis() + TIME_UPDATE_INTERVAL;
    timeToChangeShow = millis() + SHOW_TIME_INTERVAL;
    temperature = rtc.getTemperature();
}

SHOW_MODE nextShowMode(SHOW_MODE s)
{
    if (s == SHOW_HOUR_MIN)
    {
        return SHOW_TEMP;
    }
    if (s == SHOW_TEMP)
    {
        return SHOW_HOUR_MIN;
    }
}

void loop()
{
    if (millis() > timeToUpdate)
    {
        if (showMode == SHOW_HOUR_MIN)
        {
            print_date_time();
        }
        if (showMode == SHOW_TEMP)
        {
            print_temperature();
        }
        timeToUpdate = millis() + TIME_UPDATE_INTERVAL;
    }

    if (millis() > timeToChangeShow)
    {
        showMode = nextShowMode(showMode);
        if (showMode == SHOW_HOUR_MIN)
        {
            timeToChangeShow = millis() + SHOW_TIME_INTERVAL;
            temperature = rtc.getTemperature();
        }
        if (showMode == SHOW_TEMP)
        {
            timeToChangeShow = millis() + SHOW_TEMP_INTERVAL;
        }
    }

    delay(10);

    if (Serial.available())
    {
        setupTimeFromSerial();
    }
}
