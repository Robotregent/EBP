#ifndef DBCONNECTION_HXX
#define DBCONNECTION_HXX


#include "Mitarbeiter.hxx"

#include <QCoreApplication>
#include <QString>
#include <QList>

#include <odb/core.hxx>
#include <odb/database.hxx>
#include <odb/mysql/database.hxx>


namespace drkv
{
	class database : public odb::mysql::database
	{
		Q_DECLARE_TR_FUNCTIONS( database )

	public:
		database
		(
			const QString & user,
			const QString & password,
			const QString & database,
			const QString & host = "localhost",
			unsigned int port = 3306
		);

		unsigned long long execute( const QString & statement ) { return odb::database::execute( statement.toStdString() ); }

		void executeCreateUser( const Mitarbeiter & mitarbeiter, const QString & from, const QString & password );
		void executeCreateUser( const Mitarbeiter & mitarbeiter, const QString & password );
		void executeDropUser( const Mitarbeiter & mitarbeiter, const QString & from );
		void executeDropUser( const Mitarbeiter & mitarbeiter );
		void executeSetPassword( const Mitarbeiter & mitarbeiter, const QString & from, const QString & password );
		void executeSetPassword( const Mitarbeiter & mitarbeiter, const QString & password );

	private:
		QSharedPointer<Mitarbeiter> connectedUser;
	};
}


#endif // DBCONNECTION_HXX
