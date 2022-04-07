#include "controllers.h"
#include "GUI/mainMenu.h"
#include <qapplication.h>

int main(int argc, char** argv) {

	//QApplication app(argc, argv);
	//QWidget* window = app.activeWindow();
	//window = new MainMenu();
	
	
	

	ControllerMenu* controllerMenu = new ControllerMenu();
	//window->show();
	//return app.exec();
	return 0;
}