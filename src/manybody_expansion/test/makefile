iquads_root     = $(DEV_ROOT)/iquads/
iquads_src      = $(iquads_root)/src/
iquads_bin      = $(iquads_root)/bin/
CC              = gcc
CPP             = g++
CPPOPT		= -O3 -std=c++11 -fopenmp
CPPFLAGS        = -I/usr/include -I$(iquads_src)
CHEADS          =
CPPSRCS         =\
		$(iquads_src)/manybody_expansion/test/main.cpp
CPPOBJS         = $(CPPSRCS:.cpp=.o)
LIBS            = $(iquads_src)/manybody_expansion/libiquads_manybody_expansion.a\
		  $(iquads_src)/electron_correlation/libiquads_electron_correlation.a\
		  $(iquads_src)/interface_to_third_party/libiquads_third_party.a\
		  $(iquads_src)/matrix/libiquads_matrix.a\
		  $(iquads_src)/blas/libiquads_blas_interface.a\
		  -L/usr/lib64 -lboost_filesystem -lboost_date_time -lboost_system\
		  -L/home/intel/mkl/compiler_and_libraries/linux/mkl/lib/intel64 -lmkl_intel_lp64 -lmkl_sequential -lmkl_core \
	 	  -lgfortran
		  #-L/home/intel/compilers_and_libraries/linux/lib/intel64 -liomp5 -lifcore -lifport -limf -lirc -lintlc
executable      = $(iquads_src)/manybody_expansion/test/test

all: $(executable)

remove:
	rm -rf ./try/; rm -rf /scratch/wh288/lattice_x/

$(executable): $(CPPOBJS)
	rm -rf ./try/; rm -rf /scratch/wh288/lattice_x/; cd ../; make distclean; make all; cd $(iquads_src)/manybody_expansion/test/; $(CPP) -o $(executable) $(CPPFLAGS) $(CPPOPT) $(CPPOBJS) $(LIBS)

tiny: $(CPPOBJS)
	rm -rf ./try/; rm -rf /scratch/wh288/lattice_x/; $(CPP) -o $(executable) $(CPPFLAGS) $(CPPOPT) $(CPPOBJS) $(LIBS)

retry: $(CPPOBJS)
	$(CPP) -o $(executable) $(CPPFLAGS) $(CPPOPT) $(CPPOBJS) $(LIBS)

$(iquads_src)/manybody_expansion/test/main.o: $(iquads_src)/manybody_expansion/test/main.cpp
	$(CPP) -o $(iquads_src)/manybody_expansion/test/main.o -c $(CPPFLAGS) $(CPPOPT) $(iquads_src)/manybody_expansion/test/main.cpp

clean:
	rm $(iquads_src)/manybody_expansion/test/*.o; rm $(executable);
