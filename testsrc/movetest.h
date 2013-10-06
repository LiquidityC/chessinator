#ifndef _MOVE_TEST_H
#define _MOVE_TEST_H

#include "genericfixture.h"

class MoveTest : public GenericFixture
{
	public:

		CPPUNIT_TEST_SUITE( MoveTest );
		CPPUNIT_TEST( test_coordinates );
		CPPUNIT_TEST( test_coordinate_conversion );
		CPPUNIT_TEST_SUITE_END();

	public:

		void test_coordinates();

		void test_coordinate_conversion();
};

#endif
