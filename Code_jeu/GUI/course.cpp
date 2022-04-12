#include "course.h"
#include <QRectF>


Course::Course(QWidget* parent) {
	layout = new QGridLayout(parent);

	times = new QLabel(tr("Chono:\nTour: 00:00:00\nDernier: 00:00:00\nMeilleur: 00:00:00"));

	
	viewRace = new QGraphicsView(&sceneRace);

	backgroundCourse = new QGraphicsPixmapItem();
	sceneRace.addItem(backgroundCourse);
	backgroundCourse->setPos(0, 0);
	backgroundCourse->setZValue(-0.1);


	car = new QGraphicsPixmapItem();
	sceneRace.addItem(car);
	car->setPos(0, 0);

	ghost = new QGraphicsPixmapItem();
	sceneRace.addItem(ghost);
	ghost->setPos(0, 0);

	
	layout->addWidget(times, 0, 0, Qt::AlignTop);
	layout->addWidget(viewRace, 0, 1);


	


	layout->setVerticalSpacing(0);
	layout->setHorizontalSpacing(0);
	layout->setContentsMargins(QMargins(0, 0, 0, 0));

	viewRace->setContentsMargins(QMargins(0, 0, 0, 0));

	layout->setColumnStretch(1, 2);


	
	


	setLayout(layout);
	setWindowTitle(tr("Course en cours"));
}

void Course::moveCar(float x, float y, float angle)
{
	QPixmap carImage = car->pixmap();
	car->setTransformOriginPoint((carImage.width()) / 2, (carImage.height()) / 2);
	car->setRotation(-angle+90);

	
	QPointF center = car->boundingRect().center();
	car->setPos(x-center.x(), y-center.y());
	
	
}

void Course::moveGhost(float x, float y, float angle)
{
	QPixmap carImage = ghost->pixmap();
	ghost->setTransformOriginPoint((carImage.width()) / 2, (carImage.height()) / 2);
	ghost->setRotation(-angle+90);


	QPointF center = ghost->boundingRect().center();
	ghost->setPos(x - center.x(), y - center.y());
	
}

void Course::updateTimer(unsigned long current, unsigned long best, unsigned long last)
{
	QString currentTime;
	QString bestTime;
	QString lastTime;
	std::stringstream bufferCurrent;
	std::stringstream bufferBest;
	std::stringstream bufferLast;
	
	bufferCurrent << current / 60000 << ":" << std::setw(2) << std::setfill('0') << (current / 1000) % 60 << ":" << std::setw(2) << std::setfill('0') << (current / 10) % 100;
	currentTime = QString::fromStdString(bufferCurrent.str());

	bufferBest << best / 60000 << ":" << std::setw(2) << std::setfill('0') << (best / 1000) % 60 << ":" << std::setw(2) << std::setfill('0') << (best / 10) % 100;
	bestTime = QString::fromStdString(bufferBest.str());

	bufferLast << last / 60000 << ":" << std::setw(2) << std::setfill('0') << (last / 1000) % 60 << ":" << std::setw(2) << std::setfill('0') << (last / 10) % 100;
	lastTime = QString::fromStdString(bufferLast.str());

	times->setText("Chrono\nTour:" + currentTime + "\nDernier:" + lastTime + "\nMeilleur:" + bestTime);


	
}
