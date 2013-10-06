#ifndef _IO_COMMAND_TEST_H
#define _IO_COMMAND_TEST_H

#include "genericfixture.h"

class IoCommandTest : public GenericFixture
{

	public:

		CPPUNIT_TEST_SUITE( IoCommandTest );
		CPPUNIT_TEST( test_move );
		CPPUNIT_TEST_SUITE_END();

	public:
		void setUp() { };
		void tearDown() { };

		void test_move();
};

#endif
