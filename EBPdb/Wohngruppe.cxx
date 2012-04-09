#include "Wohngruppe.hxx"
#include "Wohngruppe-odb.hxx"
#include "Wohngruppenereignis-odb.hxx"
#include "Mitarbeiter-odb.hxx"
#include "connection.hxx"

#include <QDebug>


#include "databaseObject.ixx"
template class ebp::databaseObject<ebp::Wohngruppe>;


using namespace ebp;


DATABASEOBJECT_IMPLEMENT_LINK_ONEMANY( Wohngruppe, Wohnheim, wohnheim_, Wohnheim, Wohngruppe, wohngruppen_ )
DATABASEOBJECT_IMPLEMENT_LINK_MANYMANY( Wohngruppe, Mitarbeiter, mitarbeiter_, Mitarbeiter, Wohngruppe, wohngruppen_ )
DATABASEOBJECT_IMPLEMENT_LINK_INVERSE( Wohngruppe, Bewohner, Bewohner, Wohngruppe )
DATABASEOBJECT_IMPLEMENT_LINK_INVERSE( Wohngruppe, Ereignis, Wohngruppenereignis, Wohngruppe )


DATABASEOBJECT_IMPLEMENT_LOAD( Wohngruppe, Mitarbeiter, Mitarbeiter, mitarbeiter_ )
DATABASEOBJECT_IMPLEMENT_LOAD( Wohngruppe, Bewohner, Bewohner, bewohner_ )
DATABASEOBJECT_IMPLEMENT_LOAD( Wohngruppe, Ereignisse, Wohngruppenereignis, ereignisse_ )


bool Wohngruppe::hasPermission( const QSharedPointer<ebp::connection> & connection ) const
{
	if( connection->mitarbeiter() )
	{	// benutzer ist registriert
		switch( connection->mitarbeiter()->berechtigung() )
		{
			case Mitarbeiter::WohngruppenRecht:
				{	// benutzer mit wohngruppenrecht dürfen nur auf die ihnen zugeordneten wohngruppen zugreifen
				/*
					QList< QSharedPointer < Wohngruppe > > wgs = connection->mitarbeiter()->loadWohngruppen( connection );
					foreach( QSharedPointer < Wohngruppe > wg, wgs )
					{
						if( wg->id_ == id_ )
						{
							return true;
						}
					}
					return false;
				*/
					for( QList< QLazyWeakPointer<Wohngruppe> >::const_iterator i = connection->mitarbeiter()->wohngruppen_.begin(); i != connection->mitarbeiter()->wohngruppen_.end(); ++i )
					{
						if( (*i).objectId<Wohngruppe>() == id_ )
						{
							return true;
						}
					}
					return false;
				}
				break;
			default:	// alle anderen dürfen
				return true;
		}
	}
	else
	{
		return true;	// kein registrierter benutzer - üblicherweise root
	}
}

/*
QList< QSharedPointer<Mitarbeiter> > Wohngruppe::loadMitarbeiter( const QSharedPointer<ebp::connection> & connection ) const
{
	QList< QSharedPointer<Mitarbeiter> > ret;
	odb::transaction t( connection->getDB()->begin() );
	for( QList< QLazyWeakPointer<Mitarbeiter> >::const_iterator i = mitarbeiter_.begin(); i != mitarbeiter_.end(); ++i )
	{
		ret.push_back( (*i).load() );
	}
	t.commit();
	return ret;
}


QList< QSharedPointer<Bewohner> >  Wohngruppe::loadBewohner( const QSharedPointer<ebp::connection> & connection ) const
{
	QList< QSharedPointer<Bewohner> > ret;

	if( !hasPermission( connection ) )
	{
		qWarning() << tr("Zugriff auf Bewohner der Wohngruppe \"%1\" verweigert.").arg(name_);
		return ret;
	}

	odb::transaction t( connection->getDB()->begin() );
	for( QList< QLazyWeakPointer<Bewohner> >::const_iterator i = bewohner_.begin(); i != bewohner_.end(); ++i )
	{
		ret.push_back( (*i).load() );
	}
	t.commit();
	return ret;
}


QList< QSharedPointer<Wohngruppenereignis> > Wohngruppe::loadEreignisse( const QSharedPointer<ebp::connection> & connection ) const
{
	QList< QSharedPointer<Wohngruppenereignis> > ret;

	if( !hasPermission( connection ) )
	{
		qWarning() << tr("Zugriff auf Ereignisse der Wohngruppe \"%1\" verweigert.").arg(name_);
		return ret;
	}

	odb::transaction t( connection->getDB()->begin() );
	for( QList< QLazyWeakPointer<Wohngruppenereignis> >::const_iterator i = ereignisse_.begin(); i != ereignisse_.end(); ++i )
	{
		ret.push_back( (*i).load() );
	}
	t.commit();
	return ret;
}
*/