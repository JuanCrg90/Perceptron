TEMPLATE = app
CONFIG += console
CONFIG -= qt

SOURCES += main.cpp \
    perceptron.cpp \
    csv/csvhandler.cpp

HEADERS += \
    perceptron.h \
    csv/csvhandler.h

OTHER_FILES += \
    out.csv \
    train.csv

