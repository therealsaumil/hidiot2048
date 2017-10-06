/*
 * Program to help calibrate values of analogue input
 * when one of four game buttons are pressed.
 * 
 * Used for detecting S1, S2, S3 or S4 for the hidiot2048
 * game.
 * 
 * by Saumil Shah
 * 
 * Use PB5 as Analogue Input. 
 * Read the value and set LED 1's brightness accordingly
 * Also display the value on the OLED
 * 
 * LED 1 can be set to 255 levels of brighness
 * 
 * 0 = 0V
 * 255 = 3.5V
 * 
 * PB0, PB2 used for I2C interface
 * 
 * PS: If the OLED display isn't connected,
 * nothing will work. The red light shall not
 * turn on.
 * 
 * Wiring:
 * 
 * VCC --- 4.7k --+-- 10k --+-- 10k --+-- 10k --+-- 47k --+-- GND
 *                |         |         |         |         |
 *                S1        S2        S3        S4       RESET
 *                |         |         |         |         |
 *    PB5 --------+---------+---------+---------+---------+     
 * 
 * Observed values (HIDIOT)
 * 
 * Range S1: 976 - 955   delta 21
 * Range S2: 871 - 850   delta 21
 * Range S3: 781 - 764   delta 17
 * Range S4: 702 - 682   delta 20
 * 
 * Observed values (Digispark)
 * 
 * Range S1: 863 - 833   delta 30
 * Range S2: 787 - 753   delta 34
 * Range S3: 719 - 692   delta 27
 * Range S4: 648 - 631   delta 17
 * 
 */

#include <CompactDigisparkOLED.h>

const int redLED =  1;
const int PBFIVE = 5;         // pinMode 5, analogRead 0
const int delay_time = 10;    // 10ms
const int debounce = 5;       // 5ms debounce

unsigned int input = 1023;    // analogue input from PB5
unsigned int max = 0;
unsigned int min = 1023;
unsigned int input_present = false;

#define THRESHOLD 980

void setup()
{
   // initialize the display:
   oled.begin();
   // initialize the LED pin as an output:
   pinMode(redLED, OUTPUT);
   // initialize PB5 as input:
   pinMode(PBFIVE, INPUT);

   oled.setCursor(0, 0);
   oled.print(F("HIDIOT "));
   oled.print(F_CPU / 1000000);
   oled.println(F(
      " MHz\n\n"
      "Calibrate buttons\n"
      "Press S1,S2,S3,S4\n"
      "to get the ranges"
   ));
}

void loop()
{
   input = analogRead(0);     // when reading PB5 as analogue, use 0

   // check if there is an input present
   // and toggle the input_present flag
   // accordingly
   if(input < THRESHOLD) {
      delay(debounce);
      input = analogRead(0);  // read the input again after debounce
      if(input < THRESHOLD) {
         input_present = true;
      }
   }
   else {
      if(input_present) {
         // input has gone above threshold
         // which means that there's no
         // connection. reset max and min
         input_present = false;
         max = 0;
         min = 1023;
         analogWrite(redLED, 0);    // turn the LED off
      }
   }

   if(input_present) {
      if(input > max) {
         max = input;
      }
      if(input < min) {
         min = input;
      }
      processInput();
   }

   delay(delay_time);         // poll every 10ms
}

void processInput()
{
   // the values read by analogRead() vary
   // from 0-1023. We have to normalize this
   // to 0-255

   analogWrite(redLED, min >> 2);

   oled.setCursor(0, 6);
   oled.print(F("           "));
   oled.setCursor(0, 6);
   oled.print(max);
   oled.print(F(" - "));
   oled.print(min);
}

