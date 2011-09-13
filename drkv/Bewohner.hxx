#ifndef BEWOHNER_HXX
#define BEWOHNER_HXX


#include "Wohngruppe.hxx"

#include <QCoreApplication>
#include <QString>
#include <QDate>
#include <QSharedPointer>

#include <odb/core.hxx>
#include <odb/qt/lazy-ptr.hxx>


namespace drkv
{
	class Wohngruppe;
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
			const QString & krankenkasse,
			const QString & email,
			const QString & telefon,
			const QLazyWeakPointer<Wohngruppe> & wohngruppe
		) :
			nummer_(nummer),
			name_(name),
			krankenkasse_(krankenkasse),
			email_(email),
			telefon_(telefon),
			wohngruppe_(wohngruppe)
		{
		}

		const unsigned long & nummer() const { return nummer_; }
		void nummer( const unsigned long & nummer ) { nummer_ = nummer; }

		const QString & name() const { return name_; }
		void name( const QString & name ) { name_ = name; }

		const QString & email() const { return email_; }
		void email( const QString & email ) { email_ = email; }

		const QString & telefon() const { return telefon_; }
		void telefon( const QString & telefon ) { telefon_ = telefon; }

		const QLazyWeakPointer<Wohngruppe> & wohngruppe() const { return wohngruppe_; }
		void wohngruppe( const QLazyWeakPointer<Wohngruppe> & wohngruppe ) { wohngruppe_ = wohngruppe; }

		bool create( QSharedPointer<drkv::database> db );
		bool remove( QSharedPointer<drkv::database> db );
		bool update( QSharedPointer<drkv::database> db );

	private:
		friend class odb::access;
		Bewohner() {}

		#pragma db id auto
		unsigned long id_;

		#pragma db not_null options("UNIQUE")
		unsigned long nummer_;

		QDate geburtsdatum_;

		QString name_;

		QString krankenkasse_;

		QString email_;

		QString telefon_;

		QLazyWeakPointer<Wohngruppe> wohngruppe_;
	};
}


#endif // BEWOHNER_HXX
