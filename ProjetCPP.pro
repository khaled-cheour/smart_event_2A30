QT       += core gui sql axcontainer printsupport network serialport multimedia multimediawidgets charts

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

SOURCES += \
    connexion.cpp \
    dialog_event.cpp \
    dialog_fourni.cpp \
    dialog_locaux.cpp \
    dialog_menu.cpp \
    dialog_perso.cpp \
    dialog_sponso.cpp \
    evenement.cpp \
    fournisseur.cpp \
    local.cpp \
    login_bd.cpp \
    main.cpp \
    mainwindow.cpp \
    personnel.cpp \
    sponsoring.cpp

HEADERS += \
    connexion.h \
    dialog_event.h \
    dialog_fourni.h \
    dialog_locaux.h \
    dialog_menu.h \
    dialog_perso.h \
    dialog_sponso.h \
    evenement.h \
    fournisseur.h \
    local.h \
    login_bd.h \
    mainwindow.h \
    personnel.h \
    sponsoring.h

FORMS += \
    dialog_event.ui \
    dialog_fourni.ui \
    dialog_locaux.ui \
    dialog_menu.ui \
    dialog_perso.ui \
    dialog_sponso.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Source.qrc
