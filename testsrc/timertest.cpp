#include <unistd.h>

#include "timertest.h"
#include "../src/timer.h"

CPPUNIT_TEST_SUITE_REGISTRATION( TimerTest );

void TimerTest::test_timer()
{
	cengine::Timer t;

	CPPUNIT_ASSERT ( !t.is_started() );
	CPPUNIT_ASSERT ( !t.is_paused() );
	CPPUNIT_ASSERT ( t.get_time() == 0 );

	t.start();

	CPPUNIT_ASSERT ( t.is_started() );

	sleep(1);
	t.pause();

	CPPUNIT_ASSERT ( t.get_time() > 0 );
	CPPUNIT_ASSERT ( t.is_started() );
	CPPUNIT_ASSERT ( t.is_paused() );

	unsigned int pause_time = t.get_time();
	sleep(1);

	CPPUNIT_ASSERT ( pause_time == t.get_time() );

	t.unpause();
	sleep(1);

	CPPUNIT_ASSERT ( !t.is_paused() );
	CPPUNIT_ASSERT ( pause_time < t.get_time() );

	t.stop();

	CPPUNIT_ASSERT ( !t.is_started() );
	CPPUNIT_ASSERT ( !t.is_paused() );
	CPPUNIT_ASSERT ( t.get_time() == 0 );
}
