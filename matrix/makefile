DEBUG := YES

CXX	= mpic++ 
FC	= gfortran -g
HEADS	= square_matrix.h general_matrix.h functions.h mo_coeff.h one_electron_integral.h two_electron_integral.h\
	  compressed_matrix.h
CSRCS	= general_matrix.cpp square_matrix.cpp transform.cpp functions.cpp two_electron_integral.cpp read_integral.cpp\
	  compressed_matrix.cpp
FSRCS	= OEI_TRANSFORM.f EIGTQL2.f TEI_TRANSFORM.f
COBJS	= $(CSRCS:.cpp=.o)
FOBJS	= $(FSRCS:.f=.o)
INCLUDE	= -I../ -I./ -I/home/intel/composerxe/mkl/include
AR	= libmatrix.a
LIBS	= -L/home/intel/composerxe/mkl/lib/intel64 -lmkl_intel_lp64 -lmkl_sequential -lmkl_core

ifeq ($(DEBUG), YES)
  CFLAG =	-g  -DUSE_DBG
else
  CFLAG =
endif


$(AR):	$(COBJS) $(FOBJS)
	ar -r  $(AR) $(COBJS) $(FOBJS)

compressed_matrix.o:	compressed_matrix.cpp compressed_matrix.h
	$(CXX) -c $(CFLAG) $(INCLUDE) compressed_matrix.cpp

general_matrix.o:	general_matrix.h general_matrix.cpp
	$(CXX) -c $(CFLAG) $(INCLUDE) general_matrix.cpp

square_matrix.o:	square_matrix.h	square_matrix.cpp
	$(CXX) -c $(CFLAG) $(INCLUDE) square_matrix.cpp

functions.o:		general_matrix.h functions.h functions.cpp
	$(CXX) -c $(CFLAG) $(INCLUDE) functions.cpp

two_electron_integral.o: two_electron_integral.h two_electron_integral.cpp
	$(CXX) -c $(CFLAG) $(INCLUDE) two_electron_integral.cpp

read_integral.o:	two_electron_integral.h read_integral.cpp
	$(CXX) -c $(CFLAG) $(INCLUDE) read_integral.cpp

OEI_TRANSFORM.o:	OEI_TRANSFORM.f
	$(FC) -c OEI_TRANSFORM.f

EIGTQL2.o:	EIGTQL2.f
	$(FC) -c EIGTQL2.f

transform.o:	square_matrix.h	transform.cpp
	$(CXX) -c $(CFLAG) $(INCLUDE) transform.cpp

clean:
	rm *.o; rm libmatrix.a
