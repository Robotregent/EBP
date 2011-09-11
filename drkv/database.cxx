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


bool database::addUser( drkv::Mitarbeiter & mitarbeiter, QString password )
{
	if( mitarbeiter.login().isNull() || mitarbeiter.login()=="" )
	{
		qCritical() << tr("Kann keinen neuen Benutzer ohne Login-Namen erstellen");
		return false;
	}
	if( password.isNull() || password=="" )
	{
		qCritical() << tr("Kann keinen neuen Benutzer ohne Passwort erstellen");
		return false;
	}

	try
	{
		odb::transaction t( begin() );
		execute( "CREATE USER '"+mitarbeiter.login()+"'@'localhost' IDENTIFIED BY '"+password+"';" );
		execute( "CREATE USER '"+mitarbeiter.login()+"'@'%' IDENTIFIED BY '"+password+"';" );
		execute( "GRANT SELECT ON "+QString(db())+".* TO '"+mitarbeiter.login()+"'@'localhost';" );
		execute( "GRANT SELECT ON "+QString(db())+".* TO '"+mitarbeiter.login()+"'@'%';" );
		persist( mitarbeiter );
		t.commit();
	}
	catch( const odb::exception & e )
	{
		qCritical() << e.what();
		return false;
	}
	return true;
}
