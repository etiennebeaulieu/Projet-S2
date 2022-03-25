#include "controllers.h"

ControllerMenu::ControllerMenu()
{
	
	updateData();

	
	printMenu();
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

void ControllerMenu::printMenu()
{
	//int option;
	std::cout << "Bienvenue sur SparkUS racing" << std::endl;
	std::cout << "CLASSEMENT\n" << printLeaderboard() << std::endl;
	std::cout << "VOITURE\nNom : "<<carList[currentCar]->getName()<< "\nVitesse :" << carList[currentCar]->getSpeed() << "\nVirage : " << carList[currentCar]->getHandling() << std::endl;
	std::cout << "\nCIRCUIT\nNom : " << circuitList[currentCircuit]->getName() << std::endl;
	std::cout << "1. Play\n2. Reglages\n3. Prochaine voiture\n4. Voiture precedente\n5. Prochain circuit\n6. Circuit precedent\n7. Quitter" << std::endl;
	//std::cout << "Entrez le chiffre de l'option choisie" << std::endl;
	//std::cin >> option;


	
	std::thread menu(&ControllerMenu::menuThread, this);
	menu.join();


	switch (optionSelected) {
	case 1:
		optionSelected = 0;
		startGame();
		system("CLS");
		printMenu();
		break;
	case 2:
		optionSelected = 0;
		system("CLS");
		openSettings();
		break;
	case 3:
		optionSelected = 0;
		nextCar();
		system("CLS");
		printMenu();
		break;
	case 4:
		optionSelected = 0;
		previousCar();
		system("CLS");
		printMenu();
		break;
	case 5:
		optionSelected = 0;
		nextCircuit();
		system("CLS");
		printMenu();
		break;
	case 6:
		optionSelected = 0;
		previousCircuit();
		system("CLS");
		printMenu();
		break;
	case 7:
		optionSelected = 0;
		exit(1);
		break;
	default:
		optionSelected = 0;
		system("CLS");
		printMenu();
		break;
	}

	
	
}

void ControllerMenu::openSettings()
{
	int option;
	std::cout << "Ceci sont les reglages" << std::endl;
	std::cout << "Appuyer sur 9 pour retourner au menu" << std::endl;
	std::cin >> option;

	if (option == 9) {
		system("CLS");
		printMenu();
	}
		
}

void ControllerMenu::startGame()
{
	system("CLS");
	controllerCourse = new Controller_course(carList[currentCar], circuitList[currentCircuit], this);
	controllerCourse->startRace();
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

void ControllerMenu::updateData()
{
	std::ifstream sLeaderboard;
	sLeaderboard.open("leaderboard.lb");

	std::ifstream sCar;
	sCar.open("carList.car");
	//lire fichier leaderboard et mettre dans le tableau
	for (int i = 0; i < 5; i++)
	{
		sLeaderboard >> leaderboard[i];
	}

	for (int i = 0; i < 5; i++) {
		carList[i] = new ModelAuto();
		sCar >> *carList[i];
	}

	//lire fichier circuits et mettre dans le tableau

	std::string path("maps/");
    std::string ext(".gamemap");
    for (auto &p : fs::recursive_directory_iterator(path)) {
        if (p.path().extension() == ext){
			circuitList.push_back(new ModelCircuit(p.path().filename().string()));
			std::ifstream sCircuit;
			sCircuit.open(p.path().string());
			circuitList[circuitList.size() - 1] = new ModelCircuit();
			sCircuit >> *circuitList[circuitList.size() - 1];
		}
    }
	
	currentCar = 0;
	currentCircuit = 0;
}

std::string ControllerMenu::printLeaderboard()
{
	std::string retour;
	for (BestTime entry : leaderboard)
	{
		retour += entry.name + "..............." + entry.time + "\n";
	}
	return retour;
}

void ControllerMenu::gotoXY(int x, int y)
{
	COORD scrn;
	HANDLE houtput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = 2 * x;
	scrn.Y = y;
	SetConsoleCursorPosition(houtput, scrn);
}

void ControllerMenu::menuThread(ControllerMenu* controller)
{
	bool btn1 = 0;	//Avant gauche
	bool btn2 = 0;	//Avant droit
	bool btn3 = 0;	//Gachette gauche
	bool btn4 = 0;	//Gacehtte droite
	float x = 0;	//Joystick axe X
	int y = 0;		//Joystick axe y
	float acc = 0;	//Angle acceleromètre
	int optionSelected = 1;		//Bouton surligné dans le menu
	//0 = Resume
	//1 = Options
	//2 = Quit

	int previousBtn1 = 0;
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
		//TODO Lire JSON Arduino


		//Contôle au clavier
		previousUp = up;
		previousDown = down;

		up = GetKeyState(VK_UP);
		down = GetKeyState(VK_DOWN);
		enter = GetKeyState(VK_RETURN);


		


		if (((y == -1 && previousY == 0) || (down < 0 && previousDown >= 0)) && optionSelected < 7) {
			optionSelected++;
			controller->gotoXY(0, optionSelected+14);
		}
		else if (((y == 1 && previousY == 0) || (up < 0 && previousUp >= 0)) && optionSelected > 1) {
			optionSelected--;
			controller->gotoXY(0, optionSelected+14);
		}
		else if ((btn1 == 1 && previousBtn1 == 0) || enter < 0) {
			controller->optionSelected = optionSelected;
			break;
		}



		Sleep(30);
	}
}
