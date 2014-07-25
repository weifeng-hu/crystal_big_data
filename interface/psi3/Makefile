SHELL = /bin/sh

INCLUDE = ../

HEAD_FILES = qcread.h

LIBS  = /home/intel/fce/10.1.021/lib/ -lifcore -L/home/intel/mkl/10.1.0.015/lib/em64t -lmkl_intel_lp64 -lmkl_intel_thread -lmkl_lapack -lmkl_core -liomp5 -lpthread -lm

CSRCS = qcread.cpp

COBJS = $(CSRCS:.cpp=.o)

FOBJS = $(FSRCS:.f=.o)

CXX   = icpc
FORT  = ifort

COPT  = -O2
FOPT  = -O2

qcread.o:	../psi3/qcread.h\
		../../tensor/tensor.h\
		../psi3/qcread.cpp
	$(CXX) $(COPT) -c -I$(INCLUDE) qcread.cpp
