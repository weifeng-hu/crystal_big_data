SHELL = /bin/sh

INCLUDE = -I../ -I/usr/include/python -I../ithaca -I../interface/psi3/ -I../scf/ -I../tensor/

HEAD_FILES = \
	scf.h\
	scf_class_input_ao.h cmd_options.h scf_class_rhf.cpp\
	scf_class_SCF.h\

LIBS  = /home/intel/fce/10.1.021/lib/ -lifcore -L/home/intel/mkl/10.1.0.015/lib/em64t -lmkl_intel_lp64 -lmkl_intel_thread -lmkl_lapack -lmkl_core -liomp5 -lpthread -lm -lpython2.7

CSRCS = scf_class_input_ao.cpp cmd_options.cpp scf_class_rhf.cpp\
	scf_class_SCF.cpp\
	rhf_main.cpp\
	scf_f.cpp\
	scf.cpp

FSRCS = SCF.f

COBJS = $(CSRCS:.cpp=.o)

COBJS2 = ../py/interface.o\
	 ../py/py_value.o\
	 ../py/py_string.o\
	 ../py/py_structure.o\
	 ../py/py_vector.o\
	 ../tensor/tensor.o\
	 ../interface/psi3/qcread.o\
	 ../ithaca/cmd_options.o

FOBJS = $(FSRCS:.f=.o)

CXX   = mpic++
FORT  = ifort

COPT  = -O2
FOPT  = -O2

PGM   = scf

$(PGM): $(FOBJS) $(COBJS)
	$(CXX) $(COPT) -o $(PGM) $(INCLUDE) $(FOBJS) $(COBJS) $(COBJS2) -L$(LIBS)


SCF.o:	SCF.f
	$(FORT) $(FOPT) -c SCF.f

scf_f.o:  scf.h 
	$(CXX) $(COPT) $(INCLUDE) -c scf_f.cpp

cmd_options.o:		../ithaca/cmd_options.h\
			cmd_options.cpp
	$(CXX) $(COPT) $(INCLUDE) -c cmd_options.cpp

scf_class_input_ao.o:	 ../ithaca/cmd_options.h\
			 ../interface/psi3/qcread.h\
			 ../scf/scf_class_input_ao.h\
			 ../tensor/tensor.h\
			 ../tensor/tensor.cpp\
			 ../py/interface.h\
			 ../py/py_api.h\
			 ../py/py_value.cpp\
			 ../py/py_vector.cpp\
			 scf_class_input_ao.cpp
	$(CXX) $(COPT) $(INCLUDE) -c scf_class_input_ao.cpp

scf_class_rhf.o:	../tensor/tensorclass.h\
			scf_class_rhf.h\
			scf_class_rhf.cpp
	$(CXX) $(COPT) $(INCLUDE) -c scf_class_rhf.cpp;

rhf_main.o:	rhf_main.cpp
	$(CXX) $(COPT) $(INCLUDE) -c rhf_main.cpp

scf_class_SCF.o:	../ithaca/cmd_options.h\
			../interface/psi3/qcread.h\
			scf_class_input_ao.h\
			scf_class_SCF.h\
			scf_class_SCF.cpp
	$(CXX) $(COPT) $(INCLUDE) -c scf_class_SCF.cpp

scf.o:			../ithaca/cmd_options.h\
			../interface/psi3/qcread.h\
			../scf/scf_class_SCF.h\
			scf.cpp
	$(CXX) $(COPT) $(INCLUDE) -c scf.cpp

clean:
	rm *.o; rm scf
