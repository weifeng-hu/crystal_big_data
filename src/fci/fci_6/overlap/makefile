PGM    = Be
FOPT   = -O3  
FFLAGS = $(FOPT)
FC     = ifort        
FFSRCS = 
FSRCS  = overlap.f
FOBJS  = $(FSRCS:.f=.o)   
FFOBJS = $(FFSRCS:.f90=.o)
OBJS   = $(FFOBJS) $(FOBJS)  
FFLIBS = -L/home/intel/mkl/lib/intel64
FLIBS  = $(FFLIBS) -lmkl_intel_lp64 -lmkl_intel_thread -lmkl_core -liomp5

$(PGM): $(OBJS) 
	$(FC) $(FFLAGS) -o $(PGM) $(OBJS) $(FLIBS) 

clean:
	rm *.o; rm Be

clobber:

.SUFFIXES:      .f .f90 .o

.f90.o: 
	$(FC) $(FFLAGS) -c  $<

.f.o:
	$(FC) $(FFLAGS) -c  $<

