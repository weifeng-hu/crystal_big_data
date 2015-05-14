SHELL	= /bin/sh
CXX	= g++
CXXFLAGS= -std=c++11 -g 
COPT	= -O0
CSRCS	= transform_info.cpp\
          transform.cpp\
	  transform_main.cpp\
	  compute_u.cpp\
	  compute_ctsh.cpp\
	  main.cpp
COBJS	= $(CSRCS:.cpp=.o)
HEAD	= ph_analysis.h\
	  pdm.h\
	  mo_coefficients.h\
	  transform_info.h
INCLUDE = -I/home/wh288/iquads/blas/ -I/home/wh288/iquads/utilities/ph_analysis/ -I/home/wh288/iquads/matrix/
LIBS	= /home/wh288/iquads/blas/lib_blas_interface.a /home/wh288/iquads/matrix/libmatrix.a -L/home/intel/mkl/lib/intel64/ -lmkl_intel_lp64 -lmkl_sequential -lmkl_core -lpthread -lgfortran

PGM	= ph_trans

$(PGM):	$(COBJS) $(HEAD) /home/wh288/iquads/blas/lib_blas_interface.a
	$(CXX) $(CXXFLAGS) -o $(PGM) $(COBJS) $(LIBS)

.SUFFIXES: .cpp .o

.cpp.o: $(HEAD)
	$(CXX) -c $(CXXFLAGS) $(INCLUDE) $<

clean:
	rm *.o; rm $(PGM)
	
