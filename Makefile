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

OBJDIR				= obj
DEPS				= 
EXECUTABLE 			= chess
PROG_SOURCES 		= $(wildcard src/*.cpp)
PROG_OBJECTS 		= $(addprefix $(OBJDIR)/,$(notdir $(PROG_SOURCES:.cpp=.o)))

TEST				= test
TEST_SOURCES 		= $(filter-out src/chess.cpp,$(wildcard src/*.cpp)) $(wildcard testsrc/*.cpp)
TEST_OBJECTS 		= $(addprefix $(OBJDIR)/,$(notdir $(TEST_SOURCES:.cpp=.o)))

default: all

all: $(EXECUTABLE)

$(EXECUTABLE): $(PROG_OBJECTS) $(DEPS)
	$(LD) $(LDFLAGS) $(LIBS) -o $@ $^

check: $(TEST)
	./$(TEST)

$(TEST): $(TEST_OBJECTS) $(DEPS)
	$(LD) $(LDFLAGS) -lcppunit $(LIBS) -o $@ $(TEST_OBJECTS)

$(OBJDIR)/%.o: src/%.cpp
	$(CC) $(INCLUDE) $(CFLAGS) -c -o $@ $<

$(OBJDIR)/%.o: testsrc/%.cpp
	$(CC) $(INCLUDE) $(CFLAGS) -c -o $@ $<

$(PROG_OBJECTS): $(OBJDIR)

$(OBJDIR):
	mkdir $(OBJDIR)

clean:
	$(RM) -f $(EXECUTABLE) $(TEST) $(PROG_OBJECTS) $(TEST_OBJECTS)
