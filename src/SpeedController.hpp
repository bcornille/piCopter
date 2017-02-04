/***********************************************************************
 * This is a library for controlling motors with various PWM or other
 * types for of speed control protocols.
 *
 * All protocols are  built on a virtual class SpeedController.
 *
 * Supported protocols:
 *  - OneShot125
 **********************************************************************/

#ifndef __Speed_Controller_h__
#define __Speed_Controller_h__

typedef enum
{
//	GPIO0 = 0; These pins are generally reserved for i2c communication
//	GPIO1 = 1; with an EEPROM.
	GPIO2 = 2;
	GPIO3 = 3;
	GPIO4 = 4;
	GPIO5 = 5;
	GPIO6 = 6;
	GPIO7 = 7;
	GPIO8 = 8;
	GPIO9 = 9;
	GPIO10 = 10;
	GPIO11 = 11;
	GPIO12 = 12;
	GPIO13 = 13;
//	GPIO14 = 14; Used for the TXD of the BNO055 sensor.
//	GPIO15 = 15; Used for the RXD of the BNO055 sensor.
	GPIO16 = 16;
	GPIO17 = 17;
//	GPIO18 = 18; Used for the RST of the BNO055 sensor.
	GPIO19 = 19;
	GPIO20 = 20;
	GPIO21 = 21;
	GPIO22 = 22;
	GPIO23 = 23;
	GPIO24 = 24;
	GPIO25 = 25;
	GPIO26 = 26;
	GPIO27 = 27;
//	GPIO28 = 28;
//	GPIO29 = 29;
//	GPIO30 = 30;
//	GPIO31 = 31;
} GPIO_BCM;

class SpeedController
{
	public:
		SpeedController(GPIO_BCM pin);
		virtual ~SpeedController();
		virtual void calibrate(void) = 0;

	private:
		virtual void full_on(void) = 0;
		virtual void full_off(void) = 0;
}

class OneShot125 : public SpeedController
{
	public:
		OneShot125(GPIO_BCM pin);
		virtual ~OneShot125();
		virtual void calibrate(void);

	private:
		virtual void full_on(void);
		virtual void full_off(void);
}

#endif // __Speed_Controller_h__
