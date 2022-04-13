#include "controllers.h"

ControllerMenu::ControllerMenu()
{
	// Initialisation du port de communication
	std::string com;
	std::cout << "Entrer le port de communication du Arduino (-1 si pas de Arduino): ";
	std::cin >> com;
	
	if (strcmp(com.c_str(), "-1") != 0) {
		arduino = new SerialPort(com.c_str(), BAUD);

		if (!arduino->isConnected()) {
			std::cerr << "Impossible de se connecter au port " << std::string(com) << ". Fermeture du programme!" << std::endl;
			exit(1);
		}

		if (!SerialCommunication::SendToSerial(arduino, j_msg_send)) {				//Lecture pour purger
			std::cerr << "Erreur lors de l'envoie du message. " << std::endl;
		}
		j_msg_rcv.clear();
		if (!SerialCommunication::RcvFromSerial(arduino, raw_msg)) {
			std::cerr << "Erreur lors de la r�ception du message. " << std::endl;
		}
		isConnected = true;
	}
	else {
		isConnected = false;
		sorteControle = 2;
	}

	mutex = new QMutex();

	system("CLS");
	optionSelected = 1;
}

/**
 * Destructeur du controlleur de menu
 */
ControllerMenu::~ControllerMenu(){
	for (int i = 0; i < circuitList.size(); i++) {
		delete circuitList[i];
	}

	for (int i = 0; i < 5; i++) {
		delete carList[i];
	}
	
	delete controllerCourse;
}

void ControllerMenu::startApp(int argc, char** argv)
{
	updateData();
	app = new QApplication(argc, argv);
	mainWindow = (MainWindow*)app->activeWindow();

	mainWindow = new MainWindow();
	menuWindow = mainWindow->menuWindow;
	
	

	QThread* thread = QThread::create([this]() {printMenu(); });
	thread->start();

	mainWindow->show();
	app->exec();
}

/*
* Affiche le menu et g�re les options s�l�ctionn�es
*/
void ControllerMenu::printMenu()
{
	std::cout << "Bienvenue sur SparkUS racing" << std::endl;
	std::cout << "CLASSEMENT\n" << printLeaderboard() << std::endl;
	std::cout << "VOITURE\nNom : "<<carList[currentCar]->getName()<< "\nVitesse :" << carList[currentCar]->getSpeed() << "\nVirage : " << carList[currentCar]->getHandling() << std::endl;
	std::cout << "\nCIRCUIT\nNom : " << circuitList[currentCircuit]->getName() << std::endl;
	std::cout << "1. Play\n2. Reglages\n3. Prochaine voiture\n4. Voiture precedente\n5. Prochain circuit\n6. Circuit precedent\n7. Quitter" << std::endl;
	

	QMetaObject::invokeMethod(mainWindow, "showMenu");

	mutex->lock();

	menuWindow->leaderboardLabel->setText(QString::fromStdString(printLeaderboard()));
	menuWindow->carNameLabel->setText(QString::fromStdString(carList[currentCar]->getName()));
	
	std::stringstream buffer;
	buffer << "Vitesse : " << carList[currentCar]->getSpeed() << "\nManiabilite : " << carList[currentCar]->getHandling();
	menuWindow->carStatsLabel->setText(QString::fromStdString(buffer.str()));
	menuWindow->circuitNameLabel->setText(QString::fromStdString(circuitList[currentCircuit]->getName()));
	QPixmap circuitImage = QPixmap(QString::fromStdString((string)"image/" + circuitList[currentCircuit]->getName() + ".png")).scaled(500, 500);
	menuWindow->circuitLabel->setPixmap(circuitImage);
	
	QPixmap carImage = QPixmap(QString::fromStdString((string)"image/" + carList[currentCar]->getName() + ".png")).scaled(500, 500);
	menuWindow->carLabel->setPixmap(carImage);

	menuWindow->buttons[optionSelected - 1]->setFlat(true);

	
	mutex->unlock();
	
	std::thread menu(&ControllerMenu::menuThread, this);
	menu.join();


	switch (optionSelected) {
	case 1:
		optionSelected = 1;
		startGame();
		system("CLS");
		printMenu();
		break;
	case 2:
		optionSelected = 1;
		system("CLS");
		openSettings();
		break;
	case 3:
		nextCar();
		system("CLS");
		printMenu();
		break;
	case 4:
		previousCar();
		system("CLS");
		printMenu();
		break;
	case 5:
		nextCircuit();
		system("CLS");
		printMenu();
		break;
	case 6:
		previousCircuit();
		system("CLS");
		printMenu();
		break;
	case 7:
		optionSelected = 1;
		exit(1);
		break;
	default:
		optionSelected = 1;
		system("CLS");
		printMenu();
		break;
	}

	
	
}

