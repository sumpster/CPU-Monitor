QT += widgets

CONFIG += debug

TARGET = monitor
TEMPLATE = app

SOURCES += src/main.cpp src/model.cpp src/hw/linux.cpp src/ui/section.cpp src/ui/dots.cpp src/ui/chart.cpp

HEADERS += src/model.h src/ui/section.h src/ui/dots.h src/ui/chart.h

RESOURCES += resources/resources.qrc
