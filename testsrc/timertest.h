#ifndef _TIMER_TEST_H
#define _TIMER_TEST_H

#include "genericfixture.h"

namespace cengine {
	class Timer;
}

class TimerTest : public GenericFixture
{
	public:

		CPPUNIT_TEST_SUITE( TimerTest );
		CPPUNIT_TEST( test_timer );
		CPPUNIT_TEST_SUITE_END();

	public:
		void test_timer();
};

#endif
