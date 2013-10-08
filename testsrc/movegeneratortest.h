#ifndef _MOVE_GENERATOR_TEST_H
#define _MOVE_GENERATOR_TEST_H

#include "genericfixture.h"

class MoveGeneratorTest : public GenericFixture
{
	public:

		CPPUNIT_TEST_SUITE( MoveGeneratorTest );
		CPPUNIT_TEST( test_pawn );
		CPPUNIT_TEST_SUITE_END();

	public:

		void test_pawn();
};

#endif
