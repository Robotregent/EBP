#include <drkv/database.hxx>
#include <drkv/Mitarbeiter.hxx>

#include <iostream>


int main( int argc, char * argv[] )
{
	drkv::database db( "drk_admin", "drk_pass", "drk" );
	db.removeUser( "tester" );
	drkv::Mitarbeiter m( "tester", false, QLazyWeakPointer<drkv::Wohngruppe>(), "Mr. Test", "test@test.test", "01234567890" );
	db.addUser( m, "test" );
	db.getUsers();

	return 0;
}
