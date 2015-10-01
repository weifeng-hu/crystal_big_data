IQUADS_ROOT     = /home/wh288/Development/iquads/
IQUADS_SRC      = $(IQUADS_ROOT)/src/
IQUADS_BIN      = $(IQUADS_ROOT)/bin/
CC              = gcc
CXX             = g++
COPT		= -g -std=c++11
CFLAGS          = -I$(IQUADS_SRC)
CHEADS          =
CSRCS           =\
		request.cpp\
		report.cpp\
		agent.cpp\
		client.cpp\
		main.cpp
COBJS           = $(CSRCS:.cpp=.o)
LIBS            = -lboost_date_time
PGM             = test

$(PGM): $(COBJS)
	$(CXX) -o $(PGM) $(CFLAGS) $(COPT) $(COBJS) $(LIBS)
	cp $(PGM) $(IQUADS_BIN)

main.o: ../*.hpp
	$(CXX) -c $(CFLAGS) $(COPT) main.cpp

request.o: ../*.hpp
	$(CXX) -c $(CFLAGS) $(COPT) ../request.cpp

report.o: ../*.hpp
	$(CXX) -c $(CFLAGS) $(COPT) ../report.cpp

agent.o: ../*.hpp
	$(CXX) -c $(CFLAGS) $(COPT) ../agent.cpp

client.o: ../*.hpp
	$(CXX) -c $(CFLAGS) $(COPT) ../client.cpp

clean:
	rm *.o; rm $(PGM); rm $(IQUADS_BIN)/$(PGM)
