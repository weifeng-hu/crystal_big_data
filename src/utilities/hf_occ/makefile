SHELL	= /bin/sh
CXX	= g++ -std=c++11
CSRCS	= reorder.cpp
COBJS	= $(CSRCS:.cpp=.o)
PGM	= hf_occ

$(PGM):	$(COBJS)
	$(CXX) -o $(PGM) $(COBJS)

.SUFFIXES: .cpp .o

.c.o:
	$(Cxx) -c $(COBJS) >$
