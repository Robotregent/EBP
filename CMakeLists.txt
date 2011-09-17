cmake_minimum_required( VERSION 2.6 )
project( drk )

find_package( Qt4 REQUIRED )
include( ${QT_USE_FILE} )

add_subdirectory( drkv )
add_subdirectory( AdminDialog )
add_dependencies( AdminDialog drkv )
