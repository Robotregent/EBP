#include <drkv/DBConnection.hxx>
#include <drkv/Mitarbeiter.hxx>

#include <odb/database.hxx>
#include <odb/session.hxx>
#include <odb/transaction.hxx>

#include <iostream>


int main( int argc, char * argv[] )
{
	try
	{
		drkv::DBConnection db( "drk_admin", "drk_pass", "drk" );
		drkv::Mitarbeiter m( "tester", "Mr. Test", "test@test.test", "01234567890" );
		db.addMitarbeiter( m );
	}
	catch( const odb::exception& e )
	{
		std::cerr << e.what () << std::endl;
		return 1;
	}
	return 0;
}
