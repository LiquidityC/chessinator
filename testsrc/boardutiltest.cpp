#include "boardutiltest.h"
#include "../src/move.h"
#include "../src/boardutil.h"
#include "../src/board.h"

CPPUNIT_TEST_SUITE_REGISTRATION ( BoardUtilTest );

void BoardUtilTest::test_move()
{
	using namespace cengine;

	Board b = BoardUtil::create_board();

	CPPUNIT_ASSERT ( b.units[WHITE_KNIGHTS] == 0x42 );

	Move m("b1", "c3"); // Queen pawn to steps
	BoardUtil::perform_move(m, b);

	CPPUNIT_ASSERT ( b.units[WHITE_KNIGHTS] == static_cast<int64_t>(0x40040) );
}

void BoardUtilTest::test_take()
{
	using namespace cengine;

	Board b = BoardUtil::create_board();

	CPPUNIT_ASSERT (b.units[WHITE_QUEEN] == 0x8);

	Move m("d1", "d2"); // Queen pawn to steps
	BoardUtil::perform_move(m, b);

	CPPUNIT_ASSERT (b.units[WHITE_QUEEN] == 0x800);
	CPPUNIT_ASSERT (b.units[WHITE_PAWNS] == 0xF700);
}
