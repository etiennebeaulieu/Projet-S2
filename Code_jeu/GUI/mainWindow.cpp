#include "mainWindow.h"



MainWindow::MainWindow(QWidget* parent) {
	menuWindow = new MainMenu();
	courseWindow = new Course();
}


void MainWindow::showMenu() {
	courseWindow->hide();
	menuWindow->show();


}

void MainWindow::showCourse()
{
	menuWindow->hide();
	courseWindow->show();
}
