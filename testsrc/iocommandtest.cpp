#include "iocommandtest.h"
#include "../src/iocommand.h"

CPPUNIT_TEST_SUITE_REGISTRATION( IoCommandTest );

void IoCommandTest::test_move()
{
	cengine::IoCommand move1("e3e4"); // Move
	cengine::IoCommand move2("e3e4q"); // Pawn promotion
	cengine::IoCommand not_a_move("accepted variants");

	CPPUNIT_ASSERT ( move1.is_move() );
	CPPUNIT_ASSERT ( move2.is_move() );
	CPPUNIT_ASSERT ( !not_a_move.is_move() );
}
