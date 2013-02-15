TEMPLATE = app
CONFIG += console
CONFIG -= qt

SOURCES += main.cpp \
    perceptron.cpp \
    csv/csvhandler.cpp \
    neuralnet.cpp

HEADERS += \
    perceptron.h \
    csv/csvhandler.h \
    neuralnet.h

OTHER_FILES += \
    out.csv \
    train.csv

