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
	odb::transaction t( connection->getDB()->begin() );
	for( QList< QLazyWeakPointer<Wohngruppenereignis> >::const_iterator i = ereignisse_.begin(); i != ereignisse_.end(); ++i )
	{
		ret.push_back( (*i).load() );
	}
	t.commit();
	return ret;
}
