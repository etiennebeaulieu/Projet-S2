TEMPLATE     = vcapp
TARGET       = SparkUS
CONFIG      += warn_on qt debug windows console
HEADERS     += controller_course.h controller_menu.h model_auto.h model_circuit.h position.h best_time.h
SOURCES     += main.cpp controller_course.cpp controller_menu.cpp model_auto.cpp model_circuit.cpp
INCLUDEPATH += 
LIBS        += 
QT          += widgets