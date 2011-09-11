#ifndef MITARBEITER_HXX
#define MITARBEITER_HXX


#include "Wohngruppe.hxx"

#include <QString>
#include <QSharedPointer>

#include <odb/core.hxx>
#include <odb/qt/lazy-ptr.hxx>


namespace drkv
{
	// forward declarations - in case of mutual inclusions
	class Wohngruppe;

	#pragma db object
	class Mitarbeiter
	{
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
		void login( QString login ) { login_ = login; }

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
