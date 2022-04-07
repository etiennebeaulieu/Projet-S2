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

private:
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

};


#endif