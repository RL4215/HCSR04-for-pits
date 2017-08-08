#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>

//#define TRUE 1

#define TRIG 6
#define ECHO 13

void HCSR04_setup() {
	wiringPiSetupGpio();
	pinMode(TRIG, OUTPUT);
	pinMode(ECHO, INPUT);

	//TRIG pin must start LOW
	digitalWrite(TRIG, LOW);
	delay(30);
}

int get_speed(int distance) {
	//Send trig pulse
	digitalWrite(TRIG, HIGH);
	delayMicroseconds(20);
	digitalWrite(TRIG, LOW);

	//Wait for echo start
	while (digitalRead(ECHO) == LOW);

	//Wait for echo end
	long startTime = micros();
	while (digitalRead(ECHO) == HIGH);
	long travelTime = micros() - startTime;

	int speed = (2*distance)/travelTime

	return speed;
}

void *HCSR04Loop(void *some_void_ptr)
{

	struct TGPS *GPS;
	uint16_t UV_data;

	GPS = (struct TGPS *)some_void_ptr;


	HCSR04_SETUP();

	while (1)
	{
		speed_sound = get_speed(0.15);
		GPS->speed_sound = speed_sound;
		printf("Speed of Sound is %f\n", GPS->speed_sound);
		sleep(10);
	}

	return 0;
}