#include "countdowntimertest.h"
#include "../src/countdowntimer.h"

CPPUNIT_TEST_SUITE_REGISTRATION( CountdownTimerTest );

void CountdownTimerTest::test_timer()
{
	countdownMockTime = 0;
	cengine::CountdownTimer timer(countdownMockTimeFunction);
	timer.set_time(3);

	timer.start();
	CPPUNIT_ASSERT ( timer.time_remaining() == 3 );

	countdownMockTime += 1;
	
	CPPUNIT_ASSERT ( timer.time_remaining() < 3 );
	CPPUNIT_ASSERT ( timer.time_remaining() > 0 );
}

time_t countdownMockTimeFunction(time_t* timer)
{
	*timer = countdownMockTime;
	return countdownMockTime;
}
