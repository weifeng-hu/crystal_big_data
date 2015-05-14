ROOT = /home/wh288/Development/iqs
DMRG_DIR = $(ROOT)/dmrg
BOOST_DIR = /home/wh288/Development/boost_1_53_0
CXX   = mpic++
COPT  = -g
INCLUDES = -I$(ROOT) -I$(DMRG_DIR) -I$(BOOST_DIR)
CSRCS = cmd_option.cpp\
	dmrg_config_class.cpp\
	dmrg.cpp\
	dmrg_main.cpp
COBJS  = $(CSRCS:.cpp=.o)
LIBS   = -L/home/wh288/Development/boost_1_53_0/stage/lib -lboost_mpi
PGM    = dmrg

$(PGM): $(CSRCS) $(COBJS)
	$(CXX) -o $(PGM) $(INCLUDES) $(COBJS) $(LIBS)

cmd_option.o: dmrg_define.h cmd_option.h cmd_option.cpp
	$(CXX) -c $(INCLUDES) cmd_option.cpp

dmrg_config_class.o: dmrg_define.h cmd_option.h dmrg_config_class.cpp
	$(CXX) -c $(INCLUDES) dmrg_config_class.cpp

dmrg.o:	dmrg.h dmrg.cpp
	$(CXX) -c $(INCLUDES) dmrg.cpp

dmrg_main.o:	dmrg_define.h cmd_option.h dmrg_config_class.h dmrg_main.cpp
	$(CXX) -c $(INCLUDES) dmrg_main.cpp


#.SUFFIXES: .cpp .o

#.cpp.o:
#	$(CXX) -c $<

clean:
	rm *.o; rm dmrg
