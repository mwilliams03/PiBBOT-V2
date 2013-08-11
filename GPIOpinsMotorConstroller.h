#define WHEEL	10
#include "pins.h"
#include <lcd.h>
#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>




void setAcceleration(void);

void setMotorSpeeds( char speed, int leftWheelVelocity, int rightWheelVelocity,char WHEELGAIN,int turn);

int fd;								// File descrition
char *fileName = "/dev/i2c-1";					// Name of the port we will be using
int  address = 0x58;						// Address of MD22 shifted right one bit
unsigned char buf[10];						// Buffer for data being read and written on the i2c bus
int lcd;


void shutBcmDown()
{
        digitalWrite (STOP_START, LOW);
        digitalWrite (RESET_GYRO, LOW);
        digitalWrite (RF1, LOW);
        digitalWrite (RF2, LOW);
        digitalWrite (RF3, LOW);
        digitalWrite (RF4, LOW);
        digitalWrite (LCD_BLUE, LOW);
        digitalWrite (LCD_GREEN, LOW);
        digitalWrite (LCD_RED, LOW);
}
void setUpMotor()
{
        if ((fd = open(fileName, O_RDWR)) < 0) {					// Open port for reading and writing
                printf("Failed to open i2c port\n");
                exit(1);
        }

        if (ioctl(fd, I2C_SLAVE, address) < 0) {					// Set the port options and set the address of the device we wish to sp$
                printf("Unable to get bus access to talk to slave\n");
                exit(1);
        }
	buf[0] = 0;
	buf[1] = 1;
        if ((write(fd, buf, 2)) != 2) {						// set mode to 1 -128 (Full Reverse)   0 (Stop)   127 (Full Forward).
                printf("Error writing to i2c slave\n");
                exit(1);
        }

}
int  SetPinsOut()
{
	if (wiringPiSetup () == -1)
		exit (1) ;

	pinMode (STOP_START, INPUT) ;
	pinMode (RESET_GYRO, INPUT) ;
	pinMode (RF1, INPUT) ;
	pinMode (RF2, INPUT) ;
	pinMode (RF3, INPUT) ;
	pinMode (RF4, INPUT) ;
        pinMode (LCD_BLUE, OUTPUT);
        pinMode (LCD_GREEN, OUTPUT);
        pinMode (LCD_RED, OUTPUT);


        lcd = lcdInit (4, 20, 4,LCD_RS,LCD_E,LCD_D4,LCD_D5,LCD_D6,LCD_D7,0,0,0,0);
        if ( lcd == -1){
                printf("lcdInit 1 failed\n") ;
                exit(1) ;
        }

}

void setMotorSpeeds(char speed, int leftWheelVelocity, int rightWheelVelocity, char WHEELGAIN,int turn) {

//	printf("LftWV %3i\tRgtWV %3i\t",leftWheelVelocity,rightWheelVelocity);
	char buf[3];
	char diff = 0; //leftWheelVelocity - rightWheelVelocity;
	char RightFixValue = 0;
	char LeftFixValue = 0;

	if (leftWheelVelocity > rightWheelVelocity){
		diff = leftWheelVelocity - rightWheelVelocity;
		RightFixValue = diff * WHEELGAIN;
		printf("3diff %i", diff);
		}
	else if (rightWheelVelocity > leftWheelVelocity){
		diff = rightWheelVelocity - leftWheelVelocity;
		LeftFixValue = diff * WHEELGAIN;
		printf("4diff %i", diff);
	}



        buf[0] = 1;						// Register to set speed of motor 1 , Right motor.

	if((int)speed+(int)RightFixValue > 254) buf[1] = 254;
	else if((int)speed+(int)RightFixValue< 0)  buf[1] = 0;
	else buf[1] = speed+RightFixValue;
        if ((write(fd, buf, 2)) != 2) {
                printf("Error writing to i2c slave\n");
                exit(1);
        }

	buf[0] = 2;                                             // Register to set speed of motor 2 , Left motor.




    	if((int)speed+(int)LeftFixValue> 254) buf[1] = 254;
	else if((int)speed+(int)LeftFixValue< 0  )buf[1] = 0;
	else buf[1] = speed+LeftFixValue;
	    if ((write(fd, buf, 2)) != 2) {
                printf("Error writing to i2c slave\n");
                exit(1);
        }
	printf("left buf   %hhd ", buf[1]);

}


void lcdColor(int color)
{

	if (color == LCD_BLUE){
		digitalWrite(LCD_GREEN,LOW);
		digitalWrite(LCD_BLUE,HIGH);
		digitalWrite(LCD_RED,LOW);
	}

        if (color == LCD_RED){
                digitalWrite(LCD_GREEN,LOW);
                digitalWrite(LCD_BLUE,LOW);
                digitalWrite(LCD_RED,HIGH);
        }

        if (color == LCD_GREEN){
                digitalWrite(LCD_GREEN,HIGH);
                digitalWrite(LCD_BLUE,LOW);
                digitalWrite(LCD_RED,LOW);
        }

}

