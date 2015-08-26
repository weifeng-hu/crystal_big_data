IQUADS_ROOT	= /home/chronos/user/Development/iquads/
IQUADS_SRC	= $(IQUADS_ROOT)/src/
IQUADS_BIN	= $(IQUADS_ROOT)/bin/
CC		= gcc
CXX		= g++
CFLAGS		= -O0 -std=c++11 -I$(IQUADS_SRC)
CHEADS		= client.h\
		  agent.h\
		  command_setting.h\
		  request.h\
		  report.h\
		  config.h\
		  manybody_expansion_template.h\
		  expansion_formula_periodic_traits.h\
		  compute_expansion_term_periodic_traits.h\
		  compute_interaction_energy_traits.h\
		  order_mask.h\
		  lattice.h
CSRCS		= \
		  main.cpp\
		  config.cpp\
		  client.cpp\
		  agent.cpp
COBJS		= $(CSRCS:.cpp=.o)
LIBS		=
PGM		= mbe

$(PGM):	$(COBJS)
	$(CXX) -o $(PGM) $(CFLAGS) $(COPT) $(COBJS) $(LIBS)
	cp $(PGM) $(IQUADS_BIN)

main.o: ./../iquads/command_parser.h ./client.h ./client.cpp
	$(CXX) -c $(CFLAGS) main.cpp

config.o: ./../interface_to_third_party/external_program_bitmask.h\
	 ./../electron_correlation/config.h\
	./config.h
	$(CXX) -c $(CFLAGS) config.cpp

client.o: ./../iquads/command_parser.h\
	 ./command_setting.h\
	 ./config.h\
	 ./report.h
	$(CXX) -c $(CFLAGS) client.cpp

agent.o: ./../interface_to_third_party/external_program_agent_base.h\
	 ./compute_interaction_energy_traits.h\
	 ./agent.h\
	 ./order_mask.h
	$(CXX) -c $(CFLAGS) agent.cpp

clean:
	rm *.o; rm $(PGM); rm $(IQUADS_BIN)/$(PGM)

