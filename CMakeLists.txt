cmake_minimum_required( VERSION 2.6 )
project( EBP )

enable_testing()

find_package( Qt4 REQUIRED )
include( ${QT_USE_FILE} )

add_subdirectory( EBPdb )

add_subdirectory( AdminDialog )
add_dependencies( AdminDialog EBPdb )

add_subdirectory( drk_client )
add_dependencies( drk_client EBPdb )

add_subdirectory( unit_test )
add_dependencies( fill_test EBPdb )

add_custom_target( doc )
add_dependencies( doc EBPdb_doc )
