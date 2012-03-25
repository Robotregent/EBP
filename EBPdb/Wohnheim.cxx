#include "Wohnheim.hxx"
#include "Wohnheim-odb.hxx"
#include "Wohngruppe-odb.hxx"
#include "connection.hxx"

#include <QDebug>


#include "databaseObject.ixx"
template class ebp::databaseObject<ebp::Wohnheim>;


using namespace ebp;


DATABASEOBJECT_IMPLEMENT_LINK_INVERSE( Wohnheim, Wohngruppe, Wohngruppe, Wohnheim )


DATABASEOBJECT_IMPLEMENT_LOAD( Wohnheim, Wohngruppen, Wohngruppe, wohngruppen_ )


/*
QList< QSharedPointer<Wohngruppe> > Wohnheim::loadWohngruppen( const QSharedPointer<ebp::connection> & connection ) const
{
	QList< QSharedPointer<Wohngruppe> > ret;
	odb::transaction t( connection->getDB()->begin() );
	for( QList< QLazyWeakPointer<Wohngruppe> >::const_iterator i = wohngruppen_.begin(); i != wohngruppen_.end(); ++i )
	{
		ret.push_back( (*i).load() );
	}
	t.commit();
	return ret;
}
*/


bool Wohnheim::hasPermission( const QSharedPointer<ebp::connection> & connection ) const
{
	return true;
}
