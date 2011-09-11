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
	QString user,
	QString password,
	QString database,
	QString host,
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
}


void database::executeCreateUser( Mitarbeiter & mitarbeiter, const QString & from, const QString & password )
{
	execute( "CREATE USER '"+mitarbeiter.login()+"'@'"+from+"' IDENTIFIED BY '"+password+"';" );
	execute( "GRANT SELECT ON "+QString(db())+".* TO '"+mitarbeiter.login()+"'@'"+from+"';" );
}


void database::executeDropUser( Mitarbeiter & mitarbeiter, const QString & from )
{
	execute( "DROP USER '"+mitarbeiter.login()+"'@'"+from+"';" );
}


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
		executeCreateUser( mitarbeiter, "localhost", password );
		executeCreateUser( mitarbeiter, "%", password );
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


bool database::removeUser( drkv::Mitarbeiter & mitarbeiter )
{
	try
	{
		odb::transaction t( begin() );
		executeDropUser( mitarbeiter, "localhost" );
		executeDropUser( mitarbeiter, "%" );
		erase( mitarbeiter );
		t.commit();
	}
	catch( const odb::exception & e )
	{
		qCritical() << e.what();
		return false;
	}
	return true;
}


bool database::removeUser( const QString & login )
{
	try
	{
		odb::transaction t( begin() );
		odb::result<Mitarbeiter> r( query<Mitarbeiter>( odb::query<Mitarbeiter>::login == odb::query<Mitarbeiter>::_ref(login) ) );
		for( odb::result<Mitarbeiter>::iterator i( r.begin() ); i != r.end(); ++i )
		{
			executeDropUser( *i, "localhost" );
			executeDropUser( *i, "%" );
			erase( *i );
		}
		t.commit();
	}
	catch( const odb::exception & e )
	{
		qCritical() << e.what();
		return false;
	}
	return true;
}


QList< QSharedPointer<drkv::Mitarbeiter> > database::getUsers()
{
	QList< QSharedPointer<drkv::Mitarbeiter> > list;
	try
	{
		odb::transaction t( begin() );
		odb::result<Mitarbeiter> r( query<Mitarbeiter>() );
		for( odb::result<Mitarbeiter>::iterator i( r.begin() ); i != r.end(); ++i )
		{
			qDebug() << i->login();
			list.push_back( i.load() );
		}
		t.commit();
	}
	catch( const odb::exception & e )
	{
		qCritical() << e.what();
		return QList< QSharedPointer<drkv::Mitarbeiter> >();
	}
	return list;
}
