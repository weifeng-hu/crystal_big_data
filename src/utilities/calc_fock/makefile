ROOT	= /home/wh288/iqs/
INCLUDE	= -I/$(ROOT) -I/home/wh288/intel/composerxe/mkl/include
CXX	= mpic++ -g
FORT	= gfortran -g
CSRCS	= main.cpp
FOBJS	= $(ROOT)/matrix/EIGTQL2.o
COBJS	=$(CSRCS:.cpp=.o) $(ROOT)/matrix/read_integral.o $(ROOT)/matrix/general_matrix.o
PGM	= calc_fock
LIBS	= -lm -lgfortran -L/home/intel/composerxe/mkl/lib/intel64 -lmkl_intel_lp64 -lmkl_sequential -lmkl_core

$(PGM):	$(COBJS) $(FOBJS)
	$(CXX) -o $(PGM) $(INCLUDE) $(COBJS) $(FOBJS) $(LIBS)


main.o:	main.cpp
	$(CXX) -c $(INCLUDE) main.cpp
