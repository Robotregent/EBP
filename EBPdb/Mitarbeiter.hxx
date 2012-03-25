#ifndef MITARBEITER_HXX
#define MITARBEITER_HXX


#include "Bewohner.hxx"
#include "Bewohnerereignis.hxx"
#include "Wohngruppe.hxx"
#include "Wohngruppenereignis.hxx"
#include "Projekt.hxx"
#include "Protokoll.hxx"
#include "databaseObject.hxx"

#include <QCoreApplication>
#include <QString>
#include <QList>
#include <QSharedPointer>

#include <odb/core.hxx>
#include <odb/qt/lazy-ptr.hxx>


namespace ebp
{
	class Wohngruppe;
	class Wohngruppenereignis;
	class Bewohner;
	class Bewohnerereignis;
	class Projekt;
	class Protokoll;
	class connection;

	#pragma db object
	class Mitarbeiter : public databaseObject<Mitarbeiter>
	{
		Q_DECLARE_TR_FUNCTIONS( Mitarbeiter )

	public:
		/// Zugangsberechtigungen
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

		bool hasPermission( const QSharedPointer<ebp::connection> & connection ) const;

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

//		QList< QSharedPointer<Wohngruppe> > loadWohngruppen( const QSharedPointer<ebp::connection> & connection ) const;
		DATABASEOBJECT_DECLARE_LOAD( Wohngruppen, Wohngruppe )
		DATABASEOBJECT_DECLARE_LINK_INVERSE( Mitarbeiter, Wohngruppe, Wohngruppe )

//		QList< QSharedPointer<Projekt> > loadProjekte( const QSharedPointer<ebp::connection> & connection ) const;
		DATABASEOBJECT_DECLARE_LOAD( Projekte, Projekt )
		DATABASEOBJECT_DECLARE_LINK_INVERSE( Mitarbeiter, Projekt, Projekt )

//		QList< QSharedPointer<Bewohnerereignis> > loadBewohnerereignisse( const QSharedPointer<ebp::connection> & connection ) const;
		DATABASEOBJECT_DECLARE_LOAD( Bewohnerereignisse, Bewohnerereignis )
		DATABASEOBJECT_DECLARE_LINK_INVERSE( Mitarbeiter, Bewohnerereignis, Bewohnerereignis )

//		QList< QSharedPointer<Wohngruppenereignis> > loadWohngruppenereignisse( const QSharedPointer<ebp::connection> & connection ) const;
		DATABASEOBJECT_DECLARE_LOAD( Wohngruppenereignisse, Wohngruppenereignis )
		DATABASEOBJECT_DECLARE_LINK_INVERSE( Mitarbeiter, Wohngruppenereignis, Wohngruppenereignis )

//		QList< QSharedPointer<Protokoll> > loadProtokollTeilnehmer( const QSharedPointer<ebp::connection> & connection ) const;
		DATABASEOBJECT_DECLARE_LOAD( ProtokollTeilnehmer, Protokoll )
		DATABASEOBJECT_DECLARE_LINK_INVERSE( Mitarbeiter, ProtokollTeilnehmer, Protokoll )

//		QList< QSharedPointer<Protokoll> > loadProtokollSchreiber( const QSharedPointer<ebp::connection> & connection ) const;
		DATABASEOBJECT_DECLARE_LOAD( ProtokollSchreiber, Protokoll )
		DATABASEOBJECT_DECLARE_LINK_INVERSE( Mitarbeiter, ProtokollSchreiber, Protokoll )

//		QList< QSharedPointer<Bewohner> > loadBezugsbetreuer( const QSharedPointer<ebp::connection> & connection ) const;
		DATABASEOBJECT_DECLARE_LOAD( Bezugsbetreuer, Bewohner )
		DATABASEOBJECT_DECLARE_LINK_INVERSE( Mitarbeiter, Bezugsbetreuer, Bewohner )

		bool create( const QSharedPointer<ebp::connection> & connection, const QString & password );
		bool create( const QSharedPointer<ebp::connection> & connection );
		bool remove( const QSharedPointer<ebp::connection> & connection );
		bool updatePassword( const QSharedPointer<ebp::connection> & connection, const QString & password );

	private:
		friend class odb::access;
		friend class Wohngruppe;
		friend class Wohngruppenereignis;
		friend class Bewohner;
		friend class Bewohnerereignis;
		friend class Projekt;
		friend class Protokoll;
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

		#pragma db unordered inverse(schreiber_)
		QList< QLazyWeakPointer<Bewohnerereignis> > bewohnerereignisse_;

		#pragma db unordered inverse(schreiber_)
		QList< QLazyWeakPointer<Wohngruppenereignis> > wohngruppenereignisse_;

		#pragma db unordered inverse(teilnehmer_)
		QList< QLazyWeakPointer<Protokoll> > protokollTeilnehmer_;

		#pragma db unordered inverse(schreiber_)
		QList< QLazyWeakPointer<Protokoll> > protokollSchreiber_;

		#pragma db unordered inverse(bezugsbetreuer_)
		QList< QLazyWeakPointer<Bewohner> > bezugsbetreuer_;
	};
}


#endif // MITARBEITER_HXX
