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
INCLUDE = -I/home/wh288/iqs/blas/ -I/home/wh288/iqs/utilities/ph_analysis/
LIBS	= /home/wh288/iqs/blas/lib_blas_interface.a -L/home/intel/mkl/lib/intel64/ -lmkl_intel_lp64 -lmkl_sequential -lmkl_core -lpthread -lgfortran

PGM	= ph_trans

$(PGM):	$(COBJS) $(HEAD) /home/wh288/iqs/blas/lib_blas_interface.a
	$(CXX) $(CXXFLAGS) -o $(PGM) $(COBJS) $(LIBS)

.SUFFIXES: .cpp .o

.cpp.o: $(HEAD)
	$(CXX) -c $(CXXFLAGS) $(INCLUDE) $<

clean:
	rm *.o; rm $(PGM)
	
