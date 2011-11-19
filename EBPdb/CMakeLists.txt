cmake_minimum_required( VERSION 2.6 )
project( EBPdb )

find_package( Qt4 REQUIRED )
include( ${QT_USE_FILE} )


set( EBPdb_headers
	connection.hxx
	Mitarbeiter.hxx
	Bewohner.hxx
	Bewohnerereignis.hxx
	Wohngruppe.hxx
	Wohngruppenereignis.hxx
	Wohnheim.hxx
	Projekt.hxx
	Protokoll.hxx
)

set( EBPdb_sources
	connection.cxx
	Mitarbeiter.cxx
	Bewohner.cxx
	Bewohnerereignis.cxx
	Wohngruppe.cxx
	Wohngruppenereignis.cxx
	Wohnheim.cxx
	Projekt.cxx
	Protokoll.cxx
)

set( EBPdb_include_dirs
	${QT_INCLUDE_DIR}
	.
	..
)

set( EBPdb_library_dirs
)

set( EBPdb_libraries
	${QT_LIBRARIES}
	odb
	odb-mysql
	odb-qt
)


add_definitions( -Wall -Wno-unknown-pragmas )
link_directories( ${EBPdb_library_dirs} )
include_directories( ${EBPdb_include_dirs} )

foreach( header ${EBPdb_headers} )
	file( READ ${header} headercontent )
	if( "${headercontent}" MATCHES "#pragma[ \t]+db[ \t]+object" )
		get_filename_component( headerbase ${header} NAME_WE )
		set( EBPdb_sources ${EBPdb_sources} ${headerbase}-odb.cxx )
		get_directory_property( odbincludes INCLUDE_DIRECTORIES )
		foreach( includedir ${odbincludes} )
			set( odbincludeargs ${odbincludeargs} -I${includedir} )
		endforeach( includedir )
		add_custom_command( OUTPUT ${headerbase}-odb.cxx ${headerbase}-odb.hxx ${headerbase}-odb.ixx ${headerbase}.sql
			COMMAND odb ${odbincludeargs} --database mysql --profile qt --generate-query --generate-schema ${header}
			DEPENDS ${header} )
	endif( "${headercontent}" MATCHES "#pragma[ \t]+db[ \t]+object" )
endforeach( header )

add_library( EBPdb SHARED ${EBPdb_sources} )
target_link_libraries( EBPdb ${EBPdb_libraries} )