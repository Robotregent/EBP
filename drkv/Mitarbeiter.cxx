#include "Mitarbeiter.hxx"
#include "Mitarbeiter-odb.hxx"
#include "database.hxx"

#include <QDebug>


using namespace drkv;


bool Mitarbeiter::create( const QSharedPointer<drkv::database> & db, const QString & password )
{
	if( login().isNull() || login()=="" )
	{
		qCritical() << tr("Kann keinen neuen Benutzer ohne Login-Namen erstellen.");
		return false;
	}
	if( password.isNull() || password=="" )
	{
		qCritical() << tr("Kann keinen neuen Benutzer ohne Passwort erstellen.");
		return false;
	}

	try
	{
		odb::transaction t( db->begin() );
		db->executeCreateUser( *this, password );
		db->persist( *this );
		t.commit();
	}
	catch( const odb::exception & e )
	{
		qCritical() << e.what();
		return false;
	}
	return true;
}


bool Mitarbeiter::remove( const QSharedPointer<drkv::database> & db )
{
	try
	{
		odb::transaction t( db->begin() );
		db->executeDropUser( *this );
		db->erase( *this );
		t.commit();
	}
	catch( const odb::exception & e )
	{
		qCritical() << e.what();
		return false;
	}
	return true;
}


bool Mitarbeiter::update( const QSharedPointer<drkv::database> & db )
{
	try
	{
		odb::transaction t( db->begin() );
		db->update( *this );
		t.commit();
	}
	catch( const odb::exception & e )
	{
		qCritical() << e.what();
		return false;
	}
	return true;
}


bool Mitarbeiter::updatePassword( const QSharedPointer<drkv::database> & db, const QString & password )
{
	try
	{
		odb::transaction t( db->begin() );
		db->executeSetPassword( *this, password );
		t.commit();
	}
	catch( const odb::exception & e )
	{
		qCritical() << e.what();
		return false;
	}
	return true;
}


QList< QSharedPointer<Mitarbeiter> > Mitarbeiter::getAll( const QSharedPointer<drkv::database> & db )
{
	QList< QSharedPointer<Mitarbeiter> > list;
	try
	{
		odb::transaction t( db->begin() );
		odb::result<Mitarbeiter> r( db->query<Mitarbeiter>() );
		for( odb::result<Mitarbeiter>::iterator i( r.begin() ); i != r.end(); ++i )
		{
			list.push_back( i.load() );
		}
		t.commit();
	}
	catch( const odb::exception & e )
	{
		qCritical() << e.what();
		return QList< QSharedPointer<Mitarbeiter> >();
	}
	return list;
}
