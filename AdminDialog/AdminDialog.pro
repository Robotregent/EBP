#-------------------------------------------------
#
# Project created by QtCreator 2011-09-09T16:38:50
#
#-------------------------------------------------

#QT       += core gui
LIBS += -L ../EBPdb/ -lEBPdb \
#TARGET = AdminDialog
#TEMPLATE = app


SOURCES += main.cpp\
        admindialog.cpp \
    chooseemployee.cpp \
    employeelistmodel.cpp \
    zuordnung.cpp

HEADERS  += admindialog.h \
    chooseemployee.h \
    employeelistmodel.h \
    costumlistwidget.h \
    costumtreewidget.h \
    zuordnung.h

FORMS    += admindialog.ui \
    chooseemployee.ui \
    zuordnung.ui
