cmake_minimum_required(VERSION 2.6)
cmake_policy( SET CMP0015 NEW )
# set project's name
PROJECT(ebp_client)

# by default only QtCore and QtGui modules are enabled
# other modules must be enabled like this:
#SET(QT_USE_QTSQL TRUE)

FIND_PACKAGE( Qt4 REQUIRED )
INCLUDE( ${QT_USE_FILE} )

# with SET() command you can change variables or define new ones
# here we define SAMPLE_SRCS variable that contains a list of all .cpp files
SET( SAMPLE_SRCS
	betreuung.cpp
	bewohnerprotokoll.cpp
	clientmenu.cpp
	choosedialog.cpp
	decree.cpp
	decreescrollarea.cpp
	dokumentation.cpp
	einzelereignis.cpp
	ereignis.cpp
	groupmenu.cpp
	infoframe.cpp
	leistungstraegerarea.cpp
	leistungstraegerbox.cpp
	loginform.cpp
	main.cpp
	mainwindow.cpp
	meldeliste.cpp
	person.cpp
	pleaswaitdialog.cpp	
	projekt.cpp
	sidemenu.cpp
#	ueberarbeitungframe.cpp
	texttransferagent.cpp
	newereignisdialog.cpp
)

# another list, this time it includes all header files that should be treated with moc
SET( SAMPLE_MOC_HDRS
	betreuung.h
	bewohnerprotokoll.h
	clientmenu.h
	choosedialog.h
	decree.h
	decreescrollarea.h
	dokumentation.h
	einzelereignis.h
	ereignis.h
	groupmenu.h
	infoframe.h
	leistungstraegerarea.h
	leistungstraegerbox.h
	loginform.h
	mainwindow.h
	meldeliste.h
	person.h
	pleaswaitdialog.h
        projekt.h
	sidemenu.h
#	ueberarbeitungframe.h
	texttransferagent.h
	newereignisdialog.h
)

SET(ebp_src_library_dirs
	../EBPdb
)

SET(ebp_src_include_dirs
	${QT_INCLUDE_DIR}
	.
	..
)

SET(ebp_src_libraries
	${QT_LIBRARIES}
	EBPdb
)

# some .ui files
SET( SAMPLE_UIS
	betreuung.ui
	bewohnerprotokoll.ui
	choosedialog.ui
	decreescrollarea.ui
	dokumentation.ui
	einzelereignis.ui
	ereignis.ui
	infoframe.ui
	leistungstraegerarea.ui
	leistungstraegerbox.ui
	loginform.ui
	meldeliste.ui
	pleaswaitdialog.ui
	projekt.ui
#	ueberarbeitungframe.ui
	texttransferagent.ui
	newereignisdialog.ui
)
# and finally an resource file
SET( EBP_RCS
     images.qrc
)

# enable warnings
ADD_DEFINITIONS( -Wall -Wno-unknown-pragmas )

# this command will generate rules that will run rcc on all files from SAMPLE_RCS
# in result SAMPLE_RC_SRCS variable will contain paths to files produced by rcc
QT4_ADD_RESOURCES( SAMPLE_RC_SRCS ${EBP_RCS} )

# this will run uic on .ui files:
QT4_WRAP_UI( SAMPLE_UI_HDRS ${SAMPLE_UIS} )

# and finally this will run moc:
QT4_WRAP_CPP( SAMPLE_MOC_SRCS ${SAMPLE_MOC_HDRS} )

link_directories( ${ebp_src_library_dirs} )

# we need this to be able to include headers produced by uic in our code
# (CMAKE_BINARY_DIR holds a path to the build directory, while INCLUDE_DIRECTORIES() works just like INCLUDEPATH from qmake)
INCLUDE_DIRECTORIES( ${CMAKE_BINARY_DIR} ${ebp_src_include_dirs} )

ADD_EXECUTABLE( ebp_client ${SAMPLE_SRCS} ${SAMPLE_MOC_SRCS} ${SAMPLE_UI_HDRS} ${SAMPLE_RC_SRCS})

TARGET_LINK_LIBRARIES( ebp_client ${ebp_src_libraries} )
