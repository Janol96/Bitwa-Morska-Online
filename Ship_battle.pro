TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt
QT += network
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
        src/AIPlayer.cpp \
    src/BasicShip.cpp \
        src/Board.cpp \
        src/Game.cpp \
    src/GameLAN.cpp \
        src/NetworkManager.cpp \
        src/Player.cpp \
        src/Ship.cpp \
        src/SinglePlayerScreen.cpp \
        src/PlacementScreen.cpp \

HEADERS += \
    include/AIPlayer.h \
    include/BasicShip.h \
    include/Board.h \
    include/Game.h \
    include/GameLAN.h \
    include/NetworkManager.h \
    include/Player.h \
    include/Ship.h \
    include/SinglePlayerScreen.h \
    include/PlacementScreen.h \
