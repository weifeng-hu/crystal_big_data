IQUADS_ROOT	= /home/chronos/user/Development/iquads/
IQUADS_SRC	= $(IQUADS_ROOT)/src/
IQUADS_BIN	= $(IQUADS_ROOT)/bin/
CXX	= g++
COPT	= -O0 --std=c++11
CFLAGS	= -I/home/chronos/user/Development/boost_1_53_0/ -I$(IQUADS_SRC)
CHEADS	= array_matrix_base.h\
	  array_matrix.h\
	  atom.h\
	  combination.h\
	  coordinate.h\
	  crystal_info.h\
	  euclidean_distance_matrix.h\
	  fragment_generator_driver.h\
	  fragment_group_info.h\
	  fragment_info.h\
	  interaction.h\
	  iquads_limits.h\
	  lattice.h\
	  lattice_base.h\
	  lattice_parameters.h\
	  math_function.h\
	  matrix.h\
	  matrix_function.h\
	  molecule.h\
	  molecule_bulk.h\
	  polymer.h\
	  polymer_base.h\
	  polymer_group_base.h\
	  threed_space.h\
	  threed_space_function.h\
	  unit_cell.h\
	  unit_cell_base.h\
	  vector_matrix.h\
	  vector_matrix_base.h\
	  crystal_info.h
CSRCS	= crystal_info.cpp\
	  matrix_function.cpp\
	  fragment_generator_driver.cpp\
	  main.cpp
COBJS	= $(CSRCS:.cpp=.o)
LIBS	= $(IQUADS_SRC)/blas/lib_blas_interface.a /home/chronos/user/Development/lapack-3.5.0/liblapack.a /home/chronos/user/Development/BLAS/libblas.a /usr/local/gcc_arm_native/lib/libgfortran.a
PGM	= solid_gen

$(PGM):	$(COBJS)
	$(CXX) -o $(PGM) $(CFLAGS) $(COPT) $(COBJS) $(LIBS)
	cp $(PGM) $(IQUADS_BIN)

#.cpp.o:
#	$(CXX) -c $(COPT) $(CFLAGS) $<

matrix_function.o:	matrix_function.h	matrix_function.cpp
	$(CXX) -c $(COPT) $(CFLAGS) matrix_function.cpp

crystal_info.o	: $(CHEADS)	crystal_info.h	crystal_info.cpp
	$(CXX) -c $(COPT) $(CFLAGS) crystal_info.cpp

fragment_generator_driver.o: $(CHEADS)	fragment_generator_driver.cpp
	$(CXX) -c $(COPT) $(CFLAGS) fragment_generator_driver.cpp

main.o:	fragment_generator_driver.h main.cpp
	$(CXX) -c $(COPT) $(CFLAGS) main.cpp

test_combination:
	$(CXX) -o check/test_combination $(CFLAGS) $(COPT) check/test_combination.cpp
	check/test_combination

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

test_info:
	$(CXX) -c $(CFLAGS) $(COPT) crystal_info.cpp
	$(CXX) -o check/test_info.o -c $(CFLAGS) $(COPT) check/test_info.cpp
	$(CXX) -o check/test_info $(CFLAGS) $(COPT) ./crystal_info.o check/test_info.o
	check/test_info

test_lattice:
	$(CXX) -o check/test_lattice $(CFLAGS) $(COPT) check/test_lattice.cpp
	check/test_lattice > test_lattice.out

test_matrix:
	$(CXX) -o check/test_matrix $(CFLAGS) $(COPT) check/test_matrix.cpp
	check/test_matrix

test_edm:
	$(CXX) -o matrix_function.o $(CFLAGS) $(COPT) -c matrix_function.cpp
	$(CXX) -o check/test_euclidean_mat.o $(CFLAGS) $(COPT) -c check/test_euclidean_mat.cpp
	$(CXX) -o check/test_edm $(CFLAGS) $(COPT) matrix_function.o check/test_euclidean_mat.o ../../blas/lib_blas_interface.a $(LIBS)
	check/test_edm

test_polymer:
	$(CXX) -o check/test_polymer $(CFLAGS) $(COPT) check/test_polymer.cpp
	check/test_polymer

test_bulk:
	$(CXX) -o check/test_bulk $(CFLAGS) $(COPT) check/test_bulk.cpp
	check/test_bulk

test_fragment_info:
	$(CXX) -o check/test_fragment_info $(CFLAGS) $(COPT) check/test_fragment_info.cpp
	check/test_fragment_info

test_frag_group:
	$(CXX) -o check/test_frag_group $(CFLAGS) $(COPT) check/test_frag_group.cpp
	check/test_frag_group

test_polymer_group:
	$(CXX) -o check/test_polymer_group $(CFLAGS) $(COPT) check/test_polymer_group.cpp
	check/test_polymer_group

test_interaction:
	$(CXX) -o check/test_interaction $(CFLAGS) $(COPT) check/test_interaction.cpp
	check/test_interaction

clean:
	rm *.o; rm solid_gen
