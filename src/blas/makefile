SHELL	= /bin/sh
CXX	= g++
FC	= gfortran
CXXFLAGS= -O3
FCFLAGS = -O3
CSRCS	= blas_interface.cpp
COBJS	= $(CSRCS:.cpp=.o)
FSRCS	= mat_x_mat.f symdiag.f ax_b.f
FOBJS	= $(FSRCS:.f=.o)
HEAD	= blas_interface.h
INCLUDE = -I./ -I/home/intel/composerxe/mkl/include
AR	= lib_blas_interface.a

$(AR):	$(COBJS) $(FOBJS)
	ar -r $(AR) $(COBJS) $(FOBJS)

.SUFFIXES: .cpp .f .o

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $<

.f.o:
	$(FC) -c $(FCFLAGS) $<

clean:
	rm *.o; rm lib_blas_interface.a
