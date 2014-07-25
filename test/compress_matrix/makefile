ROOT	= /home/wh288/Development/iqs/
CXX	= mpic++ -g
CSRCS	= TEST_matrix_crs.cpp
COBJS	= $(CSRCS:.cpp=.o) ../../matrix/compressed_matrix.o ../../matrix/general_matrix.o
INCLUDE	= -I$(ROOT)
PGM	= test_crs

$(PGM):	$(COBJS)
	$(CXX) -o $(PGM) $(INCLUDE) $(COBJS)

TEST_matrix_crs.o:	TEST_matrix_crs.cpp
	$(CXX) -c $(INCLUDE) TEST_matrix_crs.cpp
