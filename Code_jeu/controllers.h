#ifndef CONTROLLERS_H
#define CONTROLLERS_H
#include <Windows.h>
#include <thread>
#include <iostream>
#include <sstream>
#include <future>
#include <qapplication.h>
#include "model_auto.h"
#include "model_circuit.h"
#include "position.h"
#include "timer.h"
#include "leaderboard.h"
#include "serial_communication.h"
#include "SerialPort.hpp"
#include <fstream>
#include <filesystem>
#include <vector>
#include <qthread.h>
#include <qmutex.h>
#include <qobject.h>
#include "course_record.h"
#include "GUI/mainMenu.h"
#include "GUI/course.h"
#include "GUI/mainWindow.h"

using json = nlohmann::json;
#define BAUD 115200

class Controller_course;

namespace fs = std::filesystem;


class ControllerMenu {

public:
	ControllerMenu();
	~ControllerMenu();

	void startApp(int argc, char** argv);

	void printMenu();

	void openSettings();
	void startGame();
	void nextCar();
	void previousCar();
	void nextCircuit();
	void previousCircuit();
	void updateData();
	std::string printLeaderboard();

	void gotoXY(int x, int y);

	static void menuThread(ControllerMenu* controller);
	static void settingsThread(ControllerMenu* controller);



	SerialPort* arduino;
	std::string raw_msg;
	QApplication* app;
	MainWindow* mainWindow;
	MainMenu* menuWindow;
	Course* courseWindow;
	QMutex* mutex;
	int argc;
	char** argv;
	int sorteControle = 0; //0 pour joystick, 1 pour accéléromère, autre pour clavier
	bool isConnected;

private:
	Leaderboard leaderboard;
	ModelAuto* carList[5];
	std::vector<ModelCircuit*> circuitList;
	int currentCar;
	int currentCircuit;
	int optionSelected;
	Controller_course* controllerCourse;
	



	// Structure de donnees JSON pour reception
	int bouton1 = 0;
	int bouton2 = 0;
	int bouton3 = 0;
	int bouton4 = 0;
	float joyStickX = 0;
	int joyStickY = 0;
	float acc_Value = 0;
	// Structure de donnees pour Envoie JSON
	int led_state_GREEN = 0;
	int led_state_RED1 = 0;
	int led_state_RED2 = 0;
	int led_state_RED3 = 0;
	long segment_Value = 0;
	int moteur_vibrant = 0;

	json j_msg_send, j_msg_rcv;



};


class Controller_course {

public:
	Controller_course(ModelAuto* pCar, ModelCircuit* pCircuit, ControllerMenu* pControllerMenu);
	~Controller_course();


	void initiateGUI();
	void setAuto(ModelAuto pCar);
	ModelAuto getAuto();
	void setCircuit(ModelCircuit pCircuit);
	ModelCircuit getCircuit();

	void startRace();
	bool move(float pAngle, int pMovement);

	void updateScreenConsole();
	void updateScreenGUI();

	void gotoXY(int x, int y);
	void demoConsole();

	void saveLeaderboard();

	void endRace();


	static void menuThread(Controller_course* controller);
	static void courseThread(Controller_course* controller);

	SerialPort* arduino;
	std::string raw_msg;
	Course* courseWindow;
private:
	ModelAuto car;
	ModelCircuit circuit;
	ControllerMenu* menuControleur;
	int optionSelected;
	unsigned long time;
	Position ghostPos;
	Timer timer;
	unsigned long lastTime;

	Leaderboard leaderboard;
	CourseRecord ghostCourseRecord;
	CourseRecord currentCourseRecord;
	



	// Structure de donnees JSON pour reception
	int bouton1 = 0;
	int bouton2 = 0;
	int bouton3 = 0;
	int bouton4 = 0;
	float joyStickX = 0;
	int joyStickY = 0;
	float acc_Value = 0;
	// Structure de donnees pour Envoie JSON
	int led_state_GREEN = 0;
	int led_state_RED1 = 0;
	int led_state_RED2 = 0;
	int led_state_RED3 = 0;
	long segment_Value = 0;
	int moteur_vibrant = 0;

	json j_msg_send, j_msg_rcv;
};

#endif
