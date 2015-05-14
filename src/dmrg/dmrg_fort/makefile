#/bin/sh
SHELL	= /bin/sh
FC	= gfortran
FOPT	= -g
FFLAGS	=
FSRCS	= main.f dmrg.f
FOBJS	= $(FSRCS:.f=.o)
LIBS	=
PGM	= dmrg.fortran

ifeq ($(FC),gfortran)
   FFLAGS = -cpp -D_GNU
endif

ifeq ($(FC),ifort)
   FFLAGS = -D_INTEL
endif

$(PGM):	$(FOBJS)
	$(FC) -o $(PGM) $(FOBJS) $(LIBS)

.SUFFIXES: .f .o

.f.o:
	$(FC) -c $(FFLAGS) $<

clean:
	rm *.o; rm dmrg.fortran
