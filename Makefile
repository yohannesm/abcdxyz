VALGRIND ?= valgrind
DOXYGEN ?= doxygen
CC = g++
EXTRA_CPPFLAGS += -g -ggdb -ansi -pedantic -I/public/linux/include/boost-1_38 -Wall
TEST_LDFLAGS = -lcppunit -ldl
TEST_CPPFLAGS = -DTEST
EXECUTABLE = main.app
DOXYFILE = Doxyfile

all: clean docs $(EXECUTABLE) $(TEST_EXEC)

$(EXECUTABLE): main.cpp TestGraph.h Graph.h
	$(CC) $(EXTRA_CPPFLAGS) $(TEST_LDFLAGS) $(TEST_CPPFLAGS) $< -o $@

docs: $(DOXYFILE)
	doxygen Doxyfile >/dev/null 2>&1

clean:
	-rm -f $(EXECUTABLE) $(TEST_EXEC) html/*
	-rmdir html >/dev/null 2>&1

distclean: clean
	rm -f $(DOXYFILE)

$(DOXYFILE): Graph.h
	$(DOXYGEN) $@
