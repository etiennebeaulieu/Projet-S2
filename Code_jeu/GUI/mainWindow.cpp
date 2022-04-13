#include "mainWindow.h"



MainWindow::MainWindow(QWidget* parent) {
	menuWindow = new MainMenu();
	courseWindow = new Course();
	pauseWindow = new PauseMenu();
	settingsWindow = new SettingsMenu();

	courseWindow->setStyleSheet("background-color: green");
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
	pauseWindow->resize(100, 100);
	QScreen* screen = QGuiApplication::primaryScreen();
	QRect  screenGeometry = screen->geometry();
	int height = screenGeometry.height();
	int width = screenGeometry.width();
	int x = (width - pauseWindow->width()) / 2.0;
	int y = (height - pauseWindow->height()) / 2.0;
	pauseWindow->setGeometry(x, y, pauseWindow->width(), pauseWindow->height());
	pauseWindow->show();
	
}

void MainWindow::showSettings()
{
	settingsWindow->resize(100, 100);
	QScreen* screen = QGuiApplication::primaryScreen();
	QRect  screenGeometry = screen->geometry();
	int height = screenGeometry.height();
	int width = screenGeometry.width();
	int x = (width - 100) / 2.0;
	int y = (height - 100) / 2.0;
	settingsWindow->setGeometry(x, y, 100, 100);
	settingsWindow->show();
}
