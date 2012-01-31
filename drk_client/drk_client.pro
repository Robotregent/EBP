LIBS += -L ../EBPdb/ -lEBPdb \

HEADERS += \
    mainwindow.h \
    clientmenu.h \
    sidemenu.h \
    groupmenu.h \
    person.h \
    decree.h \
    decreescrollarea.h \
    loginform.h \
    infoframe.h \
    ueberarbeitungframe.h \
    betreuung.h \
    bewohnerprotokoll.h \
    leistungstraegerbox.h \
    leistungstraegerarea.h \
    meldeliste.h \
    gruppenbuch.h

SOURCES += \
    mainwindow.cpp \
    main.cpp \
    clientmenu.cpp \
    sidemenu.cpp \
    groupmenu.cpp \
    person.cpp \
    decree.cpp \
    decreescrollarea.cpp \
    loginform.cpp \
    infoframe.cpp \
    ueberarbeitungframe.cpp \
    betreuung.cpp \
    bewohnerprotokoll.cpp \
    leistungstraegerbox.cpp \
    leistungstraegerarea.cpp \
    meldeliste.cpp \
    gruppenbuch.cpp

RESOURCES += \
    images.qrc

FORMS += \
    decreescrollarea.ui \
    loginform.ui \
    infoframe.ui \
    ueberarbeitungframe.ui \
    betreuung.ui \
    bewohnerprotokoll.ui \
    leistungstraegerbox.ui \
    leistungstraegerarea.ui \
    meldeliste.ui \
    gruppenbuch.ui
