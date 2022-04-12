#include "controllers.h"


Controller_course::Controller_course(ModelAuto* pCar, ModelCircuit* pCircuit, ControllerMenu* pControllerMenu)
{
	car = *pCar;
	circuit = *pCircuit;
	menuControleur = pControllerMenu;
	arduino = menuControleur->arduino;

	leaderboard.loadFromMap(pCircuit->getName());
	ghostCourseRecord.loadFromMap(pCircuit->getName());
	currentCourseRecord.setMapName(pCircuit->getName());

	circuit.generateBorders();
	lastTime = 0;

	courseWindow = menuControleur->mainWindow->courseWindow;
	initiateGUI();
	
	QMetaObject::invokeMethod(menuControleur->mainWindow, "showCourse");
	

	
	
	

}

Controller_course::~Controller_course()
{
	//TODO Destructeur Controller_course
}

void Controller_course::initiateGUI()
{
	courseWindow->backgroundCourse->setPixmap(QPixmap(QString::fromStdString((string)"image/" + circuit.getName() + ".png")));

	courseWindow->car->setPixmap(QPixmap(QString::fromStdString((string)"image/" + this->car.getName() + ".png")));
	courseWindow->car->setScale(0.25);

	courseWindow->ghost->setPixmap(QPixmap(QString::fromStdString((string)"image/ghostCar.png")));
	courseWindow->ghost->setScale(0.25);
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

/*
* Affiche le circuit et fait la sï¿½quence de lumiï¿½res sur la manette et commence le thread de la course
*/
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

	for (int i = 0; i < 5; i++) {
		
		Sleep(500);
		
		j_msg_send["G"] = sequenceGreen[i];      // Crï¿½ation du message ï¿½ envoyer
		j_msg_send["1"] = sequenceR1[i];
		j_msg_send["2"] = sequenceR2[i];
		j_msg_send["3"] = sequenceR3[i];
		j_msg_send["M"] = sequenceMoteur[i];

		if (!SerialCommunication::SendToSerial(arduino, j_msg_send)) {		//Envoie au Arduino
			std::cerr << "Erreur lors de l'envoie du message. " << std::endl;
		}

		j_msg_rcv.clear();
		if (!SerialCommunication::RcvFromSerial(arduino, raw_msg)) {		//Reï¿½oit du Arduino
			std::cerr << "Erreur lors de la rï¿½ception du message. " << std::endl;
		}
	}

	timer.resetAndStart();

	//Course record
	currentCourseRecord.clear();
	currentCourseRecord.recordTimeAndPosition(start, timer.get());

	std::thread course(&Controller_course::courseThread, this);
	course.join();



	


	//Affiche le menu en fin de course
	menuControleur->printMenu();

	//demoConsole();
}

/*
* Vï¿½rifie que la nouvelle position est valide et change la position
* Retourne vrai si la dï¿½placement se fait, faux sinon
*/
bool Controller_course::move(float pAngle, int pMovement)
{
	Position temp = car.move(pAngle, pMovement);
	if (temp.y <= circuit.getWidth() && temp.x <= circuit.getHeight()) {
		if (circuit.positionIsActive(temp)) {
			gotoXY(round(car.getPosition().x), round(car.getPosition().y));
			std::cout << " ";
			car.setPostion(temp);

			//Course record
			currentCourseRecord.recordTimeAndPosition(temp, timer.get());

		}
		else
			return false;
	}


	return true;
}

/*
* Update la console aprï¿½s un dï¿½placement
* Deprecated une fois qu'on a un GUI
*/
void Controller_course::updateScreenConsole()
{
	gotoXY(round(car.getPosition().x), round(car.getPosition().y));
	std::cout << "*";


	gotoXY(round(ghostPos.x), round(ghostPos.y));
	std::cout << " ";
	Sleep(10);
	ghostPos = ghostCourseRecord.getPositionAtTime(timer.get());
	gotoXY(round(ghostPos.x), round(ghostPos.y));
	std::cout << "#";

	gotoXY(50, 50);
	unsigned long temps = timer.get();
	std::cout << temps / 60000 << ":" << std::setw(2) << std::setfill('0') << (temps / 1000) % 60 << ":" << (temps / 10) % 100;
}

/*
* Fait les appels pour update le GUI
*/
void Controller_course::updateScreenGUI()
{
	//TODO Faire les calls à l'interface. Se baser sur updateScreenConsole
	QMetaObject::invokeMethod(menuControleur->mainWindow->courseWindow, "moveCar", Q_ARG(float, car.getPosition().x), Q_ARG(float, car.getPosition().y), Q_ARG(float, car.getPosition().angle));
	QMetaObject::invokeMethod(menuControleur->mainWindow->courseWindow, "moveGhost", Q_ARG(float, ghostPos.x), Q_ARG(float, ghostPos.y), Q_ARG(float,ghostPos.angle));
	QMetaObject::invokeMethod(menuControleur->mainWindow->courseWindow, "updateTimer", Q_ARG(unsigned long, timer.get()), Q_ARG(unsigned long, leaderboard.getTime(0).time),Q_ARG(unsigned long, lastTime));
}

/*
* Helper method pour deplacer le curseur sur le command prompt
*/
void Controller_course::gotoXY(int x, int y)
{
	COORD scrn;
	HANDLE houtput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = 2*x;
	scrn.Y = y;
	SetConsoleCursorPosition(houtput, scrn);
}

/*
* Sauvegarde le temps dans le leaderboard
*/
void Controller_course::saveLeaderboard(){
	BestTime bt;
	bt.name = "Player1"; //TODO remplacer ï¿½a par le nom du player
	bt.time = timer.get();
	leaderboard.newTime(bt);
	leaderboard.save();

	//Course record en fin de course
	if (leaderboard.isBestTime(timer.get())) {
		//Si on vient de faire le meilleur temps, on va update le courseRecord qui est save pour celui qu'on vient de faire.
		currentCourseRecord.save();
	}
}

