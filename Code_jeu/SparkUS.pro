TEMPLATE     = vcapp
TARGET       = SparkUS
CONFIG      += warn_on qt debug windows console
HEADERS     += controllers.h model_auto.h model_circuit.h position.h best_time.h course_record.h timer.h SerialPort.hpp json.hpp serial_communication.h leaderboard.h GUI/mainMenu.h
SOURCES     += main.cpp controller_course.cpp controller_menu.cpp model_auto.cpp model_circuit.cpp course_record.cpp timer.cpp SerialPort.cpp serial_communication.cpp leaderboard.cpp GUI/mainMenu.cpp
INCLUDEPATH += 
LIBS        += 
QT          += widgets