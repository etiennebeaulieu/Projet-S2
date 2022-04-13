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

	text->setStyleSheet("font-size: 24pt; font-weight: bold");
	vLayout->setContentsMargins(QMargins(10, 20, 10, 20));
	vLayout->setAlignment(Qt::AlignCenter);
	vLayout->setSpacing(20);

	buttons[0] = resumeBtn;
	buttons[1] = quitBtn;

	QPalette p = QPalette();
	p.setBrush(QPalette::Button, Qt::red);
	for (QPushButton* btn : buttons) {
		btn->setPalette(p);
		btn->setAutoFillBackground(true);
		btn->setStyleSheet("font-size: 18pt; font-weight: bold; text-align: center");
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