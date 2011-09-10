TEMPLATE = app
TARGET = 
DEPENDPATH += . ..
INCLUDEPATH += . ..
unix:LIBS += -L../drkv/lib -ldrkv
#win32:LIBS += 

CODECFORTR = UTF-8

# Input
#HEADERS += 
#FORMS += 
SOURCES += main.cxx

QMAKE_CXXFLAGS_WARN_ON += -Wno-unknown-pragmas
