#include "controller_menu.h"

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
	int option;
	std::cout << "Bienvenue sur SparkUS racing" << std::endl;
	std::cout << "CLASSEMENT\n" << printLeaderboard() << std::endl;
	std::cout << "VOITURE\nNom : "<<carList[currentCar]->getName()<< "\nVitesse :" << carList[currentCar]->getSpeed() << "\nVirage : " << carList[currentCar]->getHandling() << std::endl;
	std::cout << "\nCIRCUIT\nNom : " << circuitList[currentCircuit]->getName() << std::endl;
	std::cout << "1. Play\n2. Reglages\n3. Prochaine voiture\n4. Voiture precedente\n5. Prochain circuit\n6. Circuit precedent\n9. Quitter" << std::endl;
	std::cout << "Entrez le chiffre de l'option choisie" << std::endl;
	std::cin >> option;

	switch (option) {
	case 1:
		startGame();
		system("CLS");
		printMenu();
		break;
	case 2:
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
	case 9:
		exit(1);
		break;
	default:
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
	controllerCourse = new Controller_course(carList[currentCar], circuitList[currentCircuit]);
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