/*
* Ouvre la fen�tre des options
*/
void ControllerMenu::openSettings()
{
	QMetaObject::invokeMethod(mainWindow, "showSettings");

	int option = optionSelected;
	if (!isConnected)
		optionSelected = 1;
	else
		optionSelected = sorteControle+1;

	QMetaObject::invokeMethod(mainWindow->settingsWindow, "highlight", Q_ARG(int, sorteControle));

	std::thread settings(&ControllerMenu::settingsThread, this);
	settings.join();

	if (isConnected) {
		switch (optionSelected) {
		case 1:
			optionSelected = 1;
			sorteControle = 0;
			break;
		case 2:
			optionSelected = 1;
			sorteControle = 1;
			break;
		default:
			break;
		}
	}

	optionSelected = option;

	printMenu();

	QMetaObject::invokeMethod(mainWindow, "showMenu");
}

/*
* Cr�e l'objet controller_course et commencer la course
*/
void ControllerMenu::startGame()
{
	system("CLS");
	controllerCourse = new Controller_course(carList[currentCar], circuitList[currentCircuit], this);
	//controllerCourse->startRace();
}

void ControllerMenu::nextCar()
{
	currentCar = (currentCar+1)%5;
}

void ControllerMenu::previousCar()
{
	currentCar = ((currentCar-1) % 5 + 5) % 5;
}

void ControllerMenu::nextCircuit()
{
	currentCircuit = (currentCircuit+1) % circuitList.size();
}

void ControllerMenu::previousCircuit()
{
	currentCircuit = ((currentCircuit - 1) % circuitList.size() + circuitList.size()) % circuitList.size();
}

/*
* Lit les diff�rents fichier de leaderboard, car et map et stock les donn�es
*/
void ControllerMenu::updateData()
{
	std::ifstream sCar;
	sCar.open("carList.car");
	
	

	for (int i = 0; i < 5; i++) {
		carList[i] = new ModelAuto();
		sCar >> *carList[i];
	}

	//lire fichier circuits et mettre dans le tableau

	std::string path("maps/");
    std::string ext(".gamemap");
    for (auto &p : fs::recursive_directory_iterator(path)) {
        if (p.path().extension() == ext){
			circuitList.push_back(new ModelCircuit(p.path().parent_path().filename().string()));
			std::ifstream sCircuit;
			sCircuit.open(p.path().string());
			sCircuit >> *circuitList[circuitList.size() - 1];
		}
    }
	
	currentCar = 0;
	currentCircuit = 0;
}

/*
* Affiche le leaderboard
* Deprecated une fois qu'on a un GUI
*/
std::string ControllerMenu::printLeaderboard()
{
	Leaderboard leaderboard(circuitList[currentCircuit]->getName());
	std::string retour;
	unsigned long temps = 0;



	for (int i = 0; i < leaderboard.getLength(); i++) {
		temps = leaderboard.getTime(i).time;
		std::stringstream buffer;
		buffer << temps / 60000 << ":" << std::setw(2) << std::setfill('0') << (temps / 1000) % 60 << ":" << std::setw(2) << std::setfill('0') << (temps / 10) % 100;
		retour += leaderboard.getTime(i).name + "..............." + buffer.str() + "\n";
	}

	return retour;
}

/*
* Helper method pour d�placer le curseur sur le command prompt
*/
void ControllerMenu::gotoXY(int x, int y)
{
	COORD scrn;
	HANDLE houtput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = 2 * x;
	scrn.Y = y;
	SetConsoleCursorPosition(houtput, scrn);
}

/*
* Thread du menu, lit en permanance la manette et g�re la s�lection des options
*/
void ControllerMenu::menuThread(ControllerMenu* controller)
{
	if (controller->isConnected) {
		controller->j_msg_send["G"] = 1;      // Cr�ation du message � envoyer
		controller->j_msg_send["1"] = 1;
		controller->j_msg_send["2"] = 1;
		controller->j_msg_send["3"] = 1;
		controller->j_msg_send["S"] = 0;
	}

	//Pour contr�le manette
	int previousBtn3 = 0;
	int previousBtn4 = 0;
	int previousY = 0;
	int previousX = 0;
	int joyX = 0;


	//Pour contr�le clavier seulement
	SHORT up = 0;
	SHORT down = 0;
	SHORT previousUp = 0;
	SHORT previousDown = 0;
	SHORT l = 0;
	SHORT r = 0;
	SHORT previousL = 0;
	SHORT previousR = 0;
	SHORT enter = 0;

	

	controller->gotoXY(0, 15);

	Sleep(100);

	while (1) {
		if (controller->isConnected) {
			previousY = controller->joyStickY;
			previousX = joyX;
			previousBtn3 = controller->bouton3;
			previousBtn4 = controller->bouton4;

			if (!SerialCommunication::SendToSerial(controller->arduino, controller->j_msg_send)) {    //Envoie au Arduino
				std::cerr << "Erreur lors de l'envoie du message. " << std::endl;
			}

			controller->j_msg_rcv.clear();
			if (!SerialCommunication::RcvFromSerial(controller->arduino, controller->raw_msg)) {
				std::cerr << "Erreur lors de la r�ception du message. " << std::endl;
			}



			if (controller->raw_msg.size() > 0) {
				controller->j_msg_rcv = json::parse(controller->raw_msg);       // Transfert du message en json
				if (controller->j_msg_rcv.contains("Y"))
					controller->joyStickY = controller->j_msg_rcv["Y"];
				if (controller->j_msg_rcv.contains("X"))
					joyX = controller->j_msg_rcv["X"];
				if (controller->j_msg_rcv.contains("3"))
					controller->bouton3 = controller->j_msg_rcv["3"];
				if (controller->j_msg_rcv.contains("4"))
					controller->bouton4 = controller->j_msg_rcv["4"];
			}


			if (joyX > 65)
				joyX = 1;
			else if (joyX < -65)
				joyX = -1;
			else
				joyX = 0;

			//Pour d�bogage, afficher les valeurs du JSON
			//std::cout << controller->j_msg_rcv << std::endl;
		}


			//Cont�le au clavier
			previousUp = up;
			previousDown = down;
			previousL = l;
			previousR = r;
			up = GetKeyState(VK_UP);
			down = GetKeyState(VK_DOWN);
			l = GetKeyState(VK_LEFT);
			r = GetKeyState(VK_RIGHT);
			enter = GetKeyState(VK_RETURN);



			if ((controller->bouton3 == 1 && previousBtn3 == 0) || enter < 0) {

				for (QPushButton* btn : controller->menuWindow->buttons) {
					btn->setFlat(false);
				}
				break;
			}
			else if (controller->optionSelected == 1 && ((controller->joyStickY == -1 && previousY != -1) ||(down < 0 && previousDown >= 0))) {
				controller->optionSelected++;
			}
			else if (controller->optionSelected == 2) {
				if ((controller->joyStickY == 1 && previousY != 1) || (up < 0 && previousUp >= 0)) {
					controller->optionSelected--;
				}
				else if ((joyX == 1 && previousX != 1) || (l < 0 && previousL >= 0)) {
					controller->optionSelected = 5;
				}
				else if ((joyX == -1 && previousX != -1) || (r < 0 && previousR >= 0)) {
					controller->optionSelected = 4;
				}
			}
			else if (controller->optionSelected == 3 && ((joyX == 1 && previousX != 1) || (l < 0 && previousL >= 0))) {
				controller->optionSelected = 4;
			}
			else if (controller->optionSelected == 4) {
				if ((joyX == 1 && previousX != 1) || (l < 0 && previousL >= 0)) {
					controller->optionSelected = 2;
				}
				else if ((joyX == -1 && previousX != -1) || (r < 0 && previousR >= 0)) {
					controller->optionSelected = 3;
				}
			}
			else if (controller->optionSelected == 5) {
				if ((joyX == 1 && previousX != 1) || (l < 0 && previousL >= 0))
					controller->optionSelected = 6;
				else if ((joyX == -1 && previousX != -1) || (r < 0 && previousR >= 0))
					controller->optionSelected = 2;
			}
			else if (controller->optionSelected == 6 && ((joyX == -1 && previousX != -1) || (r < 0 && previousR >= 0))) {
				controller->optionSelected = 5;
			}
			

			controller->gotoXY(0, controller->optionSelected + 14);
			for (QPushButton* btn : controller->menuWindow->buttons) {
				btn->setFlat(false);
			}
			controller->menuWindow->buttons[controller->optionSelected - 1]->setFlat(true);



			Sleep(30);
	}
	
}


