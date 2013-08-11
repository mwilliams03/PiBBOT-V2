#include "pins.h"

/*#define	ENCODER_PIN0	0
#define	ENCODER_PIN1	2
#define	ENCODER_PIN2	1
#define	ENCODER_PIN3	16*/

volatile long leftEncoderValue;
volatile long rightEncoderValue;
volatile int lastLeftEncoded = 0;
volatile int lastRightEncoded = 0;

void updateLeftEncoders()
{
	int MSB = digitalRead(ENCODER_PIN0);
	int LSB = digitalRead(ENCODER_PIN1);

	int encoded = (MSB << 1) | LSB;
	int sum = (lastLeftEncoded << 2) | encoded;

	if(sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) leftEncoderValue--;
	if(sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) leftEncoderValue++;

	lastLeftEncoded = encoded;
//	printf("lastLeftEncoded %i \t",lastLeftEncoded);
}
void updateRightEncoders()
{
	int MSB = digitalRead(ENCODER_PIN2);
	int LSB = digitalRead(ENCODER_PIN3);

	int encoded = (MSB << 1) | LSB;
	int sum = (lastRightEncoded << 2) | encoded;

	if(sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) rightEncoderValue++;
	if(sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) rightEncoderValue--;

	lastRightEncoded = encoded;
//	printf("lastRightEncoded %i \n", lastRightEncoded);
}

int setupEncoders(void)
{

  if (wiringPiSetup () < 0)
  {
    fprintf (stderr, "Unable to setup wiringPi: %s\n", strerror (errno)) ;
    return 1 ;
  }

  if (wiringPiISR (ENCODER_PIN0, INT_EDGE_BOTH, &updateLeftEncoders) < 0)
  {
    fprintf (stderr, "Unable to setup ISR: %s\n", strerror (errno)) ;
    return 1 ;
  }
  if (wiringPiISR (ENCODER_PIN1, INT_EDGE_BOTH, &updateLeftEncoders) < 0)
  {
    fprintf (stderr, "Unable to setup ISR: %s\n", strerror (errno)) ;
    return 1 ;
  }

  if (wiringPiISR (ENCODER_PIN2, INT_EDGE_BOTH, &updateRightEncoders) < 0)
  {
    fprintf (stderr, "Unable to setup ISR: %s\n", strerror (errno)) ;
    return 1 ;
  }
  if (wiringPiISR (ENCODER_PIN3, INT_EDGE_BOTH, &updateRightEncoders) < 0)
  {
    fprintf (stderr, "Unable to setup ISR: %s\n", strerror (errno)) ;
    return 1 ;
  }
}

