#-------------------------------------------------
#
# Project created by QtCreator 2011-09-09T16:38:50
#
#-------------------------------------------------
INCLUDEPATH += ../
#QT       += core gui
LIBS += -L ../EBPdb/ -lEBPdb \
#TARGET = AdminDialog
#TEMPLATE = app


SOURCES += main.cpp\
    admindialog.cpp \
    employeelistmodel.cpp \
    mamodel.cpp
    zuordnung.cpp

HEADERS  += admindialog.h \
    employeelistmodel.h \
    costumlistwidget.h \
    costumtreewidget.h \
    mamodel.h
    zuordnung.h
FORMS    += admindialog.ui \
    chooseemployee.ui \
    zuordnung.ui
