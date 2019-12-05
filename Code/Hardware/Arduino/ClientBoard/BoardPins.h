/*
   MOTOR PINS

   PREFIX G -> Global
*/


//Number of motors that each panel has
#define MOTORS_PER_PANEL 8


// MOTOR 1
#define DIR_PIN_01     6
#define STEP_PIN_01    5

// MOTOR 2
#define DIR_PIN_02     8
#define STEP_PIN_02    7

// MOTOR 3
#define DIR_PIN_03     10
#define STEP_PIN_03    9

// MOTOR 4
#define DIR_PIN_04     15
#define STEP_PIN_04    14

// MOTOR 5
#define DIR_PIN_05     17
#define STEP_PIN_05    16

// MOTOR 6
#define DIR_PIN_06     21
#define STEP_PIN_06    20

// MOTOR 7
#define DIR_PIN_07     23
#define STEP_PIN_07    22

// MOTOR 8
#define DIR_PIN_08     25
#define STEP_PIN_08    24

//Global Values
#define GMOTOR_STEPS  200 * 16 // 200
#define GRPM          120

//Global pin values
#define GENABLE_PIN    33
#define GM0_PIN        11
#define GM1_PIN        12

//DEBUG LED NEO PIXEL
#define NEO_DEBUG      32

//LED DEBUG TEENSY
#define LED_TEENSY     13

//NEO PIXELS
#define NEO_PIXEL_PIN 7

//DIP SWITCH
#define MUX_S0         26         
#define MUX_S1         27
#define MUX_S2         28
#define MUX_S3         31
#define MUX_SIG       A13

//MUX I2C
#define MUX_SDA       18
#define MUX_SCL       19
