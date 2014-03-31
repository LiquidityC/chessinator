#ifndef _ALGORITHM_TEST
#define _ALGORITHM_TEST

#include "genericfixture.h"

class AlgorithmTest : public GenericFixture
{
	public:

		CPPUNIT_TEST_SUITE( AlgorithmTest );
		CPPUNIT_TEST( test_check_mate );
		CPPUNIT_TEST_SUITE_END();

	public:

		void test_check_mate();

};

#endif
