#include "Wohnheim.hxx"
#include "Wohnheim-odb.hxx"
#include "Wohngruppe-odb.hxx"
#include "connection.hxx"

#include <QDebug>


#include "databaseObject.ixx"
template class drkv::databaseObject<drkv::Wohnheim>;


using namespace drkv;


DATABASEOBJECT_IMPLEMENT_LINK_INVERSE( Wohnheim, Wohngruppe, Wohngruppe, Wohnheim )


QList< QSharedPointer<Wohngruppe> > Wohnheim::loadWohngruppen( const QSharedPointer<drkv::connection> & connection ) const
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
