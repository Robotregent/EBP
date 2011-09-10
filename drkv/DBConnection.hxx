#ifndef DBCONNECTION_HXX
#define DBCONNECTION_HXX


#include "Mitarbeiter.hxx"

#include <QString>

#include <odb/core.hxx>


namespace drkv
{
	class DBConnection
	{
	private:
		odb::database * db;
		
	public:
		DBConnection( QString user, QString password, QString database, QString host="localhost", unsigned int port=3306 );
		bool addMitarbeiter( Mitarbeiter m );
	};
}


#endif // DBCONNECTION_HXX
