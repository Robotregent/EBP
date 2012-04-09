#include "connection.hxx"
#include "Mitarbeiter.hxx"
#include "Mitarbeiter-odb.hxx"

#include <odb/core.hxx>
#include <odb/database.hxx>
#include <odb/session.hxx>
#include <odb/transaction.hxx>
#include <odb/mysql/database.hxx>

#include <QString>
#include <QDebug>


using namespace ebp;


connection::connection
(
	const QString & user,
	const QString & database,
	const QString & host,
	unsigned int port
) :
	dbUser(user),
	dbDatabase(database),
	dbHost(host),
	dbPort(port),
	connectedUser()
{
	db = NULL;
	s = NULL;
}


connection::~connection()
{
	delete s;
	delete db;
}


bool connection::establish( const QString & password )
{
	try
	{
		db = new odb::mysql::database( dbUser.toStdString(), password.toStdString(), dbDatabase.toStdString(), dbHost.toStdString(), dbPort );
		s = new odb::session();
		odb::transaction t( db->begin() );
		odb::result<Mitarbeiter> r( db->query<Mitarbeiter>( odb::query<Mitarbeiter>::login == odb::query<Mitarbeiter>::_ref(dbUser) ) );
		if( r.begin() != r.end() )
			connectedUser = QSharedPointer<Mitarbeiter>( r.begin().load() );
		else
			qWarning() << tr("Der verwendete Datenbankbenutzer \"%1\" ist nicht als Mitarbeiter registriert.").arg(dbUser);
		t.commit();
	}
	catch( const odb::exception & e )
	{
		qCritical() << e.what();
		return false;
	}
	return true;
}


void connection::flushCache()
{
	delete s;
	s = new odb::session();
}


void connection::executeCreateUser( const Mitarbeiter & mitarbeiter, const QString & from, const QString & password )
{
	execute( "CREATE USER '"+mitarbeiter.login()+"'@'"+from+"' IDENTIFIED BY '"+password+"';" );
	switch( mitarbeiter.berechtigung() )
	{
		case Mitarbeiter::AdminRecht:
			execute( "GRANT ALL PRIVILEGES ON "+dbDatabase+".* TO '"+mitarbeiter.login()+"'@'"+from+"' WITH GRANT OPTION;" );
			execute( "GRANT CREATE USER,RELOAD,PROCESS ON *.* TO '"+mitarbeiter.login()+"'@'"+from+"' WITH GRANT OPTION;" );
			break;
		case Mitarbeiter::WohnverbundRecht:
			execute( "GRANT UPDATE,INSERT,DELETE ON "+dbDatabase+".Wohnheim TO '"+mitarbeiter.login()+"'@'"+from+"';" );
		case Mitarbeiter::WohnheimRecht:
			execute( "GRANT UPDATE,INSERT,DELETE ON "+dbDatabase+".Wohngruppe TO '"+mitarbeiter.login()+"'@'"+from+"';" );
		case Mitarbeiter::WohngruppenRecht:
			execute( "GRANT UPDATE,INSERT,DELETE ON "+dbDatabase+".Betreuung TO '"+mitarbeiter.login()+"'@'"+from+"';" );
			execute( "GRANT UPDATE,INSERT,DELETE ON "+dbDatabase+".Wohngruppenereignis_schreiber TO '"+mitarbeiter.login()+"'@'"+from+"';" );
			execute( "GRANT UPDATE,INSERT,DELETE ON "+dbDatabase+".Wohngruppenereignis TO '"+mitarbeiter.login()+"'@'"+from+"';" );
			execute( "GRANT UPDATE,INSERT,DELETE ON "+dbDatabase+".Bewohner TO '"+mitarbeiter.login()+"'@'"+from+"';" );
			execute( "GRANT UPDATE,INSERT,DELETE ON "+dbDatabase+".Bewohnerereignis TO '"+mitarbeiter.login()+"'@'"+from+"';" );
			execute( "GRANT UPDATE,INSERT,DELETE ON "+dbDatabase+".Projekt TO '"+mitarbeiter.login()+"'@'"+from+"';" );
			execute( "GRANT UPDATE,INSERT,DELETE ON "+dbDatabase+".Projekt_verantwortliche TO '"+mitarbeiter.login()+"'@'"+from+"';" );
			execute( "GRANT UPDATE,INSERT,DELETE ON "+dbDatabase+".Protokoll TO '"+mitarbeiter.login()+"'@'"+from+"';" );
			execute( "GRANT UPDATE,INSERT,DELETE ON "+dbDatabase+".Protokoll_schreiber TO '"+mitarbeiter.login()+"'@'"+from+"';" );
			execute( "GRANT UPDATE,INSERT,DELETE ON "+dbDatabase+".Protokoll_teilnehmer TO '"+mitarbeiter.login()+"'@'"+from+"';" );
			execute( "GRANT UPDATE,INSERT,DELETE ON "+dbDatabase+".Abwesenheit TO '"+mitarbeiter.login()+"'@'"+from+"';" );
			execute( "GRANT UPDATE,INSERT,DELETE ON "+dbDatabase+".Verfuegung TO '"+mitarbeiter.login()+"'@'"+from+"';" );
			execute( "GRANT UPDATE,INSERT,DELETE ON "+dbDatabase+".Dokumentation TO '"+mitarbeiter.login()+"'@'"+from+"';" );
			execute( "GRANT UPDATE,INSERT,DELETE ON "+dbDatabase+".Leistungstraeger TO '"+mitarbeiter.login()+"'@'"+from+"';" );
			execute( "GRANT UPDATE,INSERT,DELETE ON "+dbDatabase+".Leistungstraeger_bewohner TO '"+mitarbeiter.login()+"'@'"+from+"';" );
			execute( "GRANT SELECT ON "+dbDatabase+".* TO '"+mitarbeiter.login()+"'@'"+from+"';" );
			break;
		default:
			break;
	}
	execute( "FLUSH PRIVILEGES;" );
}


void connection::executeCreateUser( const Mitarbeiter & mitarbeiter, const QString & password )
{
	executeCreateUser( mitarbeiter, "localhost", password );
	executeCreateUser( mitarbeiter, "%", password );
}


void connection::executeDropUser( const Mitarbeiter & mitarbeiter, const QString & from )
{
	execute( "DROP USER '"+mitarbeiter.login()+"'@'"+from+"';" );
}


void connection::executeDropUser( const Mitarbeiter & mitarbeiter )
{
	executeDropUser( mitarbeiter, "localhost" );
	executeDropUser( mitarbeiter, "%" );
}


void connection::executeSetPassword( const Mitarbeiter & mitarbeiter, const QString & from, const QString & password )
{
	// if the current user should be updated, don't use the FOR clause, so everyone can set its own password
	if( dbUser == mitarbeiter.login() )
		execute( "SET PASSWORD = PASSWORD('"+password+"');" );
	else
		execute( "SET PASSWORD FOR '"+mitarbeiter.login()+"'@'"+from+"' = PASSWORD('"+password+"');" );
}


void connection::executeSetPassword( const Mitarbeiter & mitarbeiter, const QString & password )
{
	executeSetPassword( mitarbeiter, "localhost", password );
	executeSetPassword( mitarbeiter, "%", password );
}
