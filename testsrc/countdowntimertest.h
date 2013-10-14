#ifndef _COUNTDOWN_TIMER_TEST_H
#define _COUNTDOWN_TIMER_TEST_H

#include "genericfixture.h"

class CountdownTimerTest : public GenericFixture
{
	public:

		CPPUNIT_TEST_SUITE( CountdownTimerTest );
		CPPUNIT_TEST( test_timer );
		CPPUNIT_TEST_SUITE_END();

	public:

		void test_timer();

};

int countdownMockTime;

time_t countdownMockTimeFunction(time_t*);

#endif
