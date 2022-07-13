QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    changeamountwindow.cpp \
    clientsocket.cpp \
    crc16.cpp \
    decryptor.cpp \
    encryptor.cpp \
    groupmodelwindow.cpp \
    groupswindow.cpp \
    main.cpp \
    mainwindow.cpp \
    packetutil.cpp \
    productmodelwindow.cpp

HEADERS += \
    changeamountwindow.h \
    clientsocket.h \
    crc16.h \
    decryptor.h \
    encryptor.h \
    group.h \
    groupmodelwindow.h \
    groupswindow.h \
    mainwindow.h \
    packet.h \
    packetutil.h \
    product.h \
    productmodelwindow.h

FORMS += \
    changeamountwindow.ui \
    groupmodelwindow.ui \
    groupswindow.ui \
    mainwindow.ui \
    productmodelwindow.ui

LIBS += -LC:/OpenSSL-Win64/lib -llibcrypto
INCLUDEPATH += C:/OpenSSL-Win64/include

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
