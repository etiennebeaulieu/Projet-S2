#include "mainMenu.h"


MainMenu::MainMenu(QWidget* parent) {
	
	layout = new QGridLayout(parent);

	playBtn = new QPushButton(tr("Jouer"));
	settingsBtn = new QPushButton(tr("Parametres"));
	nextCircuitBtn = new QPushButton(tr(">"));
	previousCircuitBtn = new QPushButton(tr("<"));
	nextCarBtn = new QPushButton(tr(">"));
	previousCarBtn = new QPushButton(tr("<"));

	buttons[0] = playBtn;
	buttons[1] = settingsBtn;
	buttons[2] = nextCarBtn;
	buttons[3] = previousCarBtn;
	buttons[4] = nextCircuitBtn;
	buttons[5] = previousCircuitBtn;

	QPalette p = QPalette();
	p.setBrush(QPalette::Button, Qt::red);
	for (QPushButton* btn : buttons) {
		btn->setPalette(p);
		btn->setAutoFillBackground(true);
		btn->setStyleSheet("font-size: 20pt; font-weight: bold");
	}


	leaderboardTitleLabel = new QLabel(tr("Classement"));
	leaderboardTitleLabel->setAlignment(Qt::AlignHCenter | Qt::AlignBottom);
	leaderboardLabel = new QLabel();
	carStatsLabel = new QLabel();
	carStatsLabel->setAlignment(Qt::AlignCenter);
	carNameLabel = new QLabel();
	carNameLabel->setAlignment(Qt::AlignCenter);
	carLabel = new QLabel();
	circuitNameLabel = new QLabel();
	circuitNameLabel->setAlignment(Qt::AlignCenter);
	circuitLabel = new QLabel();
	


	
	leaderboardTitleLabel->setStyleSheet("font-size: 36pt; font-weight: bold; bottom: 10px");
	leaderboardLabel->setStyleSheet("font-size: 28pt");

	carNameLabel->setStyleSheet("font-size: 20pt");
	circuitNameLabel->setStyleSheet("font-size: 20pt");
	carStatsLabel->setStyleSheet("font-size: 20pt");


	carLabel->setStyleSheet("min-width: 500; max-width: 500; min-height: 500; max-height: 500; border-width: 5px; border-style: solid; border-color: red; border-radius: 5px");
	circuitLabel->setStyleSheet("min-width: 500; max-width: 500; min-height: 500; max-height: 500; border-width: 5px; border-style: solid; border-color: red; border-radius: 5px");
	circuitLabel->setAlignment(Qt::AlignCenter);
	carLabel->setAlignment(Qt::AlignCenter);

	layout->setAlignment(Qt::AlignCenter);
	layout->setContentsMargins(QMargins(10, 10, 10, 100));



	layout->setSpacing(30);


	layout->addWidget(playBtn, 2, 3, 1, 1);
	layout->addWidget(settingsBtn, 3, 3, 1, 1);
	layout->addWidget(nextCircuitBtn, 3, 2, 1, 1);
	layout->addWidget(previousCircuitBtn, 3, 0, 1, 1);
	layout->addWidget(nextCarBtn, 3, 6, 1, 1);
	layout->addWidget(previousCarBtn, 3, 4, 1, 1);

	layout->addWidget(leaderboardTitleLabel, 0, 3, 1, 1);
	layout->addWidget(leaderboardLabel, 1, 3, 1, 1);
	layout->addWidget(carStatsLabel, 2, 4, 1, 3);
	layout->addWidget(carNameLabel, 3, 5, 1, 1);
	layout->addWidget(carLabel, 1, 4, 1, 3);
	layout->addWidget(circuitNameLabel, 3, 1, 1, 1);
	layout->addWidget(circuitLabel, 1, 0, 1, 3);

	layout->setColumnMinimumWidth(3, 200);
	layout->setRowStretch(1, 2);

	setLayout(layout);
	setWindowTitle(tr("Menu principal"));
}

void MainMenu::setColor(int indice, const char* color)
{
	buttons[indice]->setStyleSheet(color);
}
