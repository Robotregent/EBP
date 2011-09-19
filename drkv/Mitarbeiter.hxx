#ifndef MITARBEITER_HXX
#define MITARBEITER_HXX


#include "Bewohner.hxx"
#include "Wohngruppe.hxx"
#include "Projekt.hxx"
#include "databaseObject.hxx"

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
	class connection;

	#pragma db object
	class Mitarbeiter : public databaseObject<Mitarbeiter>
	{
		Q_DECLARE_TR_FUNCTIONS( Mitarbeiter )

	public:
		enum Berechtigungen
		{
			AdminRecht,
			WohnverbundRecht,
			WohnheimRecht,
			WohngruppenRecht
		};

		Mitarbeiter
		(
			const QString & login,
			const Berechtigungen & berechtigung,
			const QString & name,
			const QString & email,
			const QString & telefon
		) :
			login_(login),
			berechtigung_(berechtigung),
			name_(name),
			email_(email),
			telefon_(telefon)
		{
		}

		const QString & login() const { return login_; }
//		void login( const QString & login ) { login_ = login; }		// don't change login names for existing objects - this will break the mapping to the database user

		const QString & name() const { return name_; }
		void name( const QString & name ) { name_ = name; }

		const Berechtigungen & berechtigung() const { return berechtigung_; }
		void berechtigung( const Berechtigungen & berechtigung ) { berechtigung_ = berechtigung; }

		const QString & email() const { return email_; }
		void email( const QString & email ) { email_ = email; }

		const QString & telefon() const { return telefon_; }
		void telefon( const QString & telefon ) { telefon_ = telefon; }

		QList< QSharedPointer<Wohngruppe> > loadWohngruppen( const QSharedPointer<drkv::connection> & connection ) const;
		DATABASEOBJECT_DECLARE_LINK_INVERSE( Mitarbeiter, Wohngruppe, Wohngruppe )

		QList< QSharedPointer<Projekt> > loadProjekte( const QSharedPointer<drkv::connection> & connection ) const;
		DATABASEOBJECT_DECLARE_LINK_INVERSE( Mitarbeiter, Projekt, Projekt )

		QList< QSharedPointer<Bewohner> > loadBezugsbetreuer( const QSharedPointer<drkv::connection> & connection ) const;
		DATABASEOBJECT_DECLARE_LINK( Mitarbeiter, Bezugsbetreuer, Bewohner )

		bool create( const QSharedPointer<drkv::connection> & connection, const QString & password );
		bool create( const QSharedPointer<drkv::connection> & connection );
		bool remove( const QSharedPointer<drkv::connection> & connection );
		bool updatePassword( const QSharedPointer<drkv::connection> & connection, const QString & password );

	private:
		friend class odb::access;
		friend class Wohngruppe;
		friend class Projekt;
		Mitarbeiter() {}

		#pragma db id auto
		unsigned long id_;

		#pragma db not_null type("VARCHAR(128)") options("UNIQUE")
		QString login_;

		Berechtigungen berechtigung_;

		QString name_;

		QString email_;

		QString telefon_;

		#pragma db unordered inverse(mitarbeiter_)
		QList< QLazyWeakPointer<Wohngruppe> > wohngruppen_;

		#pragma db unordered inverse(verantwortliche_)
		QList< QLazyWeakPointer<Projekt> > projekte_;

		#pragma db unordered
		QList< QLazyWeakPointer<Bewohner> > bezugsbetreuer_;
	};
}


#endif // MITARBEITER_HXX
