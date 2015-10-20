iquads_root	= $(DEV_ROOT)/iquads/
iquads_src	= $(iquads_root)/src/
iquads_bin	= $(iquads_root)/bin/

CC		= gcc
CPP		= g++
AR		= ar -r

CFLAGS		= -I$(iquads_src) -I/usr/include
CPPFLAGS	= -std=c++11 -I$(iquads_src) -I/usr/include
CPPOPT		= 

CPPHEADS	= client.hpp\
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


CPPSRCS		= \
		  request.cpp\
		  config.cpp\
		  report.cpp\
		  client.cpp\
		  agent.cpp
CPPOBJS		= $(CPPSRCS:.cpp=.o)
LIBS		= $(iquads_src)/electron_correlation/libiquads_electron_correlation.a $(iquads_src)/interface_to_third_party/libiquads_third_party.a -L/usr/lib64 -lboost_filesystem -lboost_date_time -lboost_system 

executable	= iquads_manybody_expansion
library		= libiquads_manybody_expansion.a

all: release

debug: 	CPPOPT += -g -O3\
		  -Wextra -Wcast-align \
		  -Wdisabled-optimization \
		  -Wfloat-equal -Wformat=2 \
		  -Wformat-nonliteral -Wformat-security  \
		  -Wformat-y2k \
		  -Wimport  -Winit-self -Winline\
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
		  -Wwrite-strings
debug: executable
debug: library

release: CPPOPT +=  -O3 
release: executable
release: library

standalone: CPPOPT += -static
#standalone: we don't have static libary of boost ...
standalone: library
standalone: executable

clean:
	rm *.o; rm $(executable) $(library); rm $(iquads_bin)/$(executable)

executable:	main.o $(CPPOBJS)
	$(CPP) -o $(executable) $(CPPFLAGS) $(CPPOPT) main.o $(CPPOBJS) $(LIBS)
	cp $(executable) $(iquads_bin)

library:	$(CPPOBJS)
	$(AR) $(library)  $(CPPOBJS)

main.o: $(iquads_src)/iquads/command_parser.hpp\
	$(iquads_src)/manybody_expansion/client.hpp\
	$(iquads_src)/manybody_expansion/client.cpp
	$(CPP) -o main.o -c $(CPPOPT) $(CPPFLAGS) main.cpp

request.o: $(iquads_src)/manybody_expansion/request.hpp\
	   $(iquads_src)/manybody_expansion/request.cpp
	$(CPP) -o request.o -c $(CPPOPT) $(CPPFLAGS) request.cpp

config.o: $(iquads_src)/interface_to_third_party/program_mask.hpp\
	  $(iquads_src)/manybody_expansion/config.hpp\
	  $(iquads_src)/manybody_expansion/config.cpp
	$(CPP) -o config.o -c $(CPPOPT) $(CPPFLAGS) config.cpp

report.o: $(iquads_src)/manybody_expansion/report.hpp\
	  $(iquads_src)/manybody_expansion/report.cpp
	$(CPP) -o report.o -c $(CPPOPT) $(CPPFLAGS) report.cpp

client.o: $(iquads_src)/iquads/command_parser.hpp\
	  $(iquads_src)/manybody_expansion/command_setting.hpp\
	  $(iquads_src)/manybody_expansion/config.hpp\
	  $(iquads_src)/manybody_expansion/report.hpp\
	  $(iquads_src)/manybody_expansion/client.cpp
	$(CPP) -o client.o -c $(CPPOPT) $(CPPFLAGS) client.cpp

agent.o: $(iquads_src)/interface_to_third_party/external_program_agent_base.hpp\
	 $(iquads_src)/manybody_expansion/order_mask.hpp\
	 $(iquads_src)/manybody_expansion/request.hpp\
	 $(iquads_src)/manybody_expansion/config.hpp\
	 $(iquads_src)/manybody_expansion/manybody_expansion_template.hpp\
	 $(iquads_src)/manybody_expansion/agent.hpp\
	 $(iquads_src)/manybody_expansion/agent.cpp
	$(CPP) -o agent.o -c $(CPPOPT) $(CPPFLAGS) agent.cpp

