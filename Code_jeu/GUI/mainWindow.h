#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <qmainwindow.h>
#include <qwidget.h>
#include "mainMenu.h"
#include "course.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT
public:
	MainWindow(QWidget* parent = nullptr);

	MainMenu* menuWindow;
	Course* courseWindow;

public slots:
	void showMenu();
	void showCourse();


};


#endif

