#ifndef BEWOHNER_HXX
#define BEWOHNER_HXX


#include "Wohngruppe.hxx"
#include "Projekt.hxx"
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
	class Wohngruppe;
	class Projekt;
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

		const QSharedPointer<Mitarbeiter> & bezugsbetreuer( const QSharedPointer<drkv::connection> & connection ) const { return bezugsbetreuer_; }
		QSharedPointer<Mitarbeiter> & bezugsbetreuer( const QSharedPointer<drkv::connection> & connection ) { return bezugsbetreuer_; }
		DATABASEOBJECT_DECLARE_LINK_INVERSE( Bewohner, Bezugsbetreuer, Mitarbeiter )

		const QSharedPointer<Wohngruppe> & wohngruppe( const QSharedPointer<drkv::connection> & connection ) const { return wohngruppe_; }
		QSharedPointer<Wohngruppe> & wohngruppe( const QSharedPointer<drkv::connection> & connection ) { return wohngruppe_; }
		DATABASEOBJECT_DECLARE_LINK_INVERSE( Bewohner, Wohngruppe, Wohngruppe )

		QList< QSharedPointer<Projekt> > loadProjekte( const QSharedPointer<drkv::connection> & connection ) const;
		DATABASEOBJECT_DECLARE_LINK( Bewohner, Projekt, Projekt )

	private:
		friend class odb::access;
		friend class Mitarbeiter;
		friend class Wohngruppe;
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

		#pragma db inverse(bezugsbetreuer_)
		QSharedPointer<Mitarbeiter> bezugsbetreuer_;

		#pragma db inverse(bewohner_)
		QSharedPointer<Wohngruppe> wohngruppe_;

		#pragma db unordered
		QList< QLazyWeakPointer<Projekt> > projekte_;
	};
}


#endif // BEWOHNER_HXX
