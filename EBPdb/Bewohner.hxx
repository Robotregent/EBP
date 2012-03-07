#ifndef BEWOHNER_HXX
#define BEWOHNER_HXX


#include "Bewohnerereignis.hxx"
#include "Wohngruppe.hxx"
#include "Projekt.hxx"
#include "Protokoll.hxx"
#include "databaseObject.hxx"

#include <QCoreApplication>
#include <QString>
#include <QList>
#include <QDate>
#include <QSharedPointer>

#include <odb/core.hxx>
#include <odb/qt/lazy-ptr.hxx>


namespace ebp
{
	class Bewohnerereignis;
	class Wohngruppe;
	class Projekt;
	class Protokoll;
	class connection;

	#pragma db object
	class Bewohner : public databaseObject<Bewohner>
	{
		Q_DECLARE_TR_FUNCTIONS( Bewohner )

	public:
		Bewohner
		(
			const unsigned long & nummer,
			const QString & name,
			const QDate & geburtsdatum,
			const QString & krankenkasse,
			const QString & email,
			const QString & telefon
		) :
			nummer_(nummer),
			name_(name),
			geburtsdatum_(geburtsdatum),
			krankenkasse_(krankenkasse),
			email_(email),
			telefon_(telefon)
		{
		}

		const unsigned long & nummer() const { return nummer_; }
		void nummer( const unsigned long & nummer ) { nummer_ = nummer; }

		const QString & name() const { return name_; }
		void name( const QString & name ) { name_ = name; }

		const QDate & geburtsdatum() const { return geburtsdatum_; }
		void geburtsdatum( const QDate & geburtsdatum ) { geburtsdatum_ = geburtsdatum; }

		const QString & email() const { return email_; }
		void email( const QString & email ) { email_ = email; }

		const QString & telefon() const { return telefon_; }
		void telefon( const QString & telefon ) { telefon_ = telefon; }

		const QSharedPointer<Wohngruppe> & wohngruppe() const { return wohngruppe_; }
		DATABASEOBJECT_DECLARE_LINK( Bewohner, Wohngruppe, Wohngruppe )

		const QSharedPointer<Mitarbeiter> & bezugsbetreuer() const { return bezugsbetreuer_; }
		DATABASEOBJECT_DECLARE_LINK( Bewohner, Bezugsbetreuer, Mitarbeiter )

//		QList< QSharedPointer<Projekt> > loadProjekte( const QSharedPointer<ebp::connection> & connection ) const;
		DATABASEOBJECT_DECLARE_LOAD( Projekte, Projekt )
		DATABASEOBJECT_DECLARE_LINK( Bewohner, Projekt, Projekt )

//		QList< QSharedPointer<Protokoll> > loadProtokolle( const QSharedPointer<ebp::connection> & connection ) const;
		DATABASEOBJECT_DECLARE_LOAD( Protokolle, Protokoll )
		DATABASEOBJECT_DECLARE_LINK( Bewohner, Protokoll, Protokoll )

//		QList< QSharedPointer<Bewohnerereignis> > loadEreignisse( const QSharedPointer<ebp::connection> & connection ) const;
		DATABASEOBJECT_DECLARE_LOAD( Ereignisse, Bewohnerereignis )
		DATABASEOBJECT_DECLARE_LINK( Bewohner, Ereignis, Bewohnerereignis )

	private:
		friend class odb::access;
		friend class Projekt;
		friend class Protokoll;
		friend class Bewohnerereignis;
		Bewohner() {}

		#pragma db id auto
		unsigned long id_;

		#pragma db not_null options("UNIQUE")
		unsigned long nummer_;

		QString name_;

		QDate geburtsdatum_;

		QString krankenkasse_;

		QString email_;

		QString telefon_;

		QSharedPointer<Wohngruppe> wohngruppe_;

		QSharedPointer<Mitarbeiter> bezugsbetreuer_;

		#pragma db unordered inverse(bewohner_)
		QList< QLazyWeakPointer<Projekt> > projekte_;

		#pragma db unordered inverse(bewohner_)
		QList< QLazyWeakPointer<Protokoll> > protokolle_;

		#pragma db unordered inverse(bewohner_)
		QList< QLazyWeakPointer<Bewohnerereignis> > ereignisse_;
	};
}


#endif // BEWOHNER_HXX
