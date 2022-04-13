#include "settingsMenu.h"


SettingsMenu::SettingsMenu(QWidget* parent)
{
	vLayout = new QVBoxLayout();
	hLayout = new QHBoxLayout();

	joyBtn = new QPushButton(tr("Joystick"));
	accBtn = new QPushButton(tr("Gyroscope"));
	text = new QLabel(tr("Choix des controles"));

	vLayout->addWidget(text);
	vLayout->addLayout(hLayout);
	hLayout->addWidget(joyBtn);
	hLayout->addWidget(accBtn);

	hLayout->setContentsMargins(QMargins(10, 20, 10, 20));
	vLayout->setAlignment(Qt::AlignCenter);
	text->setAlignment(Qt::AlignCenter);
	text->setStyleSheet("font-size: 24pt; font-weight: bold");


	buttons[0] = joyBtn;
	buttons[1] = accBtn;

	QPalette p = QPalette();
	p.setBrush(QPalette::Button, Qt::red);
	for (QPushButton* btn : buttons) {
		btn->setPalette(p);
		btn->setAutoFillBackground(true);
		btn->setStyleSheet("font-size: 18pt; font-weight: bold; text-align: center");
	}

	setLayout(vLayout);
	setWindowTitle(tr("Parametres"));
}

void SettingsMenu::highlight(int indice)
{
	for (QPushButton* btn : buttons) {
		btn->setFlat(false);
	}
	buttons[indice]->setFlat(true);

}