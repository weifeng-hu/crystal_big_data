iquads_root	= $(DEV_ROOT)/iquads/
iquads_src	= $(iquads_root)/src/
iquads_bin	= $(iquads_root)/bin/

cc_third_party		= gcc
cpp_third_party		= g++
ar_third_party		= ar -r 

cflags_third_party	= -I$(iquads_src) -I/usr/include
cppflags_third_party	= -std=c++11 -I$(iquads_src) -I/usr/include
cppopt_third_party	= 

cppheads_third_party	= $(iquads_src)/interface_to_third_party/program_mask.hpp\
			  $(iquads_src)/interface_to_third_party/quantity_identifier.h\
			  $(iquads_src)/interface_to_third_party/external_program_request_base.hpp\
			  $(iquads_src)/interface_to_third_party/external_program_config_base.hpp\
			  $(iquads_src)/interface_to_third_party/external_program_agent_factory.hpp\
			  $(iquads_src)/interface_to_third_party/external_program_agent_base.hpp\
			  $(iquads_src)/interface_to_third_party/molpro_config.hpp\
			  $(iquads_src)/interface_to_third_party/molpro_agent.hpp

cppsrcs_third_party		= \
		  		$(iquads_src)/interface_to_third_party/molpro_agent.cpp
cppobjs_third_party		= $(cppsrcs_third_party:.cpp=.o)\

target_third_party		= $(iquads_src)/interface_to_third_party/libiquads_third_party.a

all_third_party: release_third_party

debug_third_party: 	cppopt_third_party += -g\
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
debug_third_party: cppopt_third_party += -O0
debug_third_party: target_third_party

release_third_party: cppopt_third_party +=  -O3
release_third_party: target_third_party

standalone_third_party: cppopt_third_party += -static
#standalone_third_party: we don't have static libary of boost ...
standalone_third_party: target_third_party

clean_third_party:
	rm $(iquads_src)/interface_to_third_party/*.o; rm $(target_third_party)

target_third_party:	$(cppobjs_third_party)
	$(ar_third_party) $(target_third_party) $(cppobjs_third_party)

$(iquads_src)/interface_to_third_party/molpro_agent.o: $(iquads_src)/iquads/sequence.hpp\
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
	$(cpp_third_party) -o $(iquads_src)/interface_to_third_party/molpro_agent.o -c $(cppopt_third_party) $(cppflags_third_party) $(iquads_src)/interface_to_third_party/molpro_agent.cpp

