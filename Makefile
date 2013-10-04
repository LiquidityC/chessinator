ifdef CLANG
CC 			= clang++
else
CC			= g++
endif

CFLAGS		= -c -g -pedantic -Wall -Wpointer-arith -Wcast-qual
LD			= g++
LDFLAGS 	= 
AR			= ar
ARFLAGS		= rcs
RM			= rm
CP			= cp
ECHO		= echo -e
SHELL		= /bin/sh
CTAGS		= ctags

LIBS 				= 
COMMON_SOURCEFILES	= chess.cpp iocommunicator.cpp move.cpp iocommand.cpp \
					  commandhandler.cpp

DEPS				= 
EXECUTABLE 			= chess
PROG_SOURCEFILES	= $(COMMON_SOURCEFILES)
PROG_SOURCES 		= $(addprefix src/, $(PROG_SOURCEFILES))
PROG_OBJECTS 		= $(PROG_SOURCES:.cpp=.o)

TEST				= testtanks
TEST_SOURCEFILES	= $(COMMON_SOURCEFILES) 
TEST_SOURCEFILES	+= 
TEST_SOURCES 		= $(addprefix src/, $(TEST_SOURCEFILES))
TEST_OBJECTS		= $(TEST_SOURCES:.cpp=.o)

default: all

all: $(EXECUTABLE)

$(EXECUTABLE): $(PROG_OBJECTS) $(DEPS)
	$(LD) $(LDFLAGS) $(LIBS) -o $@ $(PROG_OBJECTS)

check: $(TEST)
	./$(TEST)

$(TEST): $(TEST_OBJECTS) $(DEPS)
	$(LD) $(LDFLAGS) -lcppunit $(LIBS) -o $@ $(TEST_OBJECTS)

.cpp.o:
	$(CC) $(INCLUDE) $(CFLAGS) $< -o $@

clean:
	$(RM) -f $(EXECUTABLE) $(TEST) $(PROG_OBJECTS) $(TEST_OBJECTS)
