iquads_root	= $(DEV_ROOT)/iquads/
iquads_src	= $(iquads_root)/src/
iquads_bin	= $(iquads_root)/bin/

include $(iquads_src)/blas/makefile
include $(iquads_src)/matrix/makefile
include $(iquads_src)/interface_to_third_party/makefile
include $(iquads_src)/electron_correlation/makefile

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
LIBS		= $(iquads_src)/electron_correlation/libiquads_electron_correlation.a\
		  $(iquads_src)/interface_to_third_party/libiquads_third_party.a\
		  $(iquads_src)/matrix/libiquads_matrix.a\
		  $(iquads_src)/blas/libiquads_blas_interface.a\
		  -L/usr/lib64 -lboost_filesystem -lboost_date_time -lboost_system\
		  -L/home/intel/compiler_and_libraries/linux/mkl/lib/intel64 -lmkl_intel_lp64 -lmkl_sequential -lmkl_core -lpthread -lm\
			-lgfortran 
	#	  -L/home/intel/compilers_and_libraries/linux/lib/intel64 -liomp5 -lifcore -lifport -limf -lirc -lintlc

executable	= iquads_manybody_expansion
library		= libiquads_manybody_expansion.a

all: release

debug: 	CPPOPT += -g -O0\
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
debug: library
debug: executable

release: CPPOPT +=  -O3 
release: CPPOPT +=  -fopenmp
release: library
release: executable

standalone: CPPOPT += -static
#standalone: we don't have static libary of boost ...
standalone: executable
standalone: library

clean:
	rm *.o; rm $(executable) $(library); rm $(iquads_bin)/$(executable)

distclean:
	make clean_blas; make clean_matrix; make clean_third_party; make clean_electron_correlation; make clean

executable:	\
		$(iquads_src)/blas/libiquads_blas_interface.a\
		$(iquads_src)/matrix/libiquads_matrix.a\
		$(iquads_src)/interface_to_third_party/libiquads_third_party.a\
		$(iquads_src)/electron_correlation/libiquads_electron_correlation.a\
		main.o $(CPPOBJS)
	$(CPP) -o $(executable) $(CPPFLAGS) $(CPPOPT) main.o $(CPPOBJS) $(LIBS)
	cp $(executable) $(iquads_bin)

library:	\
		$(iquads_src)/blas/libiquads_blas_interface.a\
		$(iquads_src)/matrix/libiquads_matrix.a\
		$(iquads_src)/interface_to_third_party/libiquads_third_party.a\
		$(iquads_src)/electron_correlation/libiquads_electron_correlation.a\
		$(CPPOBJS)
	$(AR) $(library)  $(CPPOBJS)

$(iquads_src)/blas/libiquads_blas_interface.a:
	cd $(iquads_src)/blas/; make release_blas # make debug_blas

$(iquads_src)/matrix/libiquads_matrix.a:
	cd $(iquads_src)/matrix/; make release_matrix  #make debug_matrix

$(iquads_src)/interface_to_third_party/libiquads_third_party.a:
	cd $(iquads_src)/interface_to_third_party/; make release_third_party  #make debug_third_party

$(iquads_src)/electron_correlation/libiquads_electron_correlation.a:
	cd $(iquads_src)/electron_correlation/; make release_electron_correlation  #make debug_electron_correlation

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

