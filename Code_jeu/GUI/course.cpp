#include "course.h"
#include <QRectF>


Course::Course(QWidget* parent) {
	layout = new QGridLayout(parent);

	vBox = new QVBoxLayout();

	times = new QLabel(tr("Chono:\nTour: 0:00:00\nDernier: 0:00:00\nMeilleur: 0:00:00"));

	hint = new QLabel();
	QPixmap hintImage = QPixmap(QString::fromStdString("image/hint_course.png"));
	hintImage.scaledToHeight(100);
	hint->setPixmap(hintImage);

	

	vBox->addWidget(times);
	vBox->addWidget(hint);

	vBox->setSpacing(80);
	
	viewRace = new QGraphicsView(&sceneRace);

	backgroundCourse = new QGraphicsPixmapItem();
	sceneRace.addItem(backgroundCourse);
	backgroundCourse->setPos(0, 0);
	//backgroundCourse->setZValue(-0.1);


	car = new QGraphicsPixmapItem();
	sceneRace.addItem(car);
	car->setPos(0, 0);

	ghost = new QGraphicsPixmapItem();
	sceneRace.addItem(ghost);
	ghost->setPos(0, 0);

	
	layout->addLayout(vBox, 0, 0, Qt::AlignCenter);
	layout->addWidget(viewRace, 0, 1);


	viewRace->setStyleSheet("min-width: 950; max-width:950; min-height: 950; max-height: 950");
	times->setStyleSheet("font-size: 28pt; font-weight: bold");



	viewRace->setContentsMargins(QMargins(20, 0, 0, 0));

	layout->setAlignment(Qt::AlignCenter);
	layout->setContentsMargins(QMargins(100, 0, 100, 0));


	
	


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
