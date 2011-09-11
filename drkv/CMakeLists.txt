cmake_minimum_required( VERSION 2.6 )
project( drkv )


set( libdrkv_headers
	DBConnection.hxx
	Mitarbeiter.hxx
	Wohngruppe.hxx
)

set( libdrkv_sources
	DBConnection.cxx
	Mitarbeiter.cxx
)

set( drkv_include_dirs
	${QT_INCLUDE_DIR}
	.
	..
)

set( drkv_library_dirs
)

set( drkv_libraries
	${QT_LIBRARIES}
	odb
	odb-mysql
)


find_package( Qt4 REQUIRED )
include( ${QT_USE_FILE} )
add_definitions( -Wall -Wno-unknown-pragmas )
link_directories( ${drkv_library_dirs} )
include_directories( ${drkv_include_dirs} )

foreach( header ${libdrkv_headers} )
	file( READ ${header} headercontent )
	if( "${headercontent}" MATCHES "[ \t]*#pragma[ \t]+db[ \t]+object" )
		get_filename_component( headerbase ${header} NAME_WE )
		set( libdrkv_sources ${libdrkv_sources} ${headerbase}-odb.cxx )
		get_directory_property( odbincludes INCLUDE_DIRECTORIES )
		foreach( includedir ${odbincludes} )
			set( odbincludeargs ${odbincludeargs} -I${includedir} )
		endforeach( includedir )
		add_custom_command( OUTPUT ${headerbase}-odb.cxx ${headerbase}-odb.hxx ${headerbase}-odb.ixx ${headerbase}.sql
			COMMAND odb ${odbincludeargs} --database mysql --profile qt --generate-query --generate-schema ${header}
			DEPENDS ${header} )
	endif( "${headercontent}" MATCHES "[ \t]*#pragma[ \t]+db[ \t]+object" )
endforeach( header )

add_library( drkv SHARED ${libdrkv_sources} )
target_link_libraries( drkv ${drkv_libraries} )
