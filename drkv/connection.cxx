#include "connection.hxx"
#include "Mitarbeiter-odb.hxx"

#include <odb/core.hxx>
#include <odb/database.hxx>
#include <odb/session.hxx>
#include <odb/transaction.hxx>
#include <odb/mysql/database.hxx>

#include <QString>
#include <QDebug>


using namespace drkv;


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
	dbPort(port)
{
	db = NULL;
}


bool connection::establish( const QString & password )
{
	try
	{
		db = new odb::mysql::database( dbUser.toStdString(), password.toStdString(), dbDatabase.toStdString(), dbHost.toStdString(), dbPort );
		if( !db )
		{
			qCritical() << tr("Verbindung von \"%1\" zu Host\"%2:%3\" auf \"%4\" konnte nicht hergestellt werden!").arg(dbUser).arg(dbHost).arg(dbPort).arg(dbDatabase);
			return false;
		}
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


void connection::executeCreateUser( const Mitarbeiter & mitarbeiter, const QString & from, const QString & password )
{
	execute( "CREATE USER '"+mitarbeiter.login()+"'@'"+from+"' IDENTIFIED BY '"+password+"';" );
	switch( mitarbeiter.berechtigung() )
	{
		case Mitarbeiter::AdminRecht:
			execute( "GRANT ALL PRIVILEGES ON "+dbDatabase+".* TO '"+mitarbeiter.login()+"'@'"+from+"' WITH GRANT OPTION;" );
			break;
		case Mitarbeiter::WohnverbundRecht:
		case Mitarbeiter::WohnheimRecht:
		case Mitarbeiter::WohngruppenRecht:
			execute( "GRANT SELECT ON "+dbDatabase+".* TO '"+mitarbeiter.login()+"'@'"+from+"';" );
			break;
		default:
			break;
	}
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
