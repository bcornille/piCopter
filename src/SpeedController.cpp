#include <pigpio.h>
#include <thread>
#include <chrono>
#include <iostream>

#include "SpeedController.hpp"

SpeedController::SpeedController(GPIO_BCM pin[4]) : m_pin(pin)
{
	gpioInitialise();
}

SpeedController::~SpeedController()
{
	gpioTernimate();
}

OneShot125::OneShot125(GPIO_BCM pin[4]) : SpeedController(pin) {}

OneShot125::~OneShot125() {}

void OneShot125::calibrate(void)
{
	int on_id = full_on();
	int status = gpioWaveTxSend(wave_id, PI_WAVE_MODE_ONE_SHOT_SYNC);
	std::this_thread::sleep_for(std::chrono::seconds(3));

	int off_id = full_on();
	status = gpioWaveTxSend(wave_id, PI_WAVE_MODE_ONE_SHOT_SYNC);
	std::this_thread::sleep_for(std::chrono::seconds(3));

	status = gpioWaveDelete(on_id);
	status = gpioWaveDelete(off_id);
}

int OneShot125::full_on(void)
{
	gpioPulse_t on;

	on.gpioOn = 1 << m_pin[0];
	on.gpioOff = 0;
	on.usDelay = 250;

	gpioWaveAddGeneric(1, on);

	on.gpioOn = 1 << m_pin[1];
	on.gpioOff = 0;
	on.usDelay = 250;

	gpioWaveAddGeneric(1, on);

	on.gpioOn = 1 << m_pin[2];
	on.gpioOff = 0;
	on.usDelay = 250;

	gpioWaveAddGeneric(1, on);

	on.gpioOn = 1 << m_pin[3];
	on.gpioOff = 0;
	on.usDelay = 250;

	gpioWaveAddGeneric(1, on);

	return gpioWaveCreate();
}

int OneShot125::full_off(void)
{
	gpioPulse_t on;

	on.gpioOn = 1 << m_pin[0];
	on.gpioOff = 0;
	on.usDelay = 125;

	gpioWaveAddGeneric(1, on);

	on.gpioOn = 1 << m_pin[1];
	on.gpioOff = 0;
	on.usDelay = 125;

	gpioWaveAddGeneric(1, on);

	on.gpioOn = 1 << m_pin[2];
	on.gpioOff = 0;
	on.usDelay = 125;

	gpioWaveAddGeneric(1, on);

	on.gpioOn = 1 << m_pin[3];
	on.gpioOff = 0;
	on.usDelay = 125;

	gpioWaveAddGeneric(1, on);

	return gpioWaveCreate();
}
