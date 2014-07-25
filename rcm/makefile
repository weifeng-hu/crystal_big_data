ROOT	= /home/wh288/Development/iqs/
EXE_DIR	= $(ROOT)/bin/
CXX	= mpic++ -g
HEADS	= star_matrix.h rcm_main.h rcm.h
CSRCS	= input_matrix.cpp print_star_mat.cpp rcm_main.cpp star_matrix.cpp generate_adj.cpp reorder.cpp rcm_help.cpp calc_fock.cpp
CSRC	= rcm.c rcm_f77.c
COBJS	= $(CSRCS:.cpp=.o) ../matrix/square_matrix.o rcm.o rcm_f77.o
PGM	= rcm
INCLUDE	= -I../ -I./  -I/home/wh288/boost_1_53_0/
LIBS	= -L../matrix/ -lmatrix -lm -lgfortran -L/home/intel/composerxe/mkl/lib/intel64 -lmkl_intel_lp64 -lmkl_sequential -lmkl_core -L/home/wh288/boost_1_53_0/stage/lib -lboost_serialization

all:	
	make $(PGM); cp $(PGM) $(EXE_DIR)

$(PGM):	$(CSRCS) $(COBJS) ../matrix/libmatrix.a 
	$(CXX) -o $(PGM) $(INCLUDE) $(COBJS) $(LIBS)

calc_fock.o:	calc_fock.cpp
	$(CXX) -c $(INCLUDE) calc_fock.cpp

rcm_help.o: rcm_help.cpp
	$(CXX) -c $(INCLUDE) rcm_help.cpp

input_matrix.o:	../matrix/square_matrix.h ../matrix/square_matrix.cpp input_matrix.cpp
	$(CXX) -c $(INCLUDE) input_matrix.cpp

rcm_main.o: rcm_main.cpp ../matrix/square_matrix.h star_matrix.h rcm_main.h
	$(CXX) -c $(INCLUDE) rcm_main.cpp

print_star_mat.o:	star_matrix.h print_star_mat.cpp
	$(CXX) -c $(INCLUDE) print_star_mat.cpp

star_matrix.o:	star_matrix.h star_matrix.cpp
	$(CXX) -c $(INCLUDE) star_matrix.cpp

rcm.o:	rcm.c rcm.h
	mpicc -g -c $(INCLUDE) rcm.c

rcm_f77.o:  rcm.h  rcm_f77.c
	mpicc -g -c $(INCLUDE) rcm_f77.c

generate_adj.o:	star_matrix.h generate_adj.cpp
	$(CXX) -c $(INCLUDE) generate_adj.cpp

reorder.o:	rcm.h	reorder.cpp
	$(CXX) -c $(INCLUDE) reorder.cpp

clean:
	rm *.o; rm rcm
