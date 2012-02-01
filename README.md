# Elektronische Betreuungsplanung


## Was ist EBP


### Übersicht

Das Ziel ist es, eine Applikation zu entwickeln, die es Einrichtungen der Behinderten- und Altenhilfe ermöglicht,
die langfristige Betreuungsplanung mit der Tagesdokumentation zu verknüpfen. Es sollen Ereignisse aus dem Tagesgeschehen,
die in der Tagesdokumentation der Wohngruppe / des Pflegeheims erfasst werden,
der Betreuungsplanung des bertoffenen Bewohners zugeordnet werden können.
Damit soll doppelter Dokumentationsaufwand verhindert werden.

Die Software soll in stationären und ambulanten Einrichtungen der Behindertenhilfe in Baden Württemberg eingesetzt werden.
Diese Version orientiert sich an dem aktuell in Baden Württemberg geltenden Standard, dem Metzler-Verfahren.


### Bestandteile

Die Anwendung besteht aus:

* einer Bibliothek für den Zugriff auf die Datenbank (libEBPdb)
* einem Administrationswerkzeug
* und der eigentlichen Bedienoberfläche


## Abhängigkeiten

* Qt4
* ODB


## Kompilieren & Installieren

Die komplette Anwendung lässt sich mit

	$ cmake . && make

kompilieren.
Dies baut die Bibliothek und alle weiteren Programme.

Um die Datenbank zu initialisieren befindet sich ein Shell-Script im EBPdb Verzeichnis:

	$ ./initDB.sh -u root -p "DATENBAKNAME"

Ab Ubuntu 11.10 kann es zu Problemen mit verschiedenen Architekturen kommen. Folgender Fehler tritt häufig auf:

* /usr/include/features.h:323:26: fatal error: bits/predefs.h: No such file or directory

Das installieren der entsprechenden libc hilft.

	$ apt-get install libc6-dev-i386

## Integration des QtCreators:

Im Creator in jedem Projekt als Systemvariable angeben:

	LD_LIBRARY_PATH ../EBPdb
