#ifndef MITARBEITER_HXX
#define MITARBEITER_HXX


#include "Wohngruppe.hxx"

#include <QCoreApplication>
#include <QString>
#include <QSharedPointer>

#include <odb/core.hxx>
#include <odb/qt/lazy-ptr.hxx>


namespace drkv
{
	class Wohngruppe;
	class database;

	#pragma db object
	class Mitarbeiter
	{
		Q_DECLARE_TR_FUNCTIONS( Mitarbeiter )
	public:
		Mitarbeiter
		(
			const QString & login,
			bool istBezugsbetreuer,
			QLazyWeakPointer<Wohngruppe> wohngruppe,
			const QString & name,
			const QString & email,
			const QString & telefon
		) :
			login_(login),
			istBezugsbetreuer_(istBezugsbetreuer),
			wohngruppe_(wohngruppe),
			name_(name),
			email_(email),
			telefon_(telefon)
		{
		}

		const QString & login() const { return login_; }
//		void login( QString login ) { login_ = login; }		// don't change login names for existing objects - this will break the mapping to the database user

		const bool istBezugsbetreuer() const { return istBezugsbetreuer_; }
		void istBezugsbetreuer( bool istBezugsbetreuer ) { istBezugsbetreuer_ = istBezugsbetreuer; }

		const QLazyWeakPointer<Wohngruppe> & wohngruppe() const { return wohngruppe_; }
		void wohngruppe( QLazyWeakPointer<Wohngruppe> wohngruppe ) { wohngruppe_ = wohngruppe; }

		const QString & name() const { return name_; }
		void name( QString name ) { name_ = name; }

		const QString & email() const { return email_; }
		void email( QString email ) { email_ = email; }

		const QString & telefon() const { return telefon_; }
		void telefon( QString telefon ) { telefon_ = telefon; }

		bool create( QSharedPointer<drkv::database> db, const QString & password );
		bool remove( QSharedPointer<drkv::database> db );
		bool update( QSharedPointer<drkv::database> db );
		bool updatePassword( QSharedPointer<drkv::database> db, const QString & password );
		static QList< QSharedPointer<Mitarbeiter> > getAll( QSharedPointer<drkv::database> db );

	private:
		friend class odb::access;
		Mitarbeiter() {}

		#pragma db id auto
		unsigned long id_;

		#pragma db not_null type("VARCHAR(128)") options("UNIQUE")
		QString login_;

		#pragma db not_null
		bool istBezugsbetreuer_;

		QLazyWeakPointer<Wohngruppe> wohngruppe_;

		QString name_;

		QString email_;

		QString telefon_;
	};
}


#endif // MITARBEITER_HXX
