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
    betreuung.h \
    bewohnerprotokoll.h \
    leistungstraegerbox.h \
    leistungstraegerarea.h \
    meldeliste.h \
    ereignis.h \
    einzelereignis.h \
    projekt.h \
    dokumentation.h \
    WohngruppenUndBewohnerLaden.h \
    pleaswaitdialog.h \
    sessioncontext.h \
    texttransferinterface.h \
    texttransferagent.h \
    savecontentinterface.h \
    newereignisdialog.h \
    choosedialog.h \
    dokutypwrapper.h \
    customtablewidgetitem.h \
    customlistwidgetitem.h

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
    betreuung.cpp \
    bewohnerprotokoll.cpp \
    leistungstraegerbox.cpp \
    leistungstraegerarea.cpp \
    meldeliste.cpp \
    ereignis.cpp \
    einzelereignis.cpp \
    projekt.cpp \
    dokumentation.cpp \
    pleaswaitdialog.cpp \
    texttransferagent.cpp \
    newereignisdialog.cpp \
    choosedialog.cpp

RESOURCES += \
    images.qrc

FORMS += \
    decreescrollarea.ui \
    loginform.ui \
    infoframe.ui \
    betreuung.ui \
    bewohnerprotokoll.ui \
    leistungstraegerbox.ui \
    leistungstraegerarea.ui \
    meldeliste.ui \
    ereignis.ui \
    einzelereignis.ui \
    projekt.ui \
    dokumentation.ui \
    pleaswaitdialog.ui \
    texttransferagent.ui \
    newereignisdialog.ui \
    choosedialog.ui

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../EBPdb/release/ -lEBPdb
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../EBPdb/debug/ -lEBPdb
else:unix:!macx:!symbian: LIBS += -L$$PWD/../EBPdb/ -lEBPdb

INCLUDEPATH += $$PWD/../
DEPENDPATH += $$PWD/../

CODECFORTR = UTF-8
CODECFORSRC = UTF-8

TRANSLATIONS = ebp_client_Behindertenhilfe.ts \
               ebp_client_Altenhilfe.ts
