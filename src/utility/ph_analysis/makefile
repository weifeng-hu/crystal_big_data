

SHELL	= /bin/sh
CXX	= g++
CXXFLAGS= -std=c++11 -g -fopenmp
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
INCLUDE = -I/home/wh288/Development/6000.integrated_quantum_dynamics/src/ -I/home/wh288/Development/6000.integrated_quantum_dynamics/src//blas/ -I/home/wh288/Development/6000.integrated_quantum_dynamics/src//utilities/ph_analysis/ -I/home/wh288/Development/6000.integrated_quantum_dynamics/src//matrix/
LIBS	= -L/home/wh288/Development/6000.integrated_quantum_dynamics/src//blas -liquads_blas_interface -L/home/wh288/Development/6000.integrated_quantum_dynamics/src//matrix/ -liquads_matrix -L/home/intel/mkl/lib/intel64/ -lmkl_intel_lp64 -lmkl_sequential -lmkl_core -lpthread -lgfortran

PGM	= ph_trans

$(PGM):	$(COBJS) $(HEAD) /home/wh288/Development/6000.integrated_quantum_dynamics/src//blas/libiquads_blas_interface.a
	$(CXX) $(CXXFLAGS) -o $(PGM) $(COBJS) $(LIBS)

.SUFFIXES: .cpp .o

.cpp.o: $(HEAD)
	$(CXX) -c $(CXXFLAGS) $(INCLUDE) $<

clean:
	rm *.o; rm $(PGM)
	
