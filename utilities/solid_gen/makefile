IQUADS_ROOT	= /home/wh288/iquads/
CXX	= g++
COPT	= -g --std=c++11
CFLAGS	= -I$(IQUADS_ROOT)
CSRCS	= crystal_info.cpp\
	  fragment_generator_driver.cpp\
	  matrix_function.cpp\
	  main.cpp
COBJS	= $(CSRCS:.cpp=.o)
LIBS	= -lgfortran $(IQUADS_ROOT)/blas/lib_blas_interface.a -L/home/intel/mkl/lib/intel64 -lmkl_intel_lp64 -lmkl_core -lmkl_sequential -lpthread
PGM	= solid_gen

$(PGM):	$(COBJS)
	$(CXX) -o $(PGM) $(COBJS) $(LIBS)

#.cpp.o:
#	$(CXX) -c $(COPT) $(CFLAGS) $<

matrix_function.o:	matrix_function.h	matrix_function.cpp
	$(CXX) -c $(COPT) $(CFLAGS) matrix_function.cpp

crystal_info.o	:	crystal_info.h	crystal_info.cpp
	$(CXX) -c $(COPT) $(CFLAGS) matrix_function.cpp

fragment_generator_driver.o:	fragment_generator_driver.cpp
	$(CXX) -c $(COPT) $(CFLAGS) matrix_function.cpp

main.o:	main.cpp
	$(CXX) -c $(COPT) $(CFLAGS) matrix_function.cpp

test_coord:
	$(CXX) -o check/test_coord $(CFLAGS) $(COPT) check/test_coordinate.cpp;
	check/test_coord

test_3d_space:
	$(CXX) -o check/test_3d_space $(CFLAGS) $(COPT) check/test_threed_space.cpp
	check/test_3d_space

test_atom:
	$(CXX) -o check/test_atom $(CFLAGS) $(COPT) check/test_atom.cpp;
	check/test_atom

test_molecule:
	$(CXX) -o check/test_molecule $(CFLAGS) $(COPT) check/test_molecule.cpp
	check/test_molecule

test_lattice_para:
	$(CXX) -o check/test_lattice_para $(CFLAGS) $(COPT) check/test_lattice_parameters.cpp
	check/test_lattice_para

test_unit_cell:
	$(CXX) -o check/test_unit_cell $(CFLAGS) $(COPT) check/test_unit_cell.cpp
	check/test_unit_cell

clean:
	rm *.o; rm solid_gen
