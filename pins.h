#define LCD_BLUE	7
#define LCD_RED		15
#define LCD_GREEN	2


#define ENCODER_PIN0    10
#define ENCODER_PIN1    11
#define ENCODER_PIN2    1
#define ENCODER_PIN3    16


#define STOP_START 12
#define RESET_GYRO 13
#define RF1 19
#define RF2 20
#define RF3 18
#define RF4 17
//#define WHEELGAIN 5

// The wiring for the LCD is as follows:
// 1 : GND
// 2 : 5V
// 3 : Contrast (0-5V)*
// 4 : RS (Register Select)
// 5 : R/W (Read Write)       - GROUND THIS PIN! We do not want the LCD to send anything to the Pi @ 5v
// 6 : Enable or Strobe
// 7 : Data Bit 0             - NOT USED
// 8 : Data Bit 1             - NOT USED
// 9 : Data Bit 2             - NOT USED
// 10: Data Bit 3             - NOT USED
// 11: Data Bit 4
// 12: Data Bit 5
// 13: Data Bit 6
// 14: Data Bit 7
// 15: LCD Backlight +5V
// 16: LCD Backlight GND (Red)
// 17: LCD Backlight GND (Green)
// 18: LCD Backlight GND (Blue)


#define LCD_RS  3
#define LCD_E   0
#define LCD_D4  14
#define LCD_D5  6
#define LCD_D6  4
#define LCD_D7  5


