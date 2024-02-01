QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += \
    facile_menu/\
    interactive_buttons/\
    multi_layer_selector/

SOURCES += \
    facile_menu/facilemenu.cpp \
    facile_menu/facilemenubar.cpp \
    facile_menu/facilemenuitem.cpp \
    interactive_buttons/interactivebuttonbase.cpp \
    interactive_buttons/watercirclebutton.cpp \
    main.cpp \
    mainwindow.cpp \
    multi_layer_selector/multilayerselector.cpp

HEADERS += \
    facile_menu/facilemenu.h \
    facile_menu/facilemenuanimation.h \
    facile_menu/facilemenubar.h \
    facile_menu/facilemenubarinterface.h \
    facile_menu/facilemenuitem.h \
    interactive_buttons/interactivebuttonbase.h \
    interactive_buttons/watercirclebutton.h \
    mainwindow.h \
    multi_layer_selector/layeriteminfo.h \
    multi_layer_selector/multilayerselector.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
