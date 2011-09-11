#ifndef DBCONNECTION_HXX
#define DBCONNECTION_HXX


#include "Mitarbeiter.hxx"

#include <QCoreApplication>
#include <QString>

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
		) :
			odb::mysql::database
			(
				user.toStdString(),
				password.toStdString(),
				database.toStdString(),
				host.toStdString(),
				port
			)
		{
		}

		unsigned long long execute( const QString & statement ) { return odb::database::execute( statement.toStdString() ); }

		bool addUser( drkv::Mitarbeiter & mitarbeiter, QString password );
	};
}


#endif // DBCONNECTION_HXX
