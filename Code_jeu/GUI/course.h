#ifndef COURSE_H
#define COURSE_H

#include <qwidget.h>
#include <qlabel.h>
#include <qgridlayout.h>
#include <qgraphicsscene.h>
#include <qgraphicsview.h>
#include <qgraphicsitem.h>
#include "position.h"
#include <sstream>
#include <iostream>
#include <iomanip>


class Course : public QWidget {
	Q_OBJECT

public:
	Course(QWidget* parent = nullptr);

	QGridLayout* layout;

	QGraphicsScene sceneRace;
	QGraphicsPixmapItem* backgroundCourse;
	QGraphicsPixmapItem* car;
	QGraphicsPixmapItem* ghost;
	QLabel* times;

	

	QGraphicsView* viewRace;

public slots:
	void moveCar(float x, float y, float angle);
	void moveGhost(float x, float y, float angle);
	void updateTimer(unsigned long current, unsigned long best, unsigned long last);
};

#endif
