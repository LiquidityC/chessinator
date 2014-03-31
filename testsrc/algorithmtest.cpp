#include "algorithmtest.h"
#include "testutil.h"

#include "../src/algorithm.h"
#include "../src/move.h"

CPPUNIT_TEST_SUITE_REGISTRATION( AlgorithmTest );

void AlgorithmTest::test_check_mate()
{
	cengine::Board board = TestUtil::load_board("res/testcheckmate.txt");
	cengine::Algorithm algorithm;
	cengine::Move* m = algorithm.get_move(board);

	CPPUNIT_ASSERT( m == NULL );

	if (m != NULL) {
		delete m;
	}
}
