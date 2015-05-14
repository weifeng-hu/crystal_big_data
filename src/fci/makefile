SHELL = /bin/sh

INCLUDE = fullci.h\

CSRCS = fullci.cpp\

COBJS = $(CSRCS:.cpp=.o)

#CXX = mpiicpc
CXX = mpic++

PGM = fullci

FLIBS = -lmkl -lguide -lmkl_lapack -lpthread

$(PGM) : $(COBJS) ; $(CXX) -o $(PGM) $(COBJS) $(FLIBS)

.SUFFIXES: .cpp  .o

.cpp.o:
	$(CXX) -c -O3  $<
