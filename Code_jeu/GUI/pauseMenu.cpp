#include "pauseMenu.h"


PauseMenu::PauseMenu(QWidget* parent)
{
	vLayout = new QVBoxLayout();

	resumeBtn = new QPushButton(tr("Continuer"));
	quitBtn = new QPushButton(tr("Quitter"));
	text = new QLabel(tr("Pause"));
	text->setAlignment(Qt::AlignCenter);

	vLayout->addWidget(text);
	vLayout->addWidget(resumeBtn);
	vLayout->addWidget(quitBtn);

	buttons[0] = resumeBtn;
	buttons[1] = quitBtn;

	setLayout(vLayout);
	setWindowTitle(tr("Paramètres"));
}