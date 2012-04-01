cmake_minimum_required(VERSION 2.6)
cmake_policy( SET CMP0015 NEW )
# set project's name
PROJECT(unit_test)

enable_testing()

FIND_PACKAGE( Qt4 REQUIRED )
INCLUDE( ${QT_USE_FILE} )

# with SET() command you can change variables or define new ones
# here we define SAMPLE_SRCS variable that contains a list of all .cpp files
SET( FILL_TEST_SRCS
	createtest.cpp
	fillfieldstest.cpp
	linktest.cpp
	main.cpp
)
SET( REMOVE_TEST_SRCS	
	unlinktest.cpp
	removetest.cpp
	main.cpp
)
  
# another list, this time it includes all header files that should be treated with moc
SET( FILL_TEST_MOC_HDRS
	createtest.h
	fillfieldstest.h
	linktest.h
)
SET( REMOVE_TEST_MOC_HDRS
	unlinktest.h
	removetest.h
)
#lib directories
SET(unit_test_library_dirs
	../EBPdb
)
SET(unit_test_include_dirs
	${QT_INCLUDE_DIR}
	.
	..
)
#some libs
SET(unit_test_libraries
	${QT_QTTEST_LIBRARY}
	${QT_LIBRARIES}
	EBPdb
)
  

# enable warnings
ADD_DEFINITIONS( -Wall -Wno-unknown-pragmas )

  

SET(QT_USE_QTTEST TRUE)
# this command finds Qt4 libraries and sets all required variables
# note that it's Qt4, not QT4 or qt4
FIND_PACKAGE( Qt4 REQUIRED )
# add some useful macros and variables
# (QT_USE_FILE is a variable defined by FIND_PACKAGE( Qt4 ) that contains a path to CMake script)
INCLUDE( ${QT_USE_FILE} )
  

QT4_WRAP_CPP( FILL_TEST_MOC_SRCS ${FILL_TEST_MOC_HDRS} )
QT4_WRAP_CPP( REMOVE_TEST_MOC_SRCS ${REMOVE_TEST_MOC_HDRS} )

link_directories(${unit_test_library_dirs})  
# we need this to be able to include headers produced by uic in our code
# (CMAKE_BINARY_DIR holds a path to the build directory, while INCLUDE_DIRECTORIES() works just like INCLUDEPATH from qmake)
INCLUDE_DIRECTORIES( ${CMAKE_BINARY_DIR} ${unit_test_include_dirs} )

# initialize Database
add_test( initDB sh -c "cat ../EBPdb/*.sql *.sql | mysql $@ -u root -p ebp_test" )

# fill Database
ADD_EXECUTABLE( fill_test ${FILL_TEST_SRCS} ${FILL_TEST_MOC_SRCS} )
TARGET_LINK_LIBRARIES( fill_test ${unit_test_libraries})
ADD_TEST( fill_test fill_test )
set_property( TEST fill_test APPEND PROPERTY DEPENDS initDB )

# remove Database
ADD_EXECUTABLE( remove_test ${REMOVE_TEST_SRCS} ${REMOVE_TEST_MOC_SRCS} )
TARGET_LINK_LIBRARIES( remove_test ${unit_test_libraries})
ADD_TEST( remove_test remove_test )
set_property( TEST remove_test APPEND PROPERTY DEPENDS fill_test )
