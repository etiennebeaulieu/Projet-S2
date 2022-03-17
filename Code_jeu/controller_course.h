#ifndef CONTROLLER_COURSE_H
#define CONTROLER_COURSE_H
#include <Windows.h>
#include "model_auto.h"
#include "model_circuit.h"
#include "position.h"
#include "timer.h"


class Controller_course {

public:
	Controller_course();
	Controller_course(ModelAuto* pCar, ModelCircuit* pCircuit);
	~Controller_course();

	void setAuto(ModelAuto pCar);
	ModelAuto getAuto();
	void setCircuit(ModelCircuit pCircuit);
	ModelCircuit getCircuit();

	void startRace();
	void move(float pAngle, int pMovement);

	void updateScreenConsole();
	void updateScreenGUI();

	void gotoXY(int x, int y);
	void demoConsole();

	
private:
	ModelAuto car;
	ModelCircuit circuit;
	long time;
	int demo[][2];
	Timer timer;
};

#endif