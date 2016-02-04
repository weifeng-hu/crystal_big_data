shell	= /bin/sh
cxx	= g++
cxxflag	= -fopenmp -g -std=c++11
cxxopt	= -O0
cxxinc	= -I${HOME}/iquads/src/
cxxsrcs	= main.cpp
cxxobjs	= $(cxxsrcs:.cpp=.o)
target	= test
lib	= $(HOME)/iquads/lib/libiquads_matrix.a $(HOME)/iquads/lib/libiquads_blas_interface.a -llapack -lblas -lgfortran

${target}:	$(cxxobjs)
	${cxx} -fopenmp -o ${target} ${cxxobjs} ${lib}

main.o:	main.cpp
	${cxx} -c ${cxxflag} ${cxxinc} ${cxxopt} main.cpp

clean:
	rm main.o test
