#ifndef BEWOHNER_HXX
#define BEWOHNER_HXX


#include "Abwesenheit.hxx"
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
	class Abwesenheit;
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
			const unsigned long & nummer
		) :
			nummer_(nummer)
		{
		}

		static QList< QSharedPointer< Bewohner > > loadAll( const QSharedPointer<ebp::connection> & connection );

		const unsigned long & nummer() const { return nummer_; }
		void nummer( const unsigned long & nummer ) { nummer_ = nummer; }

		const QString & anrede() const { return anrede_; }
		void anrede( const QString & anrede ) { anrede_ = anrede; }

		const QString & vorname() const { return vorname_; }
		void vorname( const QString & vorname ) { vorname_ = vorname; }

		const QString & nachname() const { return nachname_; }
		void nachname( const QString & nachname ) { nachname_ = nachname; }

		const QString name() const;

		const QString & geburtsort() const { return geburtsort_; }
		void geburtsort( const QString & geburtsort ) { geburtsort_ = geburtsort; }

		const QDate & geburtsdatum() const { return geburtsdatum_; }
		void geburtsdatum( const QDate & geburtsdatum ) { geburtsdatum_ = geburtsdatum; }

		const QString & email() const { return email_; }
		void email( const QString & email ) { email_ = email; }

		const QString & telefon() const { return telefon_; }
		void telefon( const QString & telefon ) { telefon_ = telefon; }

		const QString & familienstatus() const { return familienstatus_; }
		void familienstatus( const QString & familienstatus ) { familienstatus_ = familienstatus; }

		const QString & konfession() const { return konfession_; }
		void konfession( const QString & konfession ) { konfession_ = konfession; }

		const QString & staat() const { return staat_; }
		void staat( const QString & staat ) { staat_ = staat; }

		const QDate & seit() const { return seit_; }
		void seit( const QDate & seit ) { seit_ = seit; }

		const QString & anmerkung() const { return anmerkung_; }
		void anmerkung( const QString & anmerkung ) { anmerkung_ = anmerkung; }

		const QSharedPointer<Wohngruppe> & wohngruppe() const { return wohngruppe_; }
		DATABASEOBJECT_DECLARE_LINK( Bewohner, Wohngruppe, Wohngruppe )

		const QSharedPointer<Mitarbeiter> & bezugsbetreuer() const { return bezugsbetreuer_; }
		DATABASEOBJECT_DECLARE_LINK( Bewohner, Bezugsbetreuer, Mitarbeiter )

//		QList< QSharedPointer<Projekt> > loadProjekte( const QSharedPointer<ebp::connection> & connection ) const;
		DATABASEOBJECT_DECLARE_LOAD( Projekte, Projekt )
		DATABASEOBJECT_DECLARE_LINK_INVERSE( Bewohner, Projekt, Projekt )

//		QList< QSharedPointer<Protokoll> > loadProtokolle( const QSharedPointer<ebp::connection> & connection ) const;
		DATABASEOBJECT_DECLARE_LOAD( Protokolle, Protokoll )
		DATABASEOBJECT_DECLARE_LINK_INVERSE( Bewohner, Protokoll, Protokoll )

//		QList< QSharedPointer<Bewohnerereignis> > loadEreignisse( const QSharedPointer<ebp::connection> & connection ) const;
		DATABASEOBJECT_DECLARE_LOAD( Ereignisse, Bewohnerereignis )
		DATABASEOBJECT_DECLARE_LINK_INVERSE( Bewohner, Ereignis, Bewohnerereignis )

		DATABASEOBJECT_DECLARE_LOAD( Abwesenheiten, Abwesenheit )
		DATABASEOBJECT_DECLARE_LINK_INVERSE( Bewohner, Abwesenheit, Abwesenheit )

	private:
		friend class odb::access;
		friend class Projekt;
		friend class Protokoll;
		friend class Bewohnerereignis;
		friend class Abwesenheit;
		Bewohner() {}

		#pragma db id auto
		unsigned long id_;

		#pragma db not_null options("UNIQUE")
		unsigned long nummer_;

		QString anrede_;

		QString vorname_;

		QString nachname_;

		QString geburtsort_;

		QDate geburtsdatum_;

		QString krankenkasse_;

		QString email_;

		QString telefon_;

		QString familienstatus_;

		QString konfession_;

		QString staat_;

		QDate seit_;

		QString anmerkung_;

		QSharedPointer<Wohngruppe> wohngruppe_;

		QSharedPointer<Mitarbeiter> bezugsbetreuer_;

		#pragma db unordered inverse(bewohner_)
		QList< QLazyWeakPointer<Projekt> > projekte_;

		#pragma db unordered inverse(bewohner_)
		QList< QLazyWeakPointer<Protokoll> > protokolle_;

		#pragma db unordered inverse(bewohner_)
		QList< QLazyWeakPointer<Bewohnerereignis> > ereignisse_;

		#pragma db unordered inverse(bewohner_)
		QList< QLazyWeakPointer<Abwesenheit> > abwesenheiten_;
	};
}


#endif // BEWOHNER_HXX
