cmake_minimum_required( VERSION 2.6 )
project( EBP )

enable_testing()

find_package( Qt4 REQUIRED )
include( ${QT_USE_FILE} )

add_subdirectory( EBPdb )

add_subdirectory( AdminDialog )
add_dependencies( AdminDialog EBPdb )

add_subdirectory( ebp_client )
add_dependencies( ebp_client EBPdb )

add_subdirectory( unit_test )
add_dependencies( fill_test EBPdb )

add_custom_target( doc )
add_dependencies( doc EBPdb_doc common_doc )

find_package( Doxygen )
if( DOXYGEN_FOUND )
	add_custom_target( common_doc ${DOXYGEN_EXECUTABLE} Doxyfile )
	set_directory_properties( PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES "doc/html;doc/latex;" )
else( DOXYGEN_FOUND )
	message( "Doxygen not found - 'common_doc' can't be generated." )
endif( DOXYGEN_FOUND )
