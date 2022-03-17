#ifndef TIMER_H
#define TIMER_H

class Timer
{
public:
	Timer();
	~Timer();

	void start();
	void stop();

	unsigned long get();

	bool isStarted();

private:
	unsigned long startTime;
	unsigned long stopTime;
};

#endif // !TIMER_H
