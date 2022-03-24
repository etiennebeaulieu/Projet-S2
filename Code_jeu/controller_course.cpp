#include "controller_course.h"


Controller_course::Controller_course()
{
	ModelAuto* car = new ModelAuto();
	ModelCircuit* circuit = new ModelCircuit();
	ControllerMenu* menu = new ControllerMenu();
	Controller_course(car, circuit, menu);
}

Controller_course::Controller_course(ModelAuto* pCar, ModelCircuit* pCircuit, ControllerMenu* pControllerMenu)
{
	car = *pCar;
	circuit = *pCircuit;
	menuControleur = *pControllerMenu;

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

	//TODO Lights sequence on controller

	std::thread course(&courseThread);
	course.join();

	menuControleur.printMenu();

	//demoConsole();
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
	//TODO once we have GUI
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
		std::cout << time / 1000 << ":" << (time/10)%100;
		Sleep(100);
	}
	Sleep(5000);
}

void Controller_course::saveLeaderboard()
{
	//TODO Save current time, car and circuit in the appropriate leaderboard file
}

void Controller_course::menuThread(int selected)
{
	bool btn1 = 0;	//Avant gauche
	bool btn2 = 0;	//Avant droit
	bool btn3 = 0;	//Gachette gauche
	bool btn4 = 0;	//Gacehtte droite
	float x = 0;	//Joystick axe X
	int y = 0;		//Joystick axe y
	float acc = 0;	//Angle acceleromètre
	int optionSelected = 0;		//Bouton surligné dans le menu
	//0 = Resume
	//1 = Options
	//2 = Quit

	int previousBtn1 = 0;
	int previousY = 0;


	system("CLS");
	std::cout << "MENU PAUSE" << std::endl;
	std::cout << "1. Continuer\n2. Options\n3. Retourner au menu" << std::endl;

	gotoXY(0, 1);

	while (1) {
		//TODO Lire JSON Arduino




		if (y == -1 && previousY == 0 && optionSelected < 2) {
			optionSelected++;
			gotoXY(0, optionSelected);
		}
		else if (y == 1 && previousY == 0 && optionSelected > 0) {
			optionSelected--;
			gotoXY(0, optionSelected);
		}
		else if (btn1 == 1 && previousBtn1 == 0) {
			selected = optionSelected;
			std::abort();
		}
			


		Sleep(30);
	}
}


void Controller_course::courseThread()
{
	bool btn1 = 0;	//Avant gauche
	bool btn2 = 0;	//Avant droit
	bool btn3 = 0;	//Gachette gauche
	bool btn4 = 0;	//Gacehtte droite
	float x = 0;	//Joystick axe X
	int y = 0;		//Joystick axe y
	float acc = 0;	//Angle acceleromètre
	int optionSelected;


	while (1) {

		//TODO Lecture JSON Arduino et split dans les différentes variables






		if (btn1 == 1) {		//Bouton pause
			timer.stop();
			std::promise<int> promiseObj;
			std::future<int> futureObj = promiseObj.get_future();
			std::thread menu(&menuThread, &promiseObj);
			optionSelected = futureObj.get();
			menu.join();

			switch (optionSelected)
			{
			case 0:
				system("CLS");
				std::cout << circuit << std::endl;
				updateScreenConsole();
				timer.start();
				break;
			case 1:
				menuControleur.openSettings();
				//TODO Coming back from settings
				break;
			case 2:
				saveLeaderboard();
				timer.reset();
				system("CLS");
				std::abort();
				break;
			default:
				break;
			}
		}


		timer.get();
		//TODO Envoyer time au Arduino
		

		if (sorteControle == true)
			move(x, btn4 - btn3);
		else
			move(acc, btn4 - btn3);
		
		Sleep(30);
	}


}