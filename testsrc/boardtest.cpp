#include "boardtest.h"
#include "../src/move.h"
#include "../src/board.h"

CPPUNIT_TEST_SUITE_REGISTRATION ( BoardTest );

void BoardTest::test_move()
{
	using namespace cengine;

	Board b;

	CPPUNIT_ASSERT ( b.get_pieces_for(WHITE_KNIGHTS) == 0x42 );

	Move m1("b1", "c3"); // Knight moves out right
	b.perform_move(m1);

	CPPUNIT_ASSERT ( b.get_pieces_for(WHITE_KNIGHTS) == static_cast<int64_t>(0x40040) );

	b = Board();

	Move m2("a1", "a3"); // Left rook forward three
	b.perform_move(m2);

	CPPUNIT_ASSERT ( b.get_pieces_for(WHITE_ROOKS) == static_cast<int64_t>(0x10080) );
	CPPUNIT_ASSERT ( !b.is_white_long_castling_available() );
}

void BoardTest::test_castling_move()
{
	using namespace cengine;

	Board b;

	Move c1("e1", "c1"); // Castling move

	CPPUNIT_ASSERT ( b.is_whites_turn() );

	b.perform_move(c1);

	CPPUNIT_ASSERT ( b.get_pieces_for(WHITE_ROOKS) & static_cast<int64_t>(0x8) );
	CPPUNIT_ASSERT ( b.get_pieces_for(WHITE_KING) & static_cast<int64_t>(0x4) );
	CPPUNIT_ASSERT ( !b.is_white_long_castling_available() );
	CPPUNIT_ASSERT ( !b.is_whites_turn() );

	b = Board();

	Move c2("e1", "g1"); // Castling move
	b.perform_move(c2);

	CPPUNIT_ASSERT ( b.get_pieces_for(WHITE_ROOKS) & static_cast<int64_t>(0x20) );
	CPPUNIT_ASSERT ( b.get_pieces_for(WHITE_KING) & static_cast<int64_t>(0x40) );
	CPPUNIT_ASSERT ( !b.is_white_short_castling_available() );
}

void BoardTest::test_take()
{
	using namespace cengine;

	Board b;

	CPPUNIT_ASSERT (b.get_pieces_for(WHITE_QUEEN) == 0x8);

	Move m("d1", "d2"); // White queen takes white pawn
	b.perform_move(m);

	CPPUNIT_ASSERT (b.get_pieces_for(WHITE_QUEEN) == 0x800);
	CPPUNIT_ASSERT (b.get_pieces_for(WHITE_PAWNS) == 0xF700);
}

void BoardTest::test_totals()
{
	using namespace cengine;

	Board b;

	CPPUNIT_ASSERT ( b.get_pieces_for(ALL_WHITE_PIECES) == 0xFFFF );
	CPPUNIT_ASSERT ( b.get_pieces_for(ALL_BLACK_PIECES) == static_cast<uint64_t>(0xFFFF)<<48 );

	Move m("d1", "d2"); // White queen takes white pawn
	b.perform_move(m);

	CPPUNIT_ASSERT ( b.get_pieces_for(ALL_WHITE_PIECES) == 0xFFF7 );
	CPPUNIT_ASSERT ( b.get_pieces_for(ALL_BLACK_PIECES) == static_cast<uint64_t>(0xFFFF)<<48 );
}
