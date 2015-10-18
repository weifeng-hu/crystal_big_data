PGM_DIR = ./
INCLUDE = ./
HEAD_FILES = $(PGM_DIR)/molecule_geom.h
CSRCS = orca_read.cpp read_output.cpp
COBJS = $(CSRCS:.cpp=.o)
CXX = g++
COPT = -O0
PGM = orca_read

$(PGM): $(HEAD_FILES) $(COBJS)
	$(CXX) $(COPT) -o $(PGM) -I$(INCLUDE) $(COBJS)

orca_read.o:	orca_read.cpp read_output.cpp
	$(CXX) $(COPT) -c -I$(INCLUDE) orca_read.cpp

read_output.o:	read_output.cpp molecule_geom.h
	$(CXX) $(COPT) -c -I$(INCLUDE) read_output.cpp
