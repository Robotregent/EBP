#include "database.hxx"
#include "Mitarbeiter-odb.hxx"

#include <odb/core.hxx>
#include <odb/database.hxx>
#include <odb/session.hxx>
#include <odb/transaction.hxx>
#include <odb/mysql/database.hxx>

#include <QString>
#include <QDebug>


using namespace drkv;


database::database
(
	const QString & user,
	const QString & password,
	const QString & database,
	const QString & host,
	unsigned int port
) :
	odb::mysql::database
	(
		user.toStdString(),
		password.toStdString(),
		database.toStdString(),
		host.toStdString(),
		port
	)
{
	try
	{
		odb::transaction t( begin() );
		odb::result<Mitarbeiter> r( query<Mitarbeiter>( odb::query<Mitarbeiter>::login == odb::query<Mitarbeiter>::_ref(user) ) );
		if( r.begin() != r.end() )
			connectedUser = QSharedPointer<Mitarbeiter>( r.begin().load() );
		else
			qWarning() << tr("Der verwendete Datenbankbenutzer ist nicht als Mitarbeiter registriert.");
		t.commit();
	}
	catch( const odb::exception & e )
	{
		qCritical() << e.what();
	}
}


void database::executeCreateUser( const Mitarbeiter & mitarbeiter, const QString & from, const QString & password )
{
	execute( "CREATE USER '"+mitarbeiter.login()+"'@'"+from+"' IDENTIFIED BY '"+password+"';" );
	switch( mitarbeiter.berechtigung() )
	{
		case Mitarbeiter::AdminRecht:
			execute( "GRANT ALL PRIVILEGES ON "+QString(db())+".* TO '"+mitarbeiter.login()+"'@'"+from+"' WITH GRANT OPTION;" );
			break;
		case Mitarbeiter::WohnverbundRecht:
		case Mitarbeiter::WohnheimRecht:
		case Mitarbeiter::WohngruppenRecht:
			execute( "GRANT SELECT ON "+QString(db())+".* TO '"+mitarbeiter.login()+"'@'"+from+"';" );
		default:
			break;
	}
}


void database::executeCreateUser( const Mitarbeiter & mitarbeiter, const QString & password )
{
	executeCreateUser( mitarbeiter, "localhost", password );
	executeCreateUser( mitarbeiter, "%", password );
}


void database::executeDropUser( const Mitarbeiter & mitarbeiter, const QString & from )
{
	execute( "DROP USER '"+mitarbeiter.login()+"'@'"+from+"';" );
}


void database::executeDropUser( const Mitarbeiter & mitarbeiter )
{
	executeDropUser( mitarbeiter, "localhost" );
	executeDropUser( mitarbeiter, "%" );
}


void database::executeSetPassword( const Mitarbeiter & mitarbeiter, const QString & from, const QString & password )
{
	// if the current user should be updated, don't use the FOR clause, so everyone can set its own password
	if( QString( user() ) == mitarbeiter.login() )
		execute( "SET PASSWORD = PASSWORD('"+password+"');" );
	else
		execute( "SET PASSWORD FOR '"+mitarbeiter.login()+"'@'"+from+"' = PASSWORD('"+password+"');" );
}


void database::executeSetPassword( const Mitarbeiter & mitarbeiter, const QString & password )
{
	executeSetPassword( mitarbeiter, "localhost", password );
	executeSetPassword( mitarbeiter, "%", password );
}
