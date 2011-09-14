#ifndef MITARBEITER_HXX
#define MITARBEITER_HXX


#include "Wohngruppe.hxx"
#include "Projekt.hxx"

#include <QCoreApplication>
#include <QString>
#include <QList>
#include <QSharedPointer>

#include <odb/core.hxx>
#include <odb/qt/lazy-ptr.hxx>


namespace drkv
{
	class Wohngruppe;
	class Projekt;
	class database;

	#pragma db object
	class Mitarbeiter
	{
		Q_DECLARE_TR_FUNCTIONS( Mitarbeiter )

	public:
		Mitarbeiter
		(
			const QString & login,
			const QString & name,
			const QString & email,
			const QString & telefon,
			QList< QLazyWeakPointer<Wohngruppe> > wohngruppen,
			QList< QLazyWeakPointer<Projekt> > projekte,
			QLazyWeakPointer<Wohngruppe> bezugsbetreuer
		) :
			login_(login),
			name_(name),
			email_(email),
			telefon_(telefon),
			wohngruppen_(wohngruppen),
			projekte_(projekte),
			bezugsbetreuer_(bezugsbetreuer)
		{
		}

		const QString & login() const { return login_; }
//		void login( const QString & login ) { login_ = login; }		// don't change login names for existing objects - this will break the mapping to the database user

		const QString & name() const { return name_; }
		void name( const QString & name ) { name_ = name; }

		const QString & email() const { return email_; }
		void email( const QString & email ) { email_ = email; }

		const QString & telefon() const { return telefon_; }
		void telefon( const QString & telefon ) { telefon_ = telefon; }

		const QList< QLazyWeakPointer<Wohngruppe> > & wohngruppen() const { return wohngruppen_; }
		void wohngruppen( QList< QLazyWeakPointer<Wohngruppe> > & wohngruppen ) { wohngruppen_ = wohngruppen; }

		const QList< QLazyWeakPointer<Projekt> > & projekte() const { return projekte_; }
		void projekte( QList< QLazyWeakPointer<Projekt> > & projekte ) { projekte_ = projekte; }

		const QLazyWeakPointer<Wohngruppe> & bezugsbetreuer() const { return bezugsbetreuer_; }
		void bezugsbetreuer( QLazyWeakPointer<Wohngruppe> & wohngruppe ) { bezugsbetreuer_ = wohngruppe; }

		bool create( const QSharedPointer<drkv::database> & db, const QString & password );
		bool remove( const QSharedPointer<drkv::database> & db );
		bool update( const QSharedPointer<drkv::database> & db );
		bool updatePassword( const QSharedPointer<drkv::database> & db, const QString & password );
		static QList< QSharedPointer<Mitarbeiter> > getAll( const QSharedPointer<drkv::database> & db );

	private:
		friend class odb::access;
		Mitarbeiter() {}

		#pragma db id auto
		unsigned long id_;

		#pragma db not_null type("VARCHAR(128)") options("UNIQUE")
		QString login_;

		QString name_;

		QString email_;

		QString telefon_;

		#pragma db unordered inverse(mitarbeiter_)
		QList< QLazyWeakPointer<Wohngruppe> > wohngruppen_;

		#pragma db unordered inverse(verantwortliche_)
		QList< QLazyWeakPointer<Projekt> > projekte_;

		#pragma db inverse(bezugsbetreuer_)
		QLazyWeakPointer<Wohngruppe> bezugsbetreuer_;
	};
}


#endif // MITARBEITER_HXX
