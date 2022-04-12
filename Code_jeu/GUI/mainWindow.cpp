#include "mainWindow.h"



MainWindow::MainWindow(QWidget* parent) {
	menuWindow = new MainMenu();
	courseWindow = new Course();
	pauseWindow = new PauseMenu();
	settingsWindow = new SettingsMenu();
}


void MainWindow::showMenu() {
	courseWindow->hide();
	menuWindow->showFullScreen();
	pauseWindow->hide();
	settingsWindow->hide();

}

void MainWindow::showCourse()
{
	//courseWindow = new Course();
	menuWindow->hide();
	courseWindow->showFullScreen();
	pauseWindow->hide();
	settingsWindow->hide();
}

void MainWindow::showPause()
{
	pauseWindow->show();
	
}

void MainWindow::showSettings()
{
	settingsWindow->show();
}
