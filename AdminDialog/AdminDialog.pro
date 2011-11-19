#-------------------------------------------------
#
# Project created by QtCreator 2011-09-09T16:38:50
#
#-------------------------------------------------

#QT       += core gui
LIBS += -L ../drkv/ -ldrkv \
#TARGET = AdminDialog
#TEMPLATE = app


SOURCES += main.cpp\
    admindialog.cpp \
    employeelistmodel.cpp \
    mamodel.cpp

HEADERS  += admindialog.h \
    employeelistmodel.h \
    costumlistwidget.h \
    costumtreewidget.h \
    mamodel.h

FORMS    += admindialog.ui
