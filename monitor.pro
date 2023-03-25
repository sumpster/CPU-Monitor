QT += widgets

CONFIG += debug

TARGET = monitor
TEMPLATE = app

SOURCES += src/main.cpp
SOURCES += src/model/Model.cpp src/model/HistogramEntry.cpp 
SOURCES += src/hw/linux.cpp
SOURCES += src/ui/section.cpp src/ui/dots.cpp src/ui/chart.cpp

HEADERS += src/model/Model.h src/model/HistogramEntry.h 
HEADERS += src/ui/section.h src/ui/dots.h src/ui/chart.h

RESOURCES += resources/resources.qrc

OBJECTS_DIR = build/obj
MOC_DIR = build/moc
RCC_DIR = build/qrc
