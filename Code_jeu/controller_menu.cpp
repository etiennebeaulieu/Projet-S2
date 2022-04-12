#include "controllers.h"

ControllerMenu::ControllerMenu()
{
	// Initialisation du port de communication
	std::string com;
	std::cout << "Entrer le port de communication du Arduino: ";
	std::cin >> com;
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
		std::cerr << "Erreur lors de la réception du message. " << std::endl;
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
	
	
	
	QPalette p = QPalette();
	p.setBrush(QPalette::Button, Qt::red);
	for (QPushButton* btn : menuWindow->buttons) {
		btn->setPalette(p);
		btn->setAutoFillBackground(true);
	}
	

	QThread* thread = QThread::create([this]() {printMenu(); });
	thread->start();

	mainWindow->show();
	app->exec();
}

/*
* Affiche le menu et gère les options séléctionnées
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
	buffer << "Vitesse :" << carList[currentCar]->getSpeed() << "\nVirage : " << carList[currentCar]->getHandling();
	menuWindow->carStatsLabel->setText(QString::fromStdString(buffer.str()));
	menuWindow->circuitNameLabel->setText(QString::fromStdString(circuitList[currentCircuit]->getName()));
	QPixmap circuitImage = QPixmap(QString::fromStdString((string)"image/" + circuitList[currentCircuit]->getName() + ".png")).scaled(300, 300);
	menuWindow->circuitLabel->setPixmap(circuitImage);
	
	QPixmap carImage = QPixmap(QString::fromStdString((string)"image/" + carList[currentCar]->getName() + ".png")).scaled(300, 300);
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
* Ouvre la fenêtre des options
*/
void ControllerMenu::openSettings()
{
	QMetaObject::invokeMethod(mainWindow, "showSettings");
	//TODO Changer la page de settings pour fonctionner avec un thread et avec la manette
	int option;
	std::cout << "Ceci sont les reglages" << std::endl;
	std::cout << "Appuyer sur 9 pour retourner au menu" << std::endl;
	std::cin >> option;

	if (option == 9) {
		system("CLS");
		printMenu();
	}
	else {
		system("CLS");
		openSettings();
	}
}

/*
* Crée l'objet controller_course et commencer la course
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
* Lit les différents fichier de leaderboard, car et map et stock les données
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
* Helper method pour déplacer le curseur sur le command prompt
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
* Thread du menu, lit en permanance la manette et gère la sélection des options
*/
void ControllerMenu::menuThread(ControllerMenu* controller)
{
	controller->j_msg_send["G"] = 1;      // Création du message à envoyer
	controller->j_msg_send["1"] = 1;
	controller->j_msg_send["2"] = 1;
	controller->j_msg_send["3"] = 1;
	controller->j_msg_send["S"] = 0;
	

	//Pour contrôle manette
	int previousBtn3 = 0;
	int previousBtn4 = 0;
	int previousY = 0;


	//Pour contrôle clavier seulement
	SHORT up = 0;
	SHORT down = 0;
	SHORT previousUp = 0;
	SHORT previousDown = 0;
	SHORT enter = 0;

	

	controller->gotoXY(0, 15);

	Sleep(100);

	while (1) {
		previousY = controller->joyStickY;
		previousBtn3 = controller->bouton3;
		previousBtn4 = controller->bouton4;

		if (!SerialCommunication::SendToSerial(controller->arduino, controller->j_msg_send)) {    //Envoie au Arduino
			std::cerr << "Erreur lors de l'envoie du message. " << std::endl;
		}

		controller->j_msg_rcv.clear();
		if (!SerialCommunication::RcvFromSerial(controller->arduino, controller->raw_msg)) {
			std::cerr << "Erreur lors de la réception du message. " << std::endl;
		}
		


		if (controller->raw_msg.size() > 0) {
			controller->j_msg_rcv = json::parse(controller->raw_msg);       // Transfert du message en json
			if (controller->j_msg_rcv.contains("Y"))
				controller->joyStickY = controller->j_msg_rcv["Y"];
			if (controller->j_msg_rcv.contains("3"))
				controller->bouton3 = controller->j_msg_rcv["3"];
			if (controller->j_msg_rcv.contains("4"))
				controller->bouton4 = controller->j_msg_rcv["4"];
		}


		//Pour débogage, afficher les valeurs du JSON
		//std::cout << controller->j_msg_rcv << std::endl;



			//Contôle au clavier
			previousUp = up;
			previousDown = down;
			up = GetKeyState(VK_UP);
			down = GetKeyState(VK_DOWN);
			enter = GetKeyState(VK_RETURN);




			
			if (((controller->joyStickY == -1 && previousY != -1) || (down < 0 && previousDown >= 0)) && controller->optionSelected < 7) {
				controller->optionSelected++;
				controller->gotoXY(0, controller->optionSelected + 14);
				
				for (QPushButton* btn : controller->menuWindow->buttons) {
					btn->setFlat(false);
				}
				controller->menuWindow->buttons[controller->optionSelected-1]->setFlat(true);
				
			}
			else if (((controller->joyStickY == 1 && previousY != 1) || (up < 0 && previousUp >= 0)) && controller->optionSelected > 1) {
				controller->optionSelected--;
				controller->gotoXY(0, controller->optionSelected + 14);
				for (QPushButton* btn : controller->menuWindow->buttons) {
					btn->setFlat(false);
				}
				controller->menuWindow->buttons[controller->optionSelected - 1]->setFlat(true);
			}
			else if ((controller->bouton3 == 1 && previousBtn3 == 0) || enter < 0) {
				
				for (QPushButton* btn : controller->menuWindow->buttons) {
					btn->setFlat(false);
				}
				break;
			}
			
			



			Sleep(30);
	}
	
}
