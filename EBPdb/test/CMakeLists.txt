cmake_minimum_required( VERSION 2.6 )
project( EBPdbTest )

cmake_policy( SET CMP0015 NEW )

enable_testing()

find_package( Qt4 REQUIRED )
include( ${QT_USE_FILE} )


set( EBPdbTest_include_dirs
	${QT_INCLUDE_DIR}
	.
	../..
)

set( EBPdbTest_library_dirs
	..
)

set( EBPdbTest_libraries
	${QT_LIBRARIES}
	odb
	odb-mysql
	odb-qt
	EBPdb
)


add_definitions( -Wall -Wno-unknown-pragmas )
link_directories( ${EBPdbTest_library_dirs} )
include_directories( ${EBPdbTest_include_dirs} )

add_test( initDB sh -c "cd .. && ./initDB.sh -u root -p ebp_test" )

add_executable( fillDB fillDB.cxx )
target_link_libraries( fillDB ${EBPdbTest_libraries} )
add_test( fillDB fillDB )
set_property( TEST fillDB APPEND PROPERTY DEPENDS initDB )

add_executable( permissions permissions.cxx )
target_link_libraries( permissions ${EBPdbTest_libraries} )
add_test( permissions permissions )
set_property( TEST permissions APPEND PROPERTY DEPENDS fillDB )
