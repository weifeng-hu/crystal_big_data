ROOT	= /home/wh288/iqs/
INCLUDE	= -I/$(ROOT) -I/home/wh288/intel/composerxe/mkl/include
CXX	= mpic++ -g
FORT	= gfortran -g
CSRCS	= ao2mo_main.cpp ao2mo_config.cpp
FOBJS	= $(ROOT)/matrix/EIGTQL2.o $(ROOT)/matrix/OEI_TRANSFORM.o $(ROOT)/matrix/TEI_TRANSFORM.o
COBJS	=$(CSRCS:.cpp=.o) $(ROOT)/matrix/read_integral.o $(ROOT)/matrix/general_matrix.o
PGM	= ao2mo
LIBS	= -lm -lgfortran -L/home/intel/composerxe/mkl/lib/intel64 -lmkl_intel_lp64 -lmkl_intel_thread -lmkl_core -lguide

$(PGM):	$(COBJS) $(FOBJS)
	$(CXX) -o $(PGM) $(INCLUDE) $(COBJS) $(FOBJS) $(LIBS)


ao2mo_main.o:	ao2mo_main.cpp
	$(CXX) -c $(INCLUDE) ao2mo_main.cpp

ao2mo_config.o:	ao2mo_config.cpp
	$(CXX) -c $(INCLUDE) ao2mo_config.cpp

clean:
	rm *.o; rm ao2mo
