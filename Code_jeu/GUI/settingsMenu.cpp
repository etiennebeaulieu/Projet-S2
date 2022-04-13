#include "settingsMenu.h"


SettingsMenu::SettingsMenu(QWidget* parent)
{
	vLayout = new QVBoxLayout();
	hLayout = new QHBoxLayout();

	joyBtn = new QPushButton(tr("Joystick"));
	accBtn = new QPushButton(tr("Gyroscope"));
	text = new QLabel(tr("Choix de contrôles"));

	vLayout->addWidget(text);
	vLayout->addLayout(hLayout);
	hLayout->addWidget(joyBtn);
	hLayout->addWidget(accBtn);

	buttons[0] = joyBtn;
	buttons[1] = accBtn;

	QPalette p = QPalette();
	p.setBrush(QPalette::Button, Qt::red);
	for (QPushButton* btn : buttons) {
		btn->setPalette(p);
		btn->setAutoFillBackground(true);
	}

	setLayout(vLayout);
	setWindowTitle(tr("Paramètres"));
}

void SettingsMenu::highlight(int indice)
{
	for (QPushButton* btn : buttons) {
		btn->setFlat(false);
	}
	buttons[indice]->setFlat(true);

}