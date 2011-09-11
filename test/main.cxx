#include <drkv/database.hxx>
#include <drkv/Mitarbeiter.hxx>

#include <iostream>


int main( int argc, char * argv[] )
{
	try
	{
		drkv::database db( "drk_admin", "drk_pass", "drk" );
		drkv::Mitarbeiter m( "tester", false, QLazyWeakPointer<drkv::Wohngruppe>(), "Mr. Test", "test@test.test", "01234567890" );
		db.addUser( m, "test" );
	}
	catch( const odb::exception& e )
	{
		std::cerr << e.what () << std::endl;
		return 1;
	}
	return 0;
}
