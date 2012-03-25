LIBS += -L ../EBPdb/ -lEBPdb \

SOURCES += \
    connectiontest.cpp \
    mitarbeitertest.cpp \
    main.cpp \
    bewohnertest.cpp \
    wohngruppentest.cpp \
    wohngruppenereignistest.cpp \
    bewohnerereignistest.cpp
CONFIG += qtestlib

INCLUDEPATH += $$PWD/../EBPdb
DEPENDPATH += $$PWD/../EBPdb

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../EBPdb/release/ -lEBPdb
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../EBPdb/debug/ -lEBPdb
else:unix:!macx:!symbian: LIBS += -L$$PWD/EBPdb/ -lEBPdb

INCLUDEPATH += $$PWD/../
DEPENDPATH += $$PWD/../

HEADERS += \
    AutoTest.h \
    connectiontest.h \
    MitarbeiterTest.h \
    bewohnertest.h \
    wohngruppentest.h \
    wohngruppenereignistest.h \
    bewohnerereignistest.h
