iquads_root	= $(DEV_ROOT)/iquads/
iquads_src	= $(iquads_root)/src/
iquads_bin	= $(iquads_root)/bin/

CC		= gcc
CPP		= g++
AR		= ar -r 

CFLAGS		= -I$(iquads_src) -I/usr/include
CPPFLAGS	= -std=c++11 -I$(iquads_src) -I/usr/include
CPPOPT		= 

CPPHEADS	= program_mask.hpp\
		  quantity_identifier.h\
		  external_program_request_base.hpp\
		  external_program_config_base.hpp\
		  external_program_agent_factory.hpp\
		  external_program_agent_base.hpp\
		  molpro_config.hpp\
		  molpro_agent.hpp

CPPSRCS		= \
		  molpro_agent.cpp
CPPOBJS		= $(CPPSRCS:.cpp=.o)\

target		= libiquads_third_party.a

all: release

debug: 	CPPOPT += -g\
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
		  -Wwrite-strings
debug: CPPOPT += -O3
debug: target

release: CPPOPT +=  -O3
release: target

standalone: CPPOPT += -static
#standalone: we don't have static libary of boost ...
standalone: target

clean:
	rm *.o; rm $(target)

target:	$(CPPOBJS)
	$(AR) $(target) $(CPPOBJS)

molpro_agent.o: $(iquads_src)/iquads/sequence.hpp\
		$(iquads_src)/structure/coordinate_representation.hpp\
		$(iquads_src)/structure/atom_list.hpp\
		$(iquads_src)/structure/molecule.hpp\
		$(iquads_src)/utility/convert_string_to.hpp\
		$(iquads_src)/file_system/file_functions.hpp\
		$(iquads_src)/file_system/filepath.hpp\
		$(iquads_src)/file_system/directory.hpp\
		$(iquads_src)/chemistry/periodic_table.hpp\
		$(iquads_src)/electron_correlation/quantity.hpp\
		$(iquads_src)/electron_correlation/correlation_level.hpp\
		$(iquads_src)/interface_to_third_party/external_program_agent_base.hpp\
		$(iquads_src)/interface_to_third_party/external_program_report.hpp\
		$(iquads_src)/interface_to_third_party/external_program_request.hpp\
		$(iquads_src)/interface_to_third_party/external_program_config_base.hpp\
		$(iquads_src)/interface_to_third_party/external_program_report.hpp\
		$(iquads_src)/interface_to_third_party/molpro_config.hpp\
		$(iquads_src)/interface_to_third_party/molpro_agent.hpp\
		$(iquads_src)/interface_to_third_party/molpro_agent.cpp
	$(CPP) -o molpro_agent.o -c $(CPPOPT) $(CPPFLAGS) molpro_agent.cpp

