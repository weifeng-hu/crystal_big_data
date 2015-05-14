SHELL = /bin/sh

PGM_DIR = /home/wh288/iquads/

INCLUDE = ../

HEAD_FILES = $(PGM_DIR)/iquads/cmd_options.h

LIBS  = /home/intel/fce/10.1.021/lib/ -lifcore -L/home/intel/mkl/10.1.0.015/lib/em64t -lmkl_intel_lp64 -lmkl_intel_thread -lmkl_lapack -lmkl_core -liomp5 -lpthread -lm

CSRCS = cmd_options.cpp iquads.cpp

COBJS = $(CSRCS:.cpp=.o)

FOBJS = $(FSRCS:.f=.o)

CXX   = icpc
FORT  = ifort

COPT  = -O2
FOPT  = -O2

PGM   = iquads

$(PGM):	$(HEAD_FILES) $(COBJS) $(FOBJS)
	$(CXX) $(COPT) -o $(PGM) -I$(INCLUDE) $(COBJS) $(FOBJS) -L$(LIBS)


cmd_options.o:	../iquads/cmd_options.h\
		../iquads/cmd_options.cpp
	$(CXX) $(COPT) -c -I$(INCLUDE) cmd_options.cpp

iquads.o:	../iquads/cmd_options.h
	$(CXX) $(COPT) -c -I$(INCLUDE) iquads.cpp
