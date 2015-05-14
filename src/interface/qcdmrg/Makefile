SHELL = /bin/sh

INCLUDE = ./

HEAD_FILES = cmd_options.h\
	     ../../ithaca/cmd_options.h

LIBS  = /home/intel/fce/10.1.021/lib/ -lifcore -L/home/intel/mkl/10.1.0.015/lib/em64t -lmkl_intel_lp64 -lmkl_intel_thread -lmkl_lapack -lmkl_core -liomp5 -lpthread -lm

CSRCS = cmd_options.cpp qcdmrg.cpp

COBJS = $(CSRCS:.cpp=.o)

FOBJS = $(FSRCS:.f=.o)

CXX   = icpc
FORT  = ifort

COPT  = -O2
FOPT  = -O2

PGM   = qcdmrg

$(PGM):	$(HEAD_FILES) $(COBJS)
	$(CXX) $(COPT) -o $(PGM) -I$(INCLUDE) ../../ithaca/cmd_options.o $(COBJS) -L$(LIBS)

cmd_options.o:	../qcdmrg/cmd_options.h\
		../../ithaca/cmd_options.h\
		../../ithaca/cmd_options.cpp\
		../qcdmrg/cmd_options.cpp
	$(CXX) $(COPT) -c -I$(INCLUDE) cmd_options.cpp

qcdmrg.o:	../qcdmrg/cmd_options.h\
		../../ithaca/cmd_options.h\
		../../ithaca/cmd_options.cpp\
		../qcdmrg/qcdmrg.cpp
	$(CXX) $(COPT) -c -I$(INCLUDE) qcdmrg.cpp
