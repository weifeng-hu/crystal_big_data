ROOT	= /home/wh288/Development/iqs/
CXX	= mpic++ -g
COPT	= -O2
HEADS	= overlap_config_class.h
CSRCS	= overlap_config_class.cpp overlap_main.cpp
COBJS	= $(CSRCS:.cpp=.o)
INCLUDE	= -I$(ROOT)
LIBS	= -L$(ROOT)/matrix/ -lmatrix -L/home/intel/mkl/lib/intel64 -lmkl_intel_lp64 -lmkl_sequential -lmkl_core
PGM	= overlap

all:
	make $(PGM); cp $(PGM) $(ROOT)/bin

$(PGM):	$(HEADS) $(COBJS)
	$(CXX) -o $(PGM) $(INCLUDE) $(COBJS) $(LIBS)

overlap_config_class.o:	overlap_config_class.h	overlap_config_class.cpp
	$(CXX) -c $(INCLUDE) overlap_config_class.cpp

overlap_main.o:	$(ROOT)/matrix/general_matrix.h $(ROOT)/matrix/general_matrix.cpp overlap_config_class.h overlap_config_class.cpp overlap_main.cpp
	$(CXX) -c $(INCLUDE) overlap_main.cpp
