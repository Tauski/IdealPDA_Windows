QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ProgramSettings.cpp \
    calendardialog.cpp \
    credentialsgateway.cpp \
    logindialog.cpp \
    main.cpp \
    mainwindow.cpp \
    notedialog.cpp \
    notelistdialog.cpp

HEADERS += \
    ProgramSettings.h \
    calendardialog.h \
    credentialsgateway.h \
    logindialog.h \
    mainwindow.h \
    notedialog.h \
    notelistdialog.h

FORMS += \
    calendardialog.ui \
    logindialog.ui \
    mainwindow.ui \
    notedialog.ui \
    notelistdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
