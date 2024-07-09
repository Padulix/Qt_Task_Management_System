QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    data_processing.cpp \
    details.cpp \
    formsplash.cpp \
    languagesettings.cpp \
    main.cpp \
    mainwindow.cpp \
    task.cpp

HEADERS += \
    data_processing.h \
    details.h \
    formsplash.h \
    languagesettings.h \
    mainwindow.h \
    task.h

FORMS += \
    details.ui \
    formsplash.ui \
    languagesettings.ui \
    mainwindow.ui \
    splash_screen.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    rsc.qrc

TRANSLATIONS += \
    Projekt_Patrick_Pertler_de_DE.ts \
    Projekt_Patrick_Pertler_en_150.ts
