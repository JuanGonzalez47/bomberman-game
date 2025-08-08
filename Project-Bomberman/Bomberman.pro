QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../Project-Bomberman/Practicas-Lab-Info-II-Bomberman/Bomberman/bomb.cpp \
    ../Project-Bomberman/Practicas-Lab-Info-II-Bomberman/Bomberman/bomberman_character.cpp \
    ../Project-Bomberman/Practicas-Lab-Info-II-Bomberman/Bomberman/enemies.cpp \
    ../Project-Bomberman/Practicas-Lab-Info-II-Bomberman/Bomberman/main.cpp \
    ../Project-Bomberman/Practicas-Lab-Info-II-Bomberman/Bomberman/mainwindow.cpp \
    ../Project-Bomberman/Practicas-Lab-Info-II-Bomberman/Bomberman/sprites.cpp

HEADERS += \
    ../Project-Bomberman/Practicas-Lab-Info-II-Bomberman/Bomberman/bomb.h \
    ../Project-Bomberman/Practicas-Lab-Info-II-Bomberman/Bomberman/bomberman_character.h \
    ../Project-Bomberman/Practicas-Lab-Info-II-Bomberman/Bomberman/enemies.h \
    ../Project-Bomberman/Practicas-Lab-Info-II-Bomberman/Bomberman/mainwindow.h \
    ../Project-Bomberman/Practicas-Lab-Info-II-Bomberman/Bomberman/sprites.h

FORMS += \
    ../Project-Bomberman/Practicas-Lab-Info-II-Bomberman/Bomberman/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    ../Project-Bomberman/Practicas-Lab-Info-II-Bomberman/Bomberman/Image_burst.qrc \
    ../Project-Bomberman/Practicas-Lab-Info-II-Bomberman/Bomberman/Images.qrc
