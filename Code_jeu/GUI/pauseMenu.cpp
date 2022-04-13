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

	QPalette p = QPalette();
	p.setBrush(QPalette::Button, Qt::red);
	for (QPushButton* btn : buttons) {
		btn->setPalette(p);
		btn->setAutoFillBackground(true);
	}

	setLayout(vLayout);
	setWindowTitle(tr("Paramètres"));
}

void PauseMenu::highlight(int indice)
{
	for (QPushButton* btn : buttons) {
		btn->setFlat(false);
	}
	buttons[indice]->setFlat(true);

}