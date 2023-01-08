# Mini clock with Arduino

## Parts

* Arduino Nano
* Display TM1637
* RTC DS3231

## Connection

| Nano Pin | Device | Name |
|----------|--------|------|
| D2       | TM1637 | DIO  |
| D3       | TM1637 | CLK  |
| 5V       | TM1637 | VCC  |
| GND      | TM1637 | GND  |
| A4       | DS3231 | DATA |
| A5       | DS3231 | CLK  |
| 3.3V     | DS3231 | VCC  |
| GND      | DS3231 | GND  |

## Libs

* [TM1637TinyDisplay](https://github.com/jasonacox/TM1637TinyDisplay)
* [DS3231](https://github.com/NorthernWidget/DS3231)
