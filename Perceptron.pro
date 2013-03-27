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
    datasets/hiddenWeights.csv \
    datasets/inputWeights.csv \
    datasets/outTest.csv \
    datasets/outWeights.csv \
    datasets/train.csv \
    datasets/trainC.csv \
    datasets/plotData.m \
    datasets/loadTest.m

