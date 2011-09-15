#ifndef BEWOHNER_HXX
#define BEWOHNER_HXX


#include "Wohngruppe.hxx"
#include "Projekt.hxx"

#include <QCoreApplication>
#include <QString>
#include <QList>
#include <QDate>
#include <QSharedPointer>

#include <odb/core.hxx>
#include <odb/qt/lazy-ptr.hxx>


namespace drkv
{
	class Wohngruppe;
	class Projekt;
	class database;

	#pragma db object
	class Bewohner
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
			const QString & telefon,
			const QLazyWeakPointer<Mitarbeiter> & bezugsbetreuer,
			const QLazyWeakPointer<Wohngruppe> & wohngruppe,
			const QList< QLazyWeakPointer<Projekt> > & projekte
		) :
			nummer_(nummer),
			name_(name),
			geburtsdatum_(geburtsdatum),
			krankenkasse_(krankenkasse),
			email_(email),
			telefon_(telefon),
			bezugsbetreuer_(bezugsbetreuer),
			wohngruppe_(wohngruppe),
			projekte_(projekte)
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

		const QLazyWeakPointer<Mitarbeiter> & bezugsbetreuer() const { return bezugsbetreuer_; }
		void bezugsbetreuer( const QLazyWeakPointer<Mitarbeiter> & bezugsbetreuer ) { bezugsbetreuer_ = bezugsbetreuer; }

		const QLazyWeakPointer<Wohngruppe> & wohngruppe() const { return wohngruppe_; }
		void wohngruppe( const QLazyWeakPointer<Wohngruppe> & wohngruppe ) { wohngruppe_ = wohngruppe; }

		const QList< QLazyWeakPointer<Projekt> > & projekte() const { return projekte_; }
		void projekte( const QList< QLazyWeakPointer<Projekt> > & projekte ) { projekte_ = projekte; }

		bool create( const QSharedPointer<drkv::database> & db );
		bool remove( const QSharedPointer<drkv::database> & db );
		bool update( const QSharedPointer<drkv::database> & db );
		static QList< QSharedPointer<Bewohner> > getAll( const QSharedPointer<drkv::database> & db );

	private:
		friend class odb::access;
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

		QLazyWeakPointer<Mitarbeiter> bezugsbetreuer_;

		#pragma db inverse(bewohner_)
		QLazyWeakPointer<Wohngruppe> wohngruppe_;

		#pragma db unordered inverse(bewohner_)
		QList< QLazyWeakPointer<Projekt> > projekte_;
	};
}


#endif // BEWOHNER_HXX
