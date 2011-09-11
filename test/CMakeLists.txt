cmake_minimum_required( VERSION 2.6 )
cmake_policy( SET CMP0015 NEW )
project( test )

find_package( Qt4 REQUIRED )
include( ${QT_USE_FILE} )


set( test_headers
)

set( test_sources
	main.cxx
)

set( test_include_dirs
	${QT_INCLUDE_DIR}
	.
	..
)

set( test_library_dirs
	../drkv
)

set( test_libraries
	${QT_LIBRARIES}
	drkv
#	odb
#	odb-mysql
#	odb-qt
)


add_definitions( -Wall -Wno-unknown-pragmas )
link_directories( ${test_library_dirs} )
include_directories( ${test_include_dirs} )

add_executable( test ${test_sources} )
target_link_libraries( test ${test_libraries} )
