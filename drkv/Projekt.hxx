#ifndef PROJEKT_HXX
#define PROJEKT_HXX


#include "Mitarbeiter.hxx"
#include "Bewohner.hxx"
#include "databaseObject.hxx"

#include <QCoreApplication>
#include <QString>
#include <QList>
#include <QDate>
#include <QSharedPointer>

#include <odb/core.hxx>
#include <odb/qt/lazy-ptr.hxx>


namespace drkv
{
	class Mitarbeiter;
	class Bewohner;
	class connection;

	#pragma db object
	class Projekt : public databaseObject<Projekt>
	{
		Q_DECLARE_TR_FUNCTIONS( Projekt )

	public:
		Projekt
		(
			const QString & name,
			const QString & beschreibung,
			const QString & typ,
			const QDate & beginn,
			const QDate & ende,
			const QSharedPointer<Bewohner> & bewohner
		) :
			name_(name),
			beschreibung_(beschreibung),
			typ_(typ),
			beginn_(beginn),
			ende_(ende),
			bewohner_(bewohner)
		{
		}

		const QString & name() const { return name_; }
		void name( const QString & name ) { name_ = name; }

		const QString & beschreibung() const { return beschreibung_; }
		void beschreibung( const QString & beschreibung ) { beschreibung_ = beschreibung; }

		const QString & typ() const { return typ_; }
		void typ( const QString & typ ) { typ_ = typ; }

		const QDate & beginn() const { return beginn_; }
		void beginn( const QDate & beginn ) { beginn_ = beginn; }

		const QDate & ende() const { return ende_; }
		void ende( const QDate & ende ) { ende_ = ende; }

		const QSharedPointer<Bewohner> & bewohner( const QSharedPointer<drkv::connection> & connection ) const;
		QSharedPointer<Bewohner> & bewohner( const QSharedPointer<drkv::connection> & connection );
		DATABASEOBJECT_DECLARE_LINK_INVERSE( Projekt, Bewohner, Bewohner )

		QList< QSharedPointer<Mitarbeiter> > loadVerantwortliche( const QSharedPointer<drkv::connection> & connection ) const;
		DATABASEOBJECT_DECLARE_LINK( Projekt, Verantwortlicher, Mitarbeiter )

	private:
		friend class odb::access;
		friend class Bewohner;
		Projekt() {}

		#pragma db id auto
		unsigned long id_;

		QString name_;

		QString beschreibung_;

		QString typ_;

		QDate beginn_;

		QDate ende_;

		#pragma db inverse(projekte_)
		QSharedPointer<Bewohner> bewohner_;

		#pragma db unordered
		QList< QLazyWeakPointer<Mitarbeiter> > verantwortliche_;
	};
}


#endif // PROJEKT_HXX
