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
	int status = gpioWaveTxSend(on_id, PI_WAVE_MODE_ONE_SHOT_SYNC);
	std::this_thread::sleep_for(std::chrono::seconds(3));

	int off_id = full_off();
	status = gpioWaveTxSend(off_id, PI_WAVE_MODE_ONE_SHOT_SYNC);
	std::this_thread::sleep_for(std::chrono::seconds(3));

	status = gpioWaveDelete(on_id);
	status = gpioWaveDelete(off_id);
}

int OneShot125::full_on(void)
{
	gpioPulse_t on[2];

	on[0].gpioOn = 1 << m_pin[0];
	on[0].gpioOff = 0;
	on[0].usDelay = 250;
	on[1].gpioOn = 0;
	on[1].gpioOff = 1 << m_pin[0];
	on[1].usDelay = 250;

	gpioWaveAddGeneric(1, on);

	on[0].gpioOn = 1 << m_pin[1];
	on[0].gpioOff = 0;
	on[0].usDelay = 250;
	on[1].gpioOn = 0;
	on[1].gpioOff = 1 << m_pin[1];
	on[1].usDelay = 250;

	gpioWaveAddGeneric(1, on);

	on[0].gpioOn = 1 << m_pin[2];
	on[0].gpioOff = 0;
	on[0].usDelay = 250;
	on[1].gpioOn = 0;
	on[1].gpioOff = 1 << m_pin[2];
	on[1].usDelay = 250;

	gpioWaveAddGeneric(1, on);

	on[0].gpioOn = 1 << m_pin[3];
	on[0].gpioOff = 0;
	on[0].usDelay = 250;
	on[1].gpioOn = 0;
	on[1].gpioOff = 1 << m_pin[3];
	on[1].usDelay = 250;

	gpioWaveAddGeneric(1, on);

	return gpioWaveCreate();
}

int OneShot125::full_off(void)
{
	gpioPulse_t on[2];

	on[0].gpioOn = 1 << m_pin[0];
	on[0].gpioOff = 0;
	on[0].usDelay = 125;
	on[1].gpioOn = 0;
	on[1].gpioOff = 1 << m_pin[0];
	on[1].usDelay = 375;

	gpioWaveAddGeneric(1, on);

	on[0].gpioOn = 1 << m_pin[1];
	on[0].gpioOff = 0;
	on[0].usDelay = 125;
	on[1].gpioOn = 0;
	on[1].gpioOff = 1 << m_pin[1];
	on[1].usDelay = 375;

	gpioWaveAddGeneric(1, on);

	on[0].gpioOn = 1 << m_pin[2];
	on[0].gpioOff = 0;
	on[0].usDelay = 125;
	on[1].gpioOn = 0;
	on[1].gpioOff = 1 << m_pin[2];
	on[1].usDelay = 375;

	gpioWaveAddGeneric(1, on);

	on[0].gpioOn = 1 << m_pin[3];
	on[0].gpioOff = 0;
	on[0].usDelay = 125;
	on[1].gpioOn = 0;
	on[1].gpioOff = 1 << m_pin[3];
	on[1].usDelay = 375;

	gpioWaveAddGeneric(1, on);

	return gpioWaveCreate();
}
