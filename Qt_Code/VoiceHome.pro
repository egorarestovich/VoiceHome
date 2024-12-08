QT       += core gui
QT += core
QT += serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

VERSION = 0.9.1.0
QMAKE_TARGET_COMPANY = VC
QMAKE_TARGET_PRODUCT = VoiceHome App
QMAKE_TARGET_DESCRIPTION = VoiceHome PC App
QMAKE_TARGET_COPYRIGHT = Egor Arestovich (Creator)

CONFIG += c++17

#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    renameusercommanddialog.cpp \
    voicehome.cpp \
    voicehomemainwindow.cpp

HEADERS += \
    renameusercommanddialog.h \
    voicehome.h \
    ui_voicehome.h \
    voicehomemainwindow.h

FORMS += \
    renameusercommanddialog.ui \
    voicehome.ui \
    voicehomemainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images.qrc
