LIBS += -L ../EBPdb/ -lEBPdb \

SOURCES += \
    main_use.cpp \
    loadrelationtest.cpp \
    loadfieldstest.cpp

HEADERS += \
    AutoTest.h \
    loadrelationtest.h \
    loadfieldstest.h

CONFIG += qtestlib

INCLUDEPATH += $$PWD/../EBPdb
DEPENDPATH += $$PWD/../EBPdb

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../EBPdb/release/ -lEBPdb
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../EBPdb/debug/ -lEBPdb
else:unix:!macx:!symbian: LIBS += -L$$PWD/EBPdb/ -lEBPdb

INCLUDEPATH += $$PWD/../
DEPENDPATH += $$PWD/../
