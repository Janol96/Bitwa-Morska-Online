TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt
INCLUDEPATH += "C:/SFML-2.5.1/include"
INCLUDEPATH += include
LIBS += -L"C:/SFML-2.5.1/lib"
CONFIG(debug, debug|release){
    LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-network-d -lsfml-system-d -lsfml-window-d
} else {
    LIBS += -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-system -lsfml-window
}

SOURCES += \
        main.cpp \
        src/Board.cpp \
        src/Ship.cpp \
        src/SinglePlayerScreen.cpp

HEADERS += \
    include/Board.h \
    include/Ship.h \
    include/SinglePlayerScreen.h
