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
    chooseemployee.cpp \
    employeelistmodel.cpp

HEADERS  += admindialog.h \
    chooseemployee.h \
    employeelistmodel.h \
    costumlistwidget.h \
    costumtreewidget.h

FORMS    += admindialog.ui \
    chooseemployee.ui











