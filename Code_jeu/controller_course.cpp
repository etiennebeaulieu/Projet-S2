#include "controllers.h"


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
	menuControleur = pControllerMenu;
	arduino = menuControleur->arduino;

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

	int sequenceGreen[5] = { 0, 0, 0, 0, 1 };
	int sequenceR1[5] = { 0, 1, 1, 1, 1 };
	int sequenceR2[5] = { 0, 0, 1, 1, 1 };
	int sequenceR3[5] = { 0, 0, 0, 1, 1 };
	int sequenceMoteur[5] = { 0, 0, 0, 0, 1 };

	//TODO Lights sequence on controller
	for (int i = 0; i < 5; i++) {
		
		Sleep(500);
		
		j_msg_send["G"] = sequenceGreen[i];      // Création du message à envoyer
		j_msg_send["1"] = sequenceR1[i];
		j_msg_send["2"] = sequenceR2[i];
		j_msg_send["3"] = sequenceR3[i];
		j_msg_send["M"] = sequenceMoteur[i];

		if (!SerialCommunication::SendToSerial(arduino, j_msg_send)) {    //Envoie au Arduino
			std::cerr << "Erreur lors de l'envoie du message. " << std::endl;
		}

		j_msg_rcv.clear();
		if (!SerialCommunication::RcvFromSerial(arduino, raw_msg)) {
			std::cerr << "Erreur lors de la réception du message. " << std::endl;
		}
	}

	timer.start();
	std::thread course(&Controller_course::courseThread, this);
	course.join();

	menuControleur->printMenu();

	//demoConsole();
}

bool Controller_course::move(float pAngle, int pMovement)
{
	Position temp = car.move(pAngle, pMovement);
	if (temp.x <= circuit.getWidth() && temp.y <= circuit.getHeight()) {
		if (circuit.positionIsActive(temp)) {
			gotoXY(round(car.getPosition().x), round(car.getPosition().y));
			std::cout << " ";
			car.setPostion(temp);
		}
		else
			return false;
	}


	return true;
}

void Controller_course::updateScreenConsole()
{
	gotoXY(round(car.getPosition().x), round(car.getPosition().y));
	std::cout << "*";

	gotoXY(50, 50);
	unsigned long temps = timer.get();
	std::cout << temps / 60000 << ":" << std::setw(2) << std::setfill('0') << (temps / 1000) % 60 << ":" << (temps / 10) % 100;
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

void Controller_course::menuThread(Controller_course* controller)
{
	controller->j_msg_send["G"] = 1;      // Création du message à envoyer
	controller->j_msg_send["1"] = 1;
	controller->j_msg_send["2"] = 1;
	controller->j_msg_send["3"] = 1;
	controller->j_msg_send["S"] = 0;

	int optionSelected = 1;		//Bouton surligné dans le menu
	//0 = Resume
	//1 = Options
	//2 = Quit

	int previousBtn3 = 0;
	int previousBtn4 = 0;
	int previousY = 0;
	std::string raw_msg;

	//Pour contrôle clavier seulement
	SHORT up = 0;
	SHORT down = 0;
	SHORT previousUp = 0;
	SHORT previousDown = 0;
	SHORT enter = 0;


	system("CLS");
	std::cout << "MENU PAUSE" << std::endl;
	std::cout << "1. Continuer\n2. Options\n3. Retourner au menu" << std::endl;

	controller->gotoXY(0, 1);

	Sleep(100);

	while (1) {
		//TODO Lire JSON Arduino
		previousY = controller->joyStickY;
		previousBtn3 = controller->bouton3;
		previousBtn4 = controller->bouton4;


		if (!SerialCommunication::SendToSerial(controller->arduino, controller->j_msg_send)) {    //Envoie au Arduino
			std::cerr << "Erreur lors de l'envoie du message. " << std::endl;
		}

		controller->j_msg_rcv.clear();
		if (!SerialCommunication::RcvFromSerial(controller->arduino, raw_msg)) {
			std::cerr << "Erreur lors de la réception du message. " << std::endl;
		}



		// Impression du message de l'Arduino, si valide
		if (raw_msg.size() > 0) {
			controller->j_msg_rcv = json::parse(raw_msg);       // Transfert du message en json
			if (controller->j_msg_rcv.contains("Y"))
				controller->joyStickY = controller->j_msg_rcv["Y"];
			if (controller->j_msg_rcv.contains("3"))
				controller->bouton3 = controller->j_msg_rcv["3"];
			if (controller->j_msg_rcv.contains("4"))
				controller->bouton4 = controller->j_msg_rcv["4"];
		}

		//std::cout << controller->j_msg_rcv << std::endl;

		//Contôle au clavier seulement
		previousUp = up;
		previousDown = down;

		up = GetKeyState(VK_UP);
		down = GetKeyState(VK_DOWN);
		enter = GetKeyState(VK_RETURN);

		
		if (((controller->joyStickY == -1 && previousY != -1) || (down < 0 && previousDown >= 0)) && optionSelected < 3) {
			optionSelected++;
			controller->gotoXY(0, optionSelected);
		}
		else if (((controller->joyStickY == 1 && previousY != 1) || (up < 0 && previousUp >= 0)) && optionSelected > 1) {
			optionSelected--;
			controller->gotoXY(0, optionSelected);
		}
		else if ((controller->bouton3 == 1 && previousBtn3 == 0) || enter < 0) {
			controller->optionSelected = optionSelected-1;
			break;
		}



		Sleep(30);
	}
	
}




void Controller_course::courseThread(Controller_course* controller)
{
	controller->j_msg_send["G"] = 0;      // Création du message à envoyer
	controller->j_msg_send["1"] = 0;
	controller->j_msg_send["2"] = 0;
	controller->j_msg_send["3"] = 0;
	controller->j_msg_send["S"] = 0;

	bool fin = false;
	bool dansLimite = true;


	//Pour contrôle clavier seulement
	SHORT up = 0;
	SHORT down = 0;
	SHORT esc = 0;


	while (1) {
		//TODO Lecture JSON Arduino et split dans les différentes variables

		if (!SerialCommunication::SendToSerial(controller->arduino, controller->j_msg_send)) {    //Envoie au Arduino
			std::cerr << "Erreur lors de l'envoie du message. " << std::endl;
		}

		controller->j_msg_rcv.clear();
		if (!SerialCommunication::RcvFromSerial(controller->arduino, controller->raw_msg)) {
			std::cerr << "Erreur lors de la réception du message. " << std::endl;
		}

		// Impression du message de l'Arduino, si valide

		if (controller->raw_msg.size() > 0) {
			controller->j_msg_rcv = json::parse(controller->raw_msg); // Transfert du message en json
			if (controller->j_msg_rcv.contains("A"))
				controller->acc_Value = controller->j_msg_rcv["A"];
			if (controller->j_msg_rcv.contains("X"))
				controller->joyStickX = controller->j_msg_rcv["X"];
			if (controller->j_msg_rcv.contains("Y"))
				controller->joyStickY = controller->j_msg_rcv["Y"];
			if (controller->j_msg_rcv.contains("1"))
				controller->bouton1 = controller->j_msg_rcv["1"];
			if (controller->j_msg_rcv.contains("2"))
				controller->bouton2 = controller->j_msg_rcv["2"];
			if (controller->j_msg_rcv.contains("3"))
				controller->bouton3 = controller->j_msg_rcv["3"];
			if (controller->j_msg_rcv.contains("4"))
				controller->bouton4 = controller->j_msg_rcv["4"];
		}


		std::cout << controller->j_msg_rcv << std::endl;



		//Contôle au clavier
		up = GetKeyState(VK_UP);
		down = GetKeyState(VK_DOWN);
		esc = GetKeyState(VK_ESCAPE);
		if (up < 0)
			up = 1;
		else
			up = 0;


		if (down < 0)
			down = 1;
		else
			down = 0;





		
		if (controller->bouton4 == 1 || esc < 0) {		//Bouton pause
			controller->timer.stop();

			std::thread menu(&Controller_course::menuThread, controller);
			menu.join();



			switch (controller->optionSelected)
			{
			case 0:
				controller->optionSelected = 0;
				system("CLS");
				std::cout << controller->circuit << std::endl;
				controller->updateScreenConsole();
				controller->timer.start();
				break;
			case 1:
				controller->optionSelected = 0;
				controller->menuControleur->openSettings();
				//TODO Coming back from settings
				break;
			case 2:
				controller->optionSelected = 0;
				controller->saveLeaderboard();
				controller->timer.reset();
				system("CLS");
				fin = true;
				break;
			default:
				break;
			}

			if (fin)
				break;

		}

		if (controller->sorteControle == 0)
			dansLimite = controller->move(controller->joyStickX, controller->bouton2 - controller->bouton1);
		else if (controller->sorteControle == 1)
			dansLimite = controller->move(controller->acc_Value, controller->bouton2 - controller->bouton1);
		else
			dansLimite = controller->move(0, down - up);


		//TODO Envoyer time au Arduino
		controller->j_msg_send["S"] = controller->timer.get();
		controller->j_msg_send["G"] = 0;      // Création du message à envoyer
		
		if (dansLimite) {
			controller->j_msg_send["M"] = 0;
			controller->j_msg_send["1"] = 0;
			controller->j_msg_send["2"] = 0;
			controller->j_msg_send["3"] = 0;
		}
		else {
			controller->j_msg_send["M"] = 1;
			controller->j_msg_send["1"] = 1;
			controller->j_msg_send["2"] = 1;
			controller->j_msg_send["3"] = 1;
		}
		




		

		controller->updateScreenConsole();

		Sleep(30);
	}

}
