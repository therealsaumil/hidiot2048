/*
 * 2048 game for the HIDIOT
 * by Saumil Shah @therealsaumil
 *
 * 5 October 2017
 * 
 * We want to differentiate between 4 analogue input levels
 * and indicate if S1, S2, S3 or S4 have been pressed, based on
 * the following values:
 * 
 * For the HIDIOT
 * 
 * Range S1: 975 - 955
 * Range S2: 870 - 850
 * Range S3: 780 - 760
 * Range S4: 700 - 680 
 * 
 * For Digispark
 * 
 * Range S1: 860 - 835
 * Range S2: 785 - 755
 * Range S3: 720 - 695
 * Range S4: 645 - 630
 * 
 * If you port this to a new board, you will need to change these
 * values. Use the "calibrate_analogue_input.ino" sketch to do this
 */

// Should be one of HIDIOT or DIGISPARK
// See analogue_switch_ranges.h
#define HIDIOT
//#define DIGISPARK

#ifdef HIDIOT
#define S1_MAX    975
#define S1_MIN    955
#define S2_MAX    870
#define S2_MIN    850
#define S3_MAX    780
#define S3_MIN    760
#define S4_MAX    700
#define S4_MIN    680
#endif

#ifdef DIGISPARK
#define S1_MAX    860
#define S1_MIN    835
#define S2_MAX    785
#define S2_MIN    755
#define S3_MAX    720
#define S3_MIN    695
#define S4_MAX    645
#define S4_MIN    630
#endif

