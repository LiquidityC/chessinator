#ifndef _IO_COMMAND_TEST_H
#define _IO_COMMAND_TEST_H

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestFixture.h>

namespace cengine {
	class IoCommand;
}

class IoCommandTest : public CppUnit::TestFixture
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
