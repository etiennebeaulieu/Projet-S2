#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include <qwidget.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qgridlayout.h>
#include <qmainwindow.h>


class MainMenu : public QWidget
{
	Q_OBJECT

public:
	MainMenu(QWidget* parent = nullptr);
	QPushButton*  buttons[6];

	QGridLayout* layout;

	QPushButton* playBtn;
	QPushButton* settingsBtn;
	QPushButton* nextCircuitBtn;
	QPushButton* previousCircuitBtn;
	QPushButton* nextCarBtn;
	QPushButton* previousCarBtn;

	QLabel* leaderboardTitleLabel;
	QLabel* leaderboardLabel;
	QLabel* circuitNameLabel;
	QLabel* circuitLabel;
	QLabel* carStatsLabel;
	QLabel* carNameLabel;
	QLabel* carLabel;

	void setColor(int indice, const char* color);
};


#endif