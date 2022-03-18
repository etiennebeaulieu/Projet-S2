#include "timer.h"
#include <chrono>

#define current_time_ms std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count()

Timer::Timer() {
	startTime = 0;
	stopTime = 0;
}

Timer::~Timer()
{
}

void Timer::start() {
	if (startTime != 0 && stopTime != 0) {
		startTime = current_time_ms - get();
	}
	else {
		startTime = current_time_ms;
	}
	stopTime = 0;
}

void Timer::stop() {
	stopTime = current_time_ms;
}

void Timer::reset() {
	startTime = 0;
	stopTime = 0;
}

void Timer::resetAndStart() {
	startTime = current_time_ms;
	stopTime = 0;
}

unsigned long Timer::get(){
	if (stopTime == 0) {
		return current_time_ms - startTime;
	}

	return stopTime - startTime;
}

bool Timer::isStarted() {
	return (startTime != 0 && stopTime == 0);
}
