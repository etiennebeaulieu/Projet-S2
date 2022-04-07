#include "mainMenu.h"


MainMenu::MainMenu(QWidget* parent) {
	layout = new QGridLayout(parent);

	playBtn = new QPushButton(tr("Jouer"));
	settingsBtn = new QPushButton(tr("Paramètre"));
	nextCircuitBtn = new QPushButton(tr(">"));
	previousCircuitBtn = new QPushButton(tr("<"));
	nextCarBtn = new QPushButton(tr(">"));
	previousCarBtn = new QPushButton(tr("<"));

	leaderboardTitleLabel = new QLabel(tr("Classement"));
	leaderboardLabel = new QLabel();
	carStatsLabel = new QLabel();
	carNameLabel = new QLabel();
	carLabel = new QLabel();
	circuitNameLabel = new QLabel();
	circuitLabel = new QLabel();

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

	setLayout(layout);
	setWindowTitle(tr("Menu principal"));
}
