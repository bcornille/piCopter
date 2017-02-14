#include <pigpio.h>
#include <thread>
#include <chrono>
#include <iostream>
#include <array>

#include "SpeedController.hpp"

SpeedController::SpeedController(std::array<GPIO_BCM, 4> pins) : m_pins(pins)
{
	int init_status = -1;
	while (gpioInitialise() < 0)
	{
		std::this_thread::sleep_for(std::chrono::seconds(1));
		std::cout << "PiGPIO not yet initialised." << std::endl;
	}
}

SpeedController::~SpeedController()
{
	gpioTerminate();
}

OneShot125::OneShot125(std::array<GPIO_BCM, 4> pins) : SpeedController(pins) {}

OneShot125::~OneShot125() {}

void OneShot125::calibrate(void)
{
	// TODO: check status values for verified send.
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

	on[0].gpioOn = 1 << m_pins[0];
	on[0].gpioOff = 0;
	on[0].usDelay = 250;
	on[1].gpioOn = 0;
	on[1].gpioOff = 1 << m_pins[0];
	on[1].usDelay = 250;

	gpioWaveAddGeneric(1, on);

	on[0].gpioOn = 1 << m_pins[1];
	on[0].gpioOff = 0;
	on[0].usDelay = 250;
	on[1].gpioOn = 0;
	on[1].gpioOff = 1 << m_pins[1];
	on[1].usDelay = 250;

	gpioWaveAddGeneric(1, on);

	on[0].gpioOn = 1 << m_pins[2];
	on[0].gpioOff = 0;
	on[0].usDelay = 250;
	on[1].gpioOn = 0;
	on[1].gpioOff = 1 << m_pins[2];
	on[1].usDelay = 250;

	gpioWaveAddGeneric(1, on);

	on[0].gpioOn = 1 << m_pins[3];
	on[0].gpioOff = 0;
	on[0].usDelay = 250;
	on[1].gpioOn = 0;
	on[1].gpioOff = 1 << m_pins[3];
	on[1].usDelay = 250;

	gpioWaveAddGeneric(1, on);

	return gpioWaveCreate();
}

int OneShot125::full_off(void)
{
	gpioPulse_t on[2];

	on[0].gpioOn = 1 << m_pins[0];
	on[0].gpioOff = 0;
	on[0].usDelay = 125;
	on[1].gpioOn = 0;
	on[1].gpioOff = 1 << m_pins[0];
	on[1].usDelay = 375;

	gpioWaveAddGeneric(1, on);

	on[0].gpioOn = 1 << m_pins[1];
	on[0].gpioOff = 0;
	on[0].usDelay = 125;
	on[1].gpioOn = 0;
	on[1].gpioOff = 1 << m_pins[1];
	on[1].usDelay = 375;

	gpioWaveAddGeneric(1, on);

	on[0].gpioOn = 1 << m_pins[2];
	on[0].gpioOff = 0;
	on[0].usDelay = 125;
	on[1].gpioOn = 0;
	on[1].gpioOff = 1 << m_pins[2];
	on[1].usDelay = 375;

	gpioWaveAddGeneric(1, on);

	on[0].gpioOn = 1 << m_pins[3];
	on[0].gpioOff = 0;
	on[0].usDelay = 125;
	on[1].gpioOn = 0;
	on[1].gpioOff = 1 << m_pins[3];
	on[1].usDelay = 375;

	gpioWaveAddGeneric(1, on);

	return gpioWaveCreate();
}
