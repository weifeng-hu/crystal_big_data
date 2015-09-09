IQUADS_ROOT     = /home/wh288/Development/iquads/
IQUADS_SRC      = $(IQUADS_ROOT)/src/
IQUADS_BIN      = $(IQUADS_ROOT)/bin/
CC              = gcc
CXX             = g++
COPT		= -g -std=c++11
CFLAGS          = -I$(IQUADS_SRC)
CHEADS          =
CSRCS           = main.cpp\
		  molpro_agent.cpp
COBJS           = $(CSRCS:.cpp=.o)
LIBS            =
PGM             = test_molpro_agent

$(PGM): $(COBJS)
	$(CXX) -o $(PGM) $(CFLAGS) $(COPT) $(COBJS) $(LIBS)
	cp $(PGM) $(IQUADS_BIN)

molpro_agent.o:
	$(CXX) -c $(CFLAGS) $(COPT) $(IQUADS_SRC)/interface_to_third_party/molpro_agent.cpp

main.o:
	$(CXX) -c $(CFLAGS) $(COPT) main.cpp

clean:
	rm *.o; rm $(PGM); rm $(IQUADS_BIN)/$(PGM)
