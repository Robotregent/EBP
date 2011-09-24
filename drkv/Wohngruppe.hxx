#ifndef WOHNGRUPPE_HXX
#define WOHNGRUPPE_HXX


#include "Mitarbeiter.hxx"
#include "Bewohner.hxx"
#include "Wohngruppenereignis.hxx"
#include "Wohnheim.hxx"
#include "databaseObject.hxx"

#include <QCoreApplication>
#include <QString>
#include <QList>
#include <QSharedPointer>

#include <odb/core.hxx>
#include <odb/qt/lazy-ptr.hxx>


namespace drkv
{
	class Mitarbeiter;
	class Bewohner;
	class Wohngruppenereignis;
	class Wohnheim;
	class connection;

	#pragma db object
	class Wohngruppe : public databaseObject<Wohngruppe>
	{
		Q_DECLARE_TR_FUNCTIONS( Wohngruppe )

	public:
		Wohngruppe
		(
			const QString & name
		) :
			name_(name)
		{
		}

		const QString & name() const { return name_; }
		QString & name() { return name_; }

		const QSharedPointer<Wohnheim> & wohnheim() const;
		DATABASEOBJECT_DECLARE_LINK( Wohngruppe, Wohnheim, Wohnheim )

		QList< QSharedPointer<Mitarbeiter> > loadMitarbeiter( const QSharedPointer<drkv::connection> & connection ) const;
		DATABASEOBJECT_DECLARE_LINK( Wohngruppe, Mitarbeiter, Mitarbeiter )

		QList< QSharedPointer<Bewohner> > loadBewohner( const QSharedPointer<drkv::connection> & connection ) const;
		DATABASEOBJECT_DECLARE_LINK_INVERSE( Wohngruppe, Bewohner, Bewohner )

		QList< QSharedPointer<Wohngruppenereignis> > loadEreignisse( const QSharedPointer<drkv::connection> & connection ) const;
		DATABASEOBJECT_DECLARE_LINK_INVERSE( Wohngruppe, Ereignis, Wohngruppenereignis )

	private:
		friend class odb::access;
		friend class Bewohner;
		friend class Wohngruppenereignis;
		Wohngruppe() {}

		#pragma db id auto
		unsigned long id_;

		QString name_;

		#pragma db unordered
		QSharedPointer<Wohnheim> wohnheim_;

		#pragma db unordered
		QList< QLazyWeakPointer<Mitarbeiter> > mitarbeiter_;

		#pragma db unordered inverse(wohngruppe_)
		QList< QLazyWeakPointer<Bewohner> > bewohner_;

		#pragma db unordered inverse(wohngruppe_)
		QList< QLazyWeakPointer<Wohngruppenereignis> > ereignisse_;
	};
}


#endif // WOHNGRUPPE_HXX
