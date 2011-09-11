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
		Q_DECLARE_TR_FUNCTIONS(database)
	public:
		database
		(
			QString user,
			QString password,
			QString database,
			QString host = "localhost",
			unsigned int port = 3306
		);

		unsigned long long execute( const QString & statement ) { return odb::database::execute( statement.toStdString() ); }

		bool addUser( drkv::Mitarbeiter & mitarbeiter, QString password );
		bool removeUser( drkv::Mitarbeiter & mitarbeiter );
		bool removeUser( const QString & login );
		QList< QSharedPointer<drkv::Mitarbeiter> > getUsers();

	private:
		void executeCreateUser( Mitarbeiter & mitarbeiter, const QString & from, const QString & password );
		void executeDropUser( Mitarbeiter & mitarbeiter, const QString & from );
	};
}


#endif // DBCONNECTION_HXX
