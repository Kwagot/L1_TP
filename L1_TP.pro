TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        animal.cpp \
        bird.cpp \
        cat.cpp \
        container.cpp \
        fish.cpp \
        main.cpp

HEADERS += \
    animal.h \
    bird.h \
    cat.h \
    container.h \
    exceptions.h \
    fish.h
