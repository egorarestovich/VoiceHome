QT += core gui widgets serialport

CONFIG += c++17

TARGET = VoiceHome
TEMPLATE = app

SOURCES += \
    main.cpp \
    voicehome.cpp \
    voicehomemainwindow.cpp \
    serialportmanager.cpp \
    renameusercommanddialog.cpp

HEADERS += \
    voicehome.h \
    voicehomemainwindow.h \
    serialportmanager.h \
    renameusercommanddialog.h \
    styles.h

FORMS += \
    voicehome.ui \
    voicehomemainwindow.ui \
    renameusercommanddialog.ui

RESOURCES += \
    images.qrc

INCLUDEPATH += .
DEPENDPATH += .
