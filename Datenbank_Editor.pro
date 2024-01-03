QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    datenbank_editor.cpp
HEADERS += \
    SQLiteDatabase.h \
    SQLiteDatabase.h \
    _struct.h \
    datenbank_editor.h \
    land.h \
    liga.h \
    mensch.h \
    nationalmannschaft.h \
    stadt.h \
    verein.h
FORMS += \
    datenbank_editor.ui
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
	resources/icons/icons.qrc
