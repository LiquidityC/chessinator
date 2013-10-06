#include "movetest.h"
#include "../src/move.h"

CPPUNIT_TEST_SUITE_REGISTRATION( MoveTest );

void MoveTest::test_coordinates()
{
	cengine::Move m("e3", "e4");

	CPPUNIT_ASSERT ( m.get_from_coord() == "e3" );
	CPPUNIT_ASSERT ( m.get_to_coord() == "e4" );
}

void MoveTest::test_coordinate_conversion()
{
	int64_t bit = 1;

	cengine::Move m1("e3", "e4");

	CPPUNIT_ASSERT ( m1.get_from_bit() == bit<<21 );
	CPPUNIT_ASSERT ( m1.get_to_bit() == bit<<29 );

	cengine::Move m2("c5", "b3");

	CPPUNIT_ASSERT ( m2.get_from_bit() == bit<<35 );
	CPPUNIT_ASSERT ( m2.get_to_bit() == bit<<18 );
}
