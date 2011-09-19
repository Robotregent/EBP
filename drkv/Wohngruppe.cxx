#include "Wohngruppe.hxx"
#include "Wohngruppe-odb.hxx"
#include "Mitarbeiter-odb.hxx"
#include "connection.hxx"

#include <QDebug>


#include "databaseObject.ixx"
template class drkv::databaseObject<drkv::Wohngruppe>;


using namespace drkv;


DATABASEOBJECT_IMPLEMENT_LINK_MANYTOMANY( Wohngruppe, Mitarbeiter, mitarbeiter_, Mitarbeiter, Wohngruppe, wohngruppen_ )
DATABASEOBJECT_IMPLEMENT_LINK_MANYTOONE( Wohngruppe, Bewohner, bewohner_, Bewohner, Wohngruppe, wohngruppe_ )


QList< QSharedPointer<Mitarbeiter> > Wohngruppe::loadMitarbeiter( const QSharedPointer<drkv::connection> & connection ) const
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
