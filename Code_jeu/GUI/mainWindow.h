#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <qmainwindow.h>
#include <qwidget.h>
#include "mainMenu.h"
#include "course.h"
#include "pauseMenu.h"
#include "settingsMenu.h"
#include <qguiapplication.h>
#include <qscreen.h>


class MainWindow : public QMainWindow
{
	Q_OBJECT
public:
	MainWindow(QWidget* parent = nullptr);

	MainMenu* menuWindow;
	Course* courseWindow;
	PauseMenu* pauseWindow;
	SettingsMenu* settingsWindow;


public slots:
	void showMenu();
	void showCourse();
	void showPause();
	void showSettings();


};


#endif

