CXX	= g++
INCLUDE	= -I/home/wh288/Development/boost_1_53_0/
COPT	= -g
PGM	= num_nac
CSRC	= num_nac.cpp
COBJ	= $(CSRC:.cpp=.o)
LIBS	= -L/home/wh288/Development/boost_1_53_0/stage/lib/ -lboost_algorithm

$(PGM): $(COBJ)
	$(CXX) -o $(PGM) $(COBJ)

.cpp.o:
	$(CXX) -c $(COPT) $<

clean:
	rm *.o; rm num_nac
