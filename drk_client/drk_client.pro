LIBS += -L ../drkv/ -ldrkv \

HEADERS += \
    mainwindow.h \
    clientmenu.h \
    sidemenu.h \
    groupmenu.h \
    person.h \
    decree.h \
    decreescrollarea.h \
    loginform.h \
    infowidget.h \
    infoframe.h \
    ueberarbeitungframe.h \
    betreuung.h \
    bewohnerprotokoll.h

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
    infowidget.cpp \
    infoframe.cpp \
    ueberarbeitungframe.cpp \
    betreuung.cpp \
    bewohnerprotokoll.cpp

RESOURCES += \
    images.qrc

FORMS += \
    decreescrollarea.ui \
    loginform.ui \
    infowidget.ui \
    infoframe.ui \
    ueberarbeitungframe.ui \
    betreuung.ui \
    bewohnerprotokoll.ui
