#ifndef SETTINGS_MENU_H
#define SETTINGS_MENU_H

#include <qwidget.h>
#include <qpushbutton.h>
#include <qboxlayout.h>
#include <qlabel.h>



class SettingsMenu : public QWidget
{
	Q_OBJECT

public:
	SettingsMenu(QWidget* parent = nullptr);
	QPushButton* buttons[2];

	QHBoxLayout* hLayout;
	QVBoxLayout* vLayout;

	QPushButton* joyBtn;
	QPushButton* accBtn;
	QLabel* text;


};


#endif
