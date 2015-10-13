IQUADS_ROOT	= /home/wh288/Development/iquads
IQUADS_SRC	= $(IQUADS_ROOT)/src/
IQUADS_BIN	= $(IQUADS_ROOT)/bin/
CC		= gcc
CXX		= g++
CFLAGS		= -g -std=c++11 -I$(IQUADS_SRC)
CHEADS		= element.hpp\
		  element_list.hpp
CSRCS		= \
		  main.cpp
COBJS		= $(CSRCS:.cpp=.o)
LIBS		=
PGM		= test_element

$(PGM):	$(COBJS)
	$(CXX) -o $(PGM) $(CFLAGS) $(COPT) $(COBJS) $(LIBS)
	cp $(PGM) $(IQUADS_BIN)

main.o: main.cpp
	$(CXX) -c $(CFLAGS) main.cpp

clean:
	rm *.o; rm $(PGM)
