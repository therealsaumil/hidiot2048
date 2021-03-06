# hidiot2048
The 2048 game, built and programmed on the HIDIOT microcomputer.

![HIDIOT 2048](hidiot2048_photo.jpg)

## About the HIDIOT

The Human Interface Device Input/Output Toolkit ([HIDIOT](https://hidiot.com)) is the remarkable credit card sized computer that you can build from scratch, even if you've never soldered before. The HIDIOT was also the speaker and attendee badge at [44CON](https://www.44con.com) for the past two years. I had a lot of fun building my own HIDIOT from scratch, and eventually rekindled my interest in hobby electronics after almost 30 years. 

## About 2048

[2048](http://gabrielecirulli.github.io/2048/) is a single-player sliding block puzzle game by Italian web developer Gabriele Cirulli. The game is incredibly addictive, and became a viral hit within days of its release.

## 2048 on the HIDIOT

My first HIDIOT project was to build a Morse Code keyboard. As a more serious project, I decided to write the 2048 from scratch and make it work on my 44CON HIDIOT badge.

### Components needed

- The HIDIOT https://rawhex.com/collections/hidiot-kits
- 1 x Breadboard
- 5 x Button switches
- 1 x SSD1306 0.96" White 128x64 OLED display ([Aliexpress](https://www.aliexpress.com/item/0-96-inch-IIC-Serial-White-OLED-Display-Module-128X64-I2C-SSD1306-12864-LCD-Screen-Board/32780054633.html), [Amazon](https://www.amazon.co.uk/Kuman-Yellow-Display-Arduino-Raspberry/dp/B01MSPCZWZ/ref=as_li_ss_tl))
- 1 x 4.7k ohm Resistor
- 3 x 10k ohm Resistors
- 1 x 47k ohm Resistor
- a few wires and connector leads

### Circuit Diagram

```
VCC -- 4.7k --+-- 10k --+-- 10k --+-- 10k --+-- 47k --+-- GND
              |         |         |         |         |
               / S1      / S2      / S3      / S4      / RESET
              |         |         |         |         |
    +---------+---------+---------+---------+---------+ 
    |                                                 S1 = Left
    |          +----v----+                            S2 = Up
    +----- PB5 |1  AT   8| VCC                        S3 = Down
        D+ PB3 |2 Tiny  7| PB2 -----------------+     S4 = Right
        D- PB4 |3  85   6| PB1 (LED1)           |
           GND |4       5| PB0 -------------+   |
               +---------+                  |   |
                                   VCC GND SDA SCL
                                    |   |   |   |
                                    |   |   |   |
                                 +-----------------+
                                 | SSD1306 OLED    |
                                 |     128 x 64    |
                                 +-----------------+
```
The four switches are connected to a single pin `PB5` and the input is treated as analogue input. `PB5` is also the `RESET` pin. Some clever work had to be done to keep the voltage level above 2.2V at all times (H/T Steve Lord). Values lower than that would trigger an accidental reset. This is where the resistor bridge divider comes in handy (H/T Udayan Shah).

## Programming Notes

All programming is done using the Arduino IDE. Please read https://docs.hidiot.com on how to [set up the Arduino IDE](https://docs.hidiot.com/cutting_code/setting_up_your_hidiot/) for programming the HIDIOT. I used a modified version of the `DigisparkOLED` library to drive the SS1306 OLED display. The library had to be slimmed down for the entire compiled sketch to fit on in the HIDIOT's memory.

## Game Play

Upon power up, the game wait until the player presses any button. The button press is also used for seeding the HIDIOT's pseudo random number generator. After this, the grid is drawn and the player can slide tiles using the four buttons `S1 (left)`, `S2 (down)`, `S3 (up)` and `S4 (right)`. Pressing the `Reset` button will cause the HIDIOT (and the game) to restart.

Enjoy!

-- Saumil Shah
@therealsaumil
