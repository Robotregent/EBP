cmake_minimum_required(VERSION 2.6)
cmake_policy( SET CMP0015 NEW )
# set project's name
PROJECT(AdminDialog)


FIND_PACKAGE( Qt4 REQUIRED )
INCLUDE( ${QT_USE_FILE} )

# with SET() command you can change variables or define new ones
# here we define SAMPLE_SRCS variable that contains a list of all .cpp files
SET( SAMPLE_SRCS
	admindialog.cpp
	chooseemployee.cpp
	costumdeletedialog.cpp
	employeelistmodel.cpp
	zuordnung.cpp
	main.cpp
)
  
# another list, this time it includes all header files that should be treated with moc
SET( SAMPLE_MOC_HDRS
       admindialog.h
	chooseemployee.h
	costumdeletedialog.h
	employeelistmodel.h
	zuordnung.h
#	wohngruppedeletedialog.h
#	oelistwidgetitem.h
)
#lib directories
SET(AdminDialog_library_dirs
	../EBPdb
)
SET(AdminDialog_include_dirs
	${QT_INCLUDE_DIR}
	.
	..
)
#some libs
SET(AdminDialog_libraries
	${QT_LIBRARIES}
	EBPdb
)
  
# some .ui files
SET( SAMPLE_UIS
	admindialog.ui
	chooseemployee.ui
	costumdeletedialog.ui
	zuordnung.ui
)
# and finally an resource file
# SET( SAMPLE_RCS
#     ./src/rc/sample.qrc
#)
 
# enable warnings
ADD_DEFINITIONS( -Wall -Wno-unknown-pragmas )
  
# by default only QtCore and QtGui modules are enabled
# other modules must be enabled like this:
SET(QT_USE_QTSQL TRUE)
# this command finds Qt4 libraries and sets all required variables
# note that it's Qt4, not QT4 or qt4
FIND_PACKAGE( Qt4 REQUIRED )
# add some useful macros and variables
# (QT_USE_FILE is a variable defined by FIND_PACKAGE( Qt4 ) that contains a path to CMake script)
INCLUDE( ${QT_USE_FILE} )
  
# this command will generate rules that will run rcc on all files from SAMPLE_RCS
# in result SAMPLE_RC_SRCS variable will contain paths to files produced by rcc
#QT4_ADD_RESOURCES( SAMPLE_RC_SRCS ${SAMPLE_RCS} )
  
# this will run uic on .ui files:
QT4_WRAP_UI( SAMPLE_UI_HDRS ${SAMPLE_UIS} )
  
# and finally this will run moc:
QT4_WRAP_CPP( SAMPLE_MOC_SRCS ${SAMPLE_MOC_HDRS} )

link_directories(${AdminDialog_library_dirs})  
# we need this to be able to include headers produced by uic in our code
# (CMAKE_BINARY_DIR holds a path to the build directory, while INCLUDE_DIRECTORIES() works just like INCLUDEPATH from qmake)
INCLUDE_DIRECTORIES( ${CMAKE_BINARY_DIR} ${AdminDialog_include_dirs} )
  
ADD_EXECUTABLE( AdminDialog ${SAMPLE_SRCS} ${SAMPLE_MOC_SRCS} ${SAMPLE_UI_HDRS} )
  
TARGET_LINK_LIBRARIES( AdminDialog ${AdminDialog_libraries} )
