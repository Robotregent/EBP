#ifndef MITARBEITER_HXX
#define MITARBEITER_HXX


#include <QString>

#include <odb/core.hxx>


namespace drkv
{
	#pragma db object
	class Mitarbeiter
	{
		public:
			Mitarbeiter( const QString & login, const QString & name, const QString & email, const QString & telefon)
				: login_(login), name_(name), email_(email), telefon_(telefon)
			{
			}

			const QString & name() const { return name_; }
			const QString & email() const { return email_; }
			const QString & telefon() const { return telefon_; }
			void name( QString name ) { name_ = name; }
			void email( QString email ) { email_ = email; }
			void telefon( QString telefon ) { telefon_ = telefon; }

		private:
			Mitarbeiter() {}
			friend class odb::access;

			#pragma db id auto
			unsigned long id_;

			#pragma db not_null
			QString login_;

			QString name_;

			QString email_;
			QString telefon_;
	};
}


#endif // MITARBEITER_HXX