/*
* Thread du menu, lit en permanance la manette et g�re la s�lection des options
*/
void ControllerMenu::settingsThread(ControllerMenu* controller)
{
	if (controller->isConnected) {
		controller->j_msg_send["G"] = 1;      // Cr�ation du message � envoyer
		controller->j_msg_send["1"] = 1;
		controller->j_msg_send["2"] = 1;
		controller->j_msg_send["3"] = 1;
		controller->j_msg_send["S"] = 0;

	}
		//Pour contr�le manette
		int previousBtn3 = 0;
		int previousBtn4 = 0;
		int previousX = 0;
		int joyX = 0;
	

	//Pour contr�le clavier seulement
	SHORT l = 0;
	SHORT r = 0;
	SHORT previousL = 0;
	SHORT previousR = 0;
	SHORT enter = 0;



	//controller->gotoXY(0, 15);

	Sleep(100);

	while (1) {
		if (controller->isConnected) {
			previousX = joyX;
			previousBtn3 = controller->bouton3;
			previousBtn4 = controller->bouton4;

			if (!SerialCommunication::SendToSerial(controller->arduino, controller->j_msg_send)) {    //Envoie au Arduino
				std::cerr << "Erreur lors de l'envoie du message. " << std::endl;
			}

			controller->j_msg_rcv.clear();
			if (!SerialCommunication::RcvFromSerial(controller->arduino, controller->raw_msg)) {
				std::cerr << "Erreur lors de la r�ception du message. " << std::endl;
			}



			if (controller->raw_msg.size() > 0) {
				controller->j_msg_rcv = json::parse(controller->raw_msg);       // Transfert du message en json
				if (controller->j_msg_rcv.contains("X"))
					joyX = controller->j_msg_rcv["X"];
				if (controller->j_msg_rcv.contains("3"))
					controller->bouton3 = controller->j_msg_rcv["3"];
				if (controller->j_msg_rcv.contains("4"))
					controller->bouton4 = controller->j_msg_rcv["4"];
			}

			if (joyX > 65)
				joyX = 1;
			else if (joyX < -65)
				joyX = -1;
			else
				joyX = 0;
		}

		//Pour d�bogage, afficher les valeurs du JSON
		//std::cout << controller->j_msg_rcv << std::endl;



			//Cont�le au clavier
		previousL = l;
		previousR = r;
		l = GetKeyState(VK_LEFT);
		r = GetKeyState(VK_RIGHT);
		enter = GetKeyState(VK_RETURN);

		if (l < 0)
			l = 1;
		else
			l = 0;

		if (r < 0)
			r = 1;
		else
			r = 0;

		if (enter < 0)
			enter = 1;
		else
			enter = 0;





		if (((joyX == -1 && previousX != -1) || (r ==1 && previousR == 0)) && controller->optionSelected < 2) {
			controller->optionSelected++;
			//controller->gotoXY(0, controller->optionSelected + 14);

			for (QPushButton* btn : controller->mainWindow->settingsWindow->buttons) {
				btn->setFlat(false);
			}
			controller->mainWindow->settingsWindow->buttons[controller->optionSelected - 1]->setFlat(true);

		}
		else if (((joyX == 1 && previousX != 1) || (l ==1 && previousL == 0)) && controller->optionSelected > 1) {
			controller->optionSelected--;
			//controller->gotoXY(0, controller->optionSelected + 14);
			
			for (QPushButton* btn : controller->mainWindow->settingsWindow->buttons) {
				btn->setFlat(false);
			}
			controller->mainWindow->settingsWindow->buttons[controller->optionSelected - 1]->setFlat(true);
		}
		else if ((controller->bouton3 == 1 && previousBtn3 == 0) || enter == 1) {

			for (QPushButton* btn : controller->menuWindow->buttons) {
				btn->setFlat(false);
			}
			break;
		}





		Sleep(30);
	}

}
