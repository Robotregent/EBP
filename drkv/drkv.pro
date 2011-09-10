VERSION = 0.0.1
TEMPLATE = lib
TARGET =
DEPENDPATH += . ..
INCLUDEPATH += . ..

unix:LIBS += -lodb-mysql -lodb
#TODO:
#win32:LIBS += 

DESTDIR = lib

CONFIG += qt dll

CODECFORTR = UTF-8


# Input

ODB_HEADERS += Mitarbeiter.hxx

HEADERS += DBConnection.hxx

SOURCES += DBConnection.cxx \
	Mitarbeiter.cxx

TRANSLATIONS += libdrkv_de.ts \
	libdrkv_en.ts


QMAKE_CXXFLAGS_WARN_ON += -Wno-unknown-pragmas

# ODB - Run the Object-Relational Mapping (ORM) compiler
odb.input = ODB_HEADERS
odb.variable_out = SOURCES
odb.output  = ${QMAKE_FILE_BASE}-odb.cxx
odb.clean = ${QMAKE_FILE_BASE}-odb.cxx ${QMAKE_FILE_BASE}-odb.hxx ${QMAKE_FILE_BASE}-odb.ixx ${QMAKE_FILE_BASE}.sql
odb.commands = odb "$(INCPATH)" --database mysql --profile qt --generate-query --generate-schema ${QMAKE_FILE_NAME}
odb.dependcy_type = TYPE_C
#FIXME:
#odb.depend_command = g++ -E -M $$join(INCLUDEPATH,'" -I "','-I "','"') ${QMAKE_FILE_NAME} | sed \"s,^.*: ,,\"
odb.depends = FORCE
QMAKE_EXTRA_COMPILERS += odb

# Documentation
dox.target = doc
dox.commands = doxygen Doxyfile
dox.depends = FORCE
QMAKE_EXTRA_TARGETS += dox
QMAKE_DISTCLEAN += -r doc/html/ doc/latex/

# Translations
trans.target = tr
trans.commands = lupdate -no-obsolete drkv.pro
trans.depends = FORCE
QMAKE_EXTRA_TARGETS += trans