/**
* Termine la course
*/
void Controller_course::endRace() {
	
}


/*
* Thread du menu pause
*/
void Controller_course::menuThread(Controller_course* controller)
{
	controller->j_msg_send["G"] = 1;		// Crï¿½ation du message ï¿½ envoyer
	controller->j_msg_send["1"] = 1;
	controller->j_msg_send["2"] = 1;
	controller->j_msg_send["3"] = 1;
	controller->j_msg_send["S"] = 0;

	int optionSelected = 1;					//Bouton surlignï¿½ dans le menu
	//0 = Resume
	//1 = Options
	//2 = Quit

	//Pour contrï¿½le manette
	int previousBtn3 = 0;
	int previousBtn4 = 0;
	int previousY = 0;
	std::string raw_msg;

	//Pour contrï¿½le clavier seulement
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
		previousY = controller->joyStickY;
		previousBtn3 = controller->bouton3;
		previousBtn4 = controller->bouton4;


		if (!SerialCommunication::SendToSerial(controller->arduino, controller->j_msg_send)) {    //Envoie au Arduino
			std::cerr << "Erreur lors de l'envoie du message. " << std::endl;
		}

		controller->j_msg_rcv.clear();
		if (!SerialCommunication::RcvFromSerial(controller->arduino, raw_msg)) {
			std::cerr << "Erreur lors de la rï¿½ception du message. " << std::endl;
		}



		
		if (raw_msg.size() > 0) {
			controller->j_msg_rcv = json::parse(raw_msg);			// Transfert du message en json
			if (controller->j_msg_rcv.contains("Y"))
				controller->joyStickY = controller->j_msg_rcv["Y"];
			if (controller->j_msg_rcv.contains("3"))
				controller->bouton3 = controller->j_msg_rcv["3"];
			if (controller->j_msg_rcv.contains("4"))
				controller->bouton4 = controller->j_msg_rcv["4"];
		}


		//Pour dï¿½bogage pour afficher la lecture du JSON
		//std::cout << controller->j_msg_rcv << std::endl;


		//Contï¿½le au clavier seulement
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



/*
* Thread de la course, lit en permanance la manette pour gï¿½rer les dï¿½placement de l'auto
*/
void Controller_course::courseThread(Controller_course* controller)
{
	controller->j_msg_send["G"] = 0;      // Crï¿½ation du message ï¿½ envoyer
	controller->j_msg_send["1"] = 0;
	controller->j_msg_send["2"] = 0;
	controller->j_msg_send["3"] = 0;
	controller->j_msg_send["S"] = 0;

	bool fin = false;
	bool dansLimite = true;


	//Pour contrï¿½le clavier seulement
	SHORT up = 0;
	SHORT down = 0;
	SHORT esc = 0;


	while (1) {
		if (!SerialCommunication::SendToSerial(controller->arduino, controller->j_msg_send)) {    //Envoie au Arduino
			std::cerr << "Erreur lors de l'envoie du message. " << std::endl;
		}

		controller->j_msg_rcv.clear();
		if (!SerialCommunication::RcvFromSerial(controller->arduino, controller->raw_msg)) {
			std::cerr << "Erreur lors de la rï¿½ception du message. " << std::endl;
		}
		

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


		//Pour dï¿½bogage affiche les valeurs du JSON
		std::cout << controller->j_msg_rcv << std::endl;



		//Contï¿½le au clavier pour dï¿½bogage, permet seulement d'avancer en ligne droite et contrï¿½le du menu
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
			BestTime bt;


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
				//controller->saveLeaderboard();

				
				bt.name = "Player1"; //TODO remplacer ï¿½a par le nom du player
				bt.time = controller->timer.get();
				controller->leaderboard.newTime(bt);
				controller->leaderboard.save();

				//Course record en fin de course
				if (controller->leaderboard.isBestTime(controller->timer.get())) {
					//Si on vient de faire le meilleur temps, on va update le courseRecord qui est save pour celui qu'on vient de faire.
					controller->currentCourseRecord.save();
				}

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
		if (controller->bouton1 == 1 || controller->bouton2 == 1) {
			if (controller->sorteControle == 0)
				dansLimite = controller->move(controller->joyStickX, controller->bouton2 - controller->bouton1);
			else if (controller->sorteControle == 1)
				dansLimite = controller->move(controller->acc_Value, controller->bouton2 - controller->bouton1);
			else
				dansLimite = controller->move(0, down - up);
		}


		controller->j_msg_send["S"] = controller->timer.get();
		controller->j_msg_send["G"] = 0;      // Crï¿½ation du message ï¿½ envoyer
		
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
		

		//Regarde si on  est rendu ï¿½ la ligne d'arrivï¿½e et que ï¿½a fait plus que x secondes qu'on race
		if (controller->circuit.positionIsOnFinishLine(controller->car.getPosition()) && (controller->timer.get() >= 5000)) {
			BestTime bt;
			bt.name = "Player1"; //TODO remplacer ï¿½a par le nom du player
			bt.time = controller->timer.get();
			controller->leaderboard.newTime(bt);
			controller->leaderboard.save();

			//Course record en fin de course
			if (controller->leaderboard.isBestTime(controller->timer.get())) {
				//Si on vient de faire le meilleur temps, on va update le courseRecord qui est save pour celui qu'on vient de faire.
				controller->currentCourseRecord.save();
			}


			controller->lastTime = controller->timer.get();
			controller->timer.resetAndStart();
			
		}


		controller->updateScreenConsole();
		controller->updateScreenGUI();

		Sleep(30);
	}

}
