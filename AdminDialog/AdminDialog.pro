#-------------------------------------------------
#
# Project created by QtCreator 2011-09-09T16:38:50
#
#-------------------------------------------------

LIBS += -L ../EBPdb/ -lEBPdb \

INCLUDEPATH += $$PWD/../EBPdb
DEPENDPATH += $$PWD/../EBPdb

SOURCES += main.cpp\
        admindialog.cpp \
    chooseemployee.cpp \
    employeelistmodel.cpp \
    zuordnung.cpp \
    costumdeletedialog.cpp

HEADERS  += admindialog.h \
    chooseemployee.h \
    employeelistmodel.h \
    costumlistwidget.h \
    costumtreewidget.h \
    zuordnung.h \
    costumdeletedialog.h \
    wohngruppedeletedialog.h

FORMS    += admindialog.ui \
    chooseemployee.ui \
    zuordnung.ui \
    costumdeletedialog.ui



win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../EBPdb/release/ -lEBPdb
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../EBPdb/debug/ -lEBPdb
else:unix:!macx:!symbian: LIBS += -L$$PWD/../EBPdb/ -lEBPdb

INCLUDEPATH += $$PWD/../
DEPENDPATH += $$PWD/../

CODECFORTR = UTF-8
CODECFORSRC = UTF-8
TRANSLATIONS = admindialog-a.ts
