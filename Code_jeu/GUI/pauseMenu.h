#ifndef PAUSE_MENU_H
#define PAUSE_MENU_H

#include <qwidget.h>
#include <qpushbutton.h>
#include <qboxlayout.h>
#include <qlabel.h>



class PauseMenu : public QWidget
{
	Q_OBJECT

public:
	PauseMenu(QWidget* parent = nullptr);
	QPushButton* buttons[2];

	QVBoxLayout* vLayout;

	QPushButton* resumeBtn;
	QPushButton* quitBtn;
	QLabel* text;
};


#endif
