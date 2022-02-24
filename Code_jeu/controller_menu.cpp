#include "controller_menu.h"

ControllerMenu::ControllerMenu()
{
	updateData();

	
	printMenu();
}

void ControllerMenu::printMenu()
{
	int option;
	cout << "Bienvenue sur SparkUS racing" << endl;
	cout << "CLASSEMENT\n" << printLeaderboard() << endl;
	cout << "VOITURE\nNom : "<<carList[currentCar].getName()<< "\nVitesse :" << carList[currentCar].getSpeed() << "\nVirage : " << carList[currentCar].getHandling() << endl;
	cout << "\nCIRCUIT\nNom : " << circuitList[currentCircuit].getName() << endl;
	cout << "1. Play\n2. R�glages\n3. Prochaine voiture\n4. Voiture pr�c�dente\n5. Prochain circuit\n6. Circuit pr�c�dent" << endl;
	cout << "Entrez le chiffre de l'option choisie" << endl;
	cin >> option;

	switch (option) {
	case 1:
		startGame();
		break;
	case 2:
		openSettings();
		break;
	case 3:
		nextCar();
		printMenu();
		break;
	case 4:
		previousCar();
		printMenu();
		break;
	case 5:
		nextCircuit();
		printMenu();
		break;
	case 6:
		previousCircuit();
		printMenu();
		break;
	default:
		printMenu();
		break;
	}

	
	
}

void ControllerMenu::openSettings()
{
	int option;
	cout << "Ceci sont les r�glages" << endl;
	cout << "Appuyer sur 9 pour retourner au menu" << endl;
	cin >> option;

	if (option == 9)
		printMenu();
}

void ControllerMenu::startGame()
{
}

void ControllerMenu::nextCar()
{
	currentCar = (currentCar++)%5;
}

void ControllerMenu::previousCar()
{
	currentCar = (currentCar--) % 5;
}

void ControllerMenu::nextCircuit()
{
	currentCar = (currentCircuit++) % 5;
}

void ControllerMenu::previousCircuit()
{
	currentCar = (currentCircuit--) % 5;
}

void ControllerMenu::updateData()
{
	ifstream sLeaderboard;
	sLeaderboard.open("leaderboard.lb");

	ifstream sCar;
	sCar.open("carList.car");
	//lire fichier leaderboard et mettre dans le tableau
	for (BestTime bestTime : leaderboard)
	{
		sLeaderboard >> bestTime;
	}

	//lire fichier autos et mettre dans le tableau
	for (Model_auto car : carList)
	{
		sCar >> car;
	}

	//lire fichier circuits et mettre dans le tableau
}

string ControllerMenu::printLeaderboard()
{
	string retour;
	for (BestTime entry : leaderboard)
	{
		retour += entry.name + "..............." + entry.time + "\n";
	}
	return retour;
}
