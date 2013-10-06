#include "boardutiltest.h"
#include "../src/move.h"
#include "../src/boardutil.h"
#include "../src/board.h"

CPPUNIT_TEST_SUITE_REGISTRATION ( BoardUtilTest );

void BoardUtilTest::test_move()
{
	using namespace cengine;

	Board b = BoardUtil::create_board();

	CPPUNIT_ASSERT ( b.white_knights == 0x42 );

	Move m("b1", "c3"); // Queen pawn to steps
	BoardUtil::perform_move(m, b);

	CPPUNIT_ASSERT ( b.white_knights == static_cast<int64_t>(0x40040) );
}
