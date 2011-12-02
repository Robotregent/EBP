cmake_minimum_required( VERSION 2.6 )
project( EBPdb )

find_package( Qt4 REQUIRED )
include( ${QT_USE_FILE} )

add_subdirectory( EBPdb )
add_subdirectory( AdminDialog )
add_subdirectory( drk_client )
add_dependencies( AdminDialog EBPdb )
add_dependencies( drk_client EBPdb )
