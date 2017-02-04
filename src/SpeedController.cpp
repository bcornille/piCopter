#include <pigpio.h>
#include <thread>
#include <chrono>
#include <iostream>

#include "SpeedController.hpp"

SpeedController::SpeedController(GPIO_BCM pin)
{
	gpioInitialise();
}

SpeedController::~SpeedController()
{
	gpioTernimate();
}

OneShot125::OneShot125(GPIO_BCM pin) : SpeedController(pin) {}

OneShot125::~OneShot125() {}

void OneShot125::calibrate(void)
{
}

void OneShot125::full_off(void)
{
}

void OneShot125::full_off(void)
{
}
