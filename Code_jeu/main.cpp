#include "controllers.h"
#include <qthread.h>


int main(int argc, char** argv) {	
	ControllerMenu* controllerMenu = new ControllerMenu();

	controllerMenu->startApp(argc, argv);

	//std::thread mainThread(&ControllerMenu::startApp, argc, argv);

	//QThread* thread = QThread::create(&ControllerMenu::startApp, argc, argv);
	//thread->start();
	
	
	return 0;
	
}


