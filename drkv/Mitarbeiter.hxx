#ifndef MITARBEITER_HXX
#define MITARBEITER_HXX


#include "Wohngruppe.hxx"

#include <QString>
#include <QSharedPointer>

#include <odb/core.hxx>


namespace drkv
{
	#pragma db object
	class Mitarbeiter
	{
		public:
			Mitarbeiter( const QString & login,
					bool istBezugsbetreuer,
					QSharedPointer<Wohngruppe> wohngruppe,
					const QString & name,
					const QString & email,
					const QString & telefon )
				: login_(login),
					istBezugsbetreuer_(istBezugsbetreuer),
					wohngruppe_(wohngruppe),
					name_(name),
					email_(email),
					telefon_(telefon)
			{
			}

			const bool istBezugsbetreuer() const { return istBezugsbetreuer_; }
			void istBezugsbetreuer( bool istBezugsbetreuer ) { istBezugsbetreuer_ = istBezugsbetreuer; }

			const QSharedPointer<Wohngruppe> & wohngruppe() const { return wohngruppe_; }
			void wohngruppe( QSharedPointer<Wohngruppe> wohngruppe ) { wohngruppe_ = wohngruppe; }

			const QString & name() const { return name_; }
			void name( QString name ) { name_ = name; }

			const QString & email() const { return email_; }
			void email( QString email ) { email_ = email; }

			const QString & telefon() const { return telefon_; }
			void telefon( QString telefon ) { telefon_ = telefon; }

		private:
			Mitarbeiter() {}
			friend class odb::access;

			#pragma db id auto
			unsigned long id_;

			#pragma db not_null
			QString login_;

			#pragma db not_null
			bool istBezugsbetreuer_;

			QSharedPointer<Wohngruppe> wohngruppe_;

			QString name_;

			QString email_;

			QString telefon_;
	};
}


#endif // MITARBEITER_HXX
