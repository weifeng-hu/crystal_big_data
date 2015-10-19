IQUADS_ROOT	= /home/wh288/Development/iquads/
IQUADS_SRC	= $(IQUADS_ROOT)/src/
IQUADS_BIN	= $(IQUADS_ROOT)/bin/
CC		= gcc
CXX		= g++
CFLAGS		= -g\
		  -Wextra -Wcast-align \
		  -Wdisabled-optimization \
		  -Wfloat-equal -Wformat=2 \
		  -Wformat-nonliteral -Wformat-security  \
		  -Wformat-y2k \
		  -Wimport  -Winit-self  -Winline \
		  -Winvalid-pch   \
		  -Wmissing-field-initializers -Wmissing-format-attribute   \
		  -Wmissing-include-dirs -Wmissing-noreturn \
		  -Wpacked  -Wpointer-arith \
		  -Wredundant-decls \
		  -Wstack-protector \
		  -Wstrict-aliasing=2 -Wswitch-default \
		  -Wswitch-enum \
		  -Wunreachable-code \
		  -Wvariadic-macros \
		  -Wwrite-strings\
		  -std=c++11 -I/usr/include -I$(IQUADS_SRC)
CHEADS		= client.hpp\
		  agent.hpp\
		  command_setting.hpp\
		  request.hpp\
		  report.hpp\
		  config.hpp\
		  manybody_expansion_template.hpp\
		  expansion_formula_periodic_traits.hpp\
		  compute_expansion_term_periodic_traits.hpp\
		  compute_interaction_energy_traits.hpp\
		  order_mask.hpp\
		  lattice.hpp
CSRCS		= \
		  main.cpp\
		  request.cpp\
		  config.cpp\
		  client.cpp\
		  agent.cpp
COBJS		= $(CSRCS:.cpp=.o)\
		 ../electron_correlation/test/client.o\
		 ../electron_correlation/test/report.o\
		 ../electron_correlation/test/setting.o\
		 ../electron_correlation/test/molpro_agent.o
LIBS		= -L/usr/lib64 -lboost_filesystem -lboost_date_time -lboost_system 
PGM		= mbe

$(PGM):	$(COBJS)
	$(CXX) -o $(PGM) $(CFLAGS) $(COPT) $(COBJS) $(LIBS)
	cp $(PGM) $(IQUADS_BIN)

main.o: ./../iquads/command_parser.hpp ./client.hpp ./client.cpp
	$(CXX) -c $(CFLAGS) main.cpp

request.o: ./request.hpp ./request.cpp
	$(CXX) -c $(CFLAGS) request.cpp

config.o: ./../interface_to_third_party/program_mask.hpp\
	 ./config.hpp
	$(CXX) -c $(CFLAGS) config.cpp

client.o: ./../iquads/command_parser.hpp\
	 ./command_setting.hpp\
	 ./config.hpp\
	 ./report.hpp
	$(CXX) -c $(CFLAGS) client.cpp

agent.o: ./../interface_to_third_party/external_program_agent_base.hpp\
	 ./compute_interaction_energy_traits.hpp\
	 ./agent.hpp\
	 ./order_mask.hpp
	$(CXX) -c $(CFLAGS) agent.cpp

clean:
	rm *.o; rm $(PGM); rm $(IQUADS_BIN)/$(PGM)

