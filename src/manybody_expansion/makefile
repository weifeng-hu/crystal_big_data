IQUADS_ROOT	= /home/chronos/user/Development/iquads/
IQUADS_SRC	= $(IQUADS_ROOT)/src/
IQUADS_BIN	= $(IQUADS_ROOT)/bin/
CC		= gcc
CXX		= g++
CFLAGS		= -O0 -std=c++11 -I$(IQUADS_SRC)
CHEADS		= manybody_expansion_client.h
CSRCS		= \
		  main.cpp\
		  manybody_expansion_config.cpp\
		  manybody_expansion_client.cpp\
		  manybody_expansion_agent.cpp
COBJS		= $(CSRCS:.cpp=.o)
LIBS		=
PGM		= mbe

$(PGM):	$(COBJS)
	$(CXX) -o $(PGM) $(CFLAGS) $(COPT) $(COBJS) $(LIBS)
	cp $(PGM) $(IQUADS_BIN)

main.o: ./../iquads/command_parser.h ./manybody_expansion_client.h ./manybody_expansion_client.cpp
	$(CXX) -c $(CFLAGS) main.cpp

manybody_expansion_config.o: ./../interface_to_third_party/external_program_bitmask.h\
		             ./../electron_correlation/electron_correlation_config.h\
			     ./manybody_expansion_config.h
	$(CXX) -c $(CFLAGS) manybody_expansion_config.cpp

manybody_expansion_client.o: ./../iquads/command_parser.h\
			     ./manybody_expansion_command_setting.h\
			     ./manybody_expansion_config.h\
			     ./manybody_expansion_report.h
	$(CXX) -c $(CFLAGS) manybody_expansion_client.cpp

manybody_expansion_agent.o: ./../interface_to_third_party/external_program_agent_base.h\
			    ./../interface_to_third_party/external_program_agent.h\
			    ./manybody_expansion_agent.h\
			    ./manybody_expansion_order_bitmask.h
	$(CXX) -c $(CFLAGS) manybody_expansion_agent.cpp

clean:
	rm *.o; rm $(PGM); rm $(IQUADS_BIN)/$(PGM)

