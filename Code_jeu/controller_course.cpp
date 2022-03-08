#include "controller_course.h"
#include <iostream>

Controller_course::Controller_course()
{
	ModelAuto* car = new ModelAuto();
	ModelCircuit* circuit = new ModelCircuit();
	Controller_course(car, circuit);
}

Controller_course::Controller_course(ModelAuto* pCar, ModelCircuit* pCircuit)
{
	car = *pCar;
	circuit = *pCircuit;

	circuit.generateBorders();

	

	std::ifstream sDemo;
	sDemo.open("demo.txt");
	//lire fichier demo et mettre dans le tableau
	for (int i = 0; i < 170; i++)
	{
		sDemo >> demo[i][0] >> demo[i][1];
	}
}

Controller_course::~Controller_course()
{
}

void Controller_course::setAuto(ModelAuto pCar)
{
	car = pCar;
}

ModelAuto Controller_course::getAuto()
{
	return car;
}

void Controller_course::setCircuit(ModelCircuit pCircuit)
{
	circuit = pCircuit;
}

ModelCircuit Controller_course::getCircuit()
{
	return circuit;
}

void Controller_course::startRace()
{
	Position start =  circuit.getStart();
	std::cout << circuit << std::endl;
	car.setPostion(start);
	updateScreenConsole();

	demoConsole();
}

void Controller_course::move(float pAngle, int pMovement)
{
	Position temp = car.move(pAngle, pMovement);
	if (temp.x <= circuit.getWidth() && temp.y <= circuit.getHeight()) {
		if (circuit.positionIsActive(temp)) {
			gotoXY(round(car.getPosition().x), round(car.getPosition().y));
			std::cout << " ";
			car.setPostion(temp);
		}
	}
		

	updateScreenConsole();
}

void Controller_course::updateScreenConsole()
{
	gotoXY(round(car.getPosition().x), round(car.getPosition().y));
	std::cout << "*";
}

void Controller_course::updateScreenGUI()
{
}

void Controller_course::gotoXY(int x, int y)
{
	COORD scrn;
	HANDLE houtput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = 2*x;
	scrn.Y = y;
	SetConsoleCursorPosition(houtput, scrn);
}

void Controller_course::demoConsole()
{
	time = 0;
	for (int i = 0; i < 170; i++) {
		time += 100;
		move(demo[i][0], demo[i][1]);

		gotoXY(50, 50);
		std::cout << time / 1000 << ":" << (time/100)%10;
		Sleep(100);
	}
	Sleep(5000);

}




