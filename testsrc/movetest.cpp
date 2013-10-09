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
	uint64_t bit = 1;

	cengine::Move m1("e3", "e4");

	CPPUNIT_ASSERT ( m1.get_from_bit() == bit<<20 );
	CPPUNIT_ASSERT ( m1.get_to_bit() == bit<<28 );

	cengine::Move m2("c5", "b3");

	CPPUNIT_ASSERT ( m2.get_from_bit() == bit<<34 );
	CPPUNIT_ASSERT ( m2.get_to_bit() == bit<<17 );

	cengine::Move m3("a1", "a2");

	CPPUNIT_ASSERT ( m3.get_from_bit() == bit );
	CPPUNIT_ASSERT ( m3.get_to_bit() == bit<<8 );
	
	cengine::Move m4("b1", "c3");

	CPPUNIT_ASSERT ( m4.get_from_bit() == bit<<1 );
	CPPUNIT_ASSERT ( m4.get_to_bit() == bit<<18 );

	cengine::Move m5(0x8, 0x800);
	CPPUNIT_ASSERT ( m5.get_from_coord() == "d1" );
	CPPUNIT_ASSERT ( m5.get_to_coord() == "d2" );

	cengine::Move m6(0x1, 0x100);
	CPPUNIT_ASSERT ( m6.get_from_coord() == "a1" );
	CPPUNIT_ASSERT ( m6.get_to_coord() == "a2" );
}
