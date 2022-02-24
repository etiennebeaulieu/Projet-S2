#include "model_auto.h"
#include "model_circuit.h"
#include <Windows.h>


class Controller_course {

public:
	Controller_course();
	Controller_course(Model_auto* pCar, ModelCircuit* pCircuit);
	~Controller_course();

	void setAuto(Model_auto pCar);
	Model_auto getAuto();
	void setCircuit(ModelCircuit pCircuit);
	ModelCircuit getCircuit();

	void startRace();
	void move(float pAngle, int pMovement);

	void updateScreenConsole();
	void updateScreenGUI();

	void gotoXY(int x, int y);
	void demoConsole();

	
private:
	Model_auto car;
	ModelCircuit circuit;




};
