#include <unistd.h>

#include "movegeneratortest.h"
#include "../src/movegenerator.h"
#include "../src/board.h"
#include "../src/boardutil.h"

CPPUNIT_TEST_SUITE_REGISTRATION( MoveGeneratorTest );

void MoveGeneratorTest::test_pawn()
{

	cengine::MoveGenerator generator;
	cengine::Board board = cengine::BoardUtil::create_board();

	generator.calculate_moves_for(board);
	int i = 0;
	for(auto it = generator.begin(); it != generator.end(); ++it) {
		i++;
	}
	// First move should have 20 outcomes.
	CPPUNIT_ASSERT( i == 20 );
}
