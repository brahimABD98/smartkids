QT       += core gui sql printsupport


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
    aliment.cpp \
    bus.cpp \
    charrad/deponse.cpp \
    charrad/gestiono9.cpp \
    charrad/revenu.cpp \
    charrad/statistique.cpp \
    club.cpp \
    connexion.cpp \
    eleves.cpp \
    equipement.cpp \
    excursion.cpp \
    gestion.cpp \
    gestion_activite.cpp \
    gestion_employe.cpp \
    instituteur.cpp \
    main.cpp \
    mainwindow.cpp \
    salles.cpp \
    staff_technique.cpp \
    stock.cpp

HEADERS += \
    aliment.h \
    bus.h \
    charrad/deponse.h \
    charrad/gestiono9.h \
    charrad/revenu.h \
    charrad/statistique.h \
    club.h \
    connexion.h \
    eleves.h \
    equipement.h \
    excursion.h \
    gestion.h \
    gestion_activite.h \
    gestion_employe.h \
    instituteur.h \
    mainwindow.h \
    salles.h \
    staff_technique.h \
    stock.h

FORMS += \
    charrad/gestiono9.ui \
    gestion.ui \
    gestion_activite.ui \
    gestion_employe.ui \
    mainwindow.ui \
    stock.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    icon.qrc

DISTFILES += \
    icon/Fichier 1.png \
    icon/bus.png
