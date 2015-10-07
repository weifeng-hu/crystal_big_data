IQUADS_ROOT     = /home/wh288/Development/iquads/
IQUADS_SRC      = $(IQUADS_ROOT)/src/
IQUADS_BIN      = $(IQUADS_ROOT)/bin/
CC              = gcc
CXX             = g++
COPT		= -g -std=c++11
CFLAGS          = -I$(IQUADS_SRC)
CHEADS          =
CSRCS           = ./main.cpp\
		 ../client.cpp
COBJS           = $(CSRCS:.cpp=.o)
LIBS            =
PGM             = test

$(PGM): $(COBJS)
	$(CXX) -o $(PGM) $(CFLAGS) $(COPT) $(COBJS) $(LIBS); cp $(PGM) $(IQUADS_BIN)

main.o: ../*.hpp ./main.cpp
	$(CXX) -c $(CFLAGS) $(COPT) ./main.cpp

../client.o: ../*.hpp ../client.cpp
	$(CXX) -o ../client.o -c $(CFLAGS) $(COPT) ../client.cpp

clean:
	rm *.o; rm $(PGM); rm $(IQUADS_BIN)/$(PGM)
