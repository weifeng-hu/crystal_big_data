
cc_manybody_expansion	= $(cc_iquads)
cpp_manybody_expansion	= $(cpp_iquads)
fc_manybody_expansion		= $(fc_iquads)
ar_manybody_expansion		= $(ar_iquads)
install_manybody_expansion	= $(install_iquads)

cflags_manybody_expansion	= $(cflags_iquads)
cppflags_manybody_expansion	= $(cppflags_iquads)
fflags_manybody_expansion	= $(fflags_iquads)

copt_manybody_expansion	= $(copt_iquads)
cppopt_manybody_expansion	= $(cppopt_iquads)
fopt_manybody_expansion	= $(fopt_iquads)

cppheads_manybody_expansion	= $(iquads_src)/manybody_expansion/client.hpp\
				  $(iquads_src)/manybody_expansion/agent.hpp\
				  $(iquads_src)/manybody_expansion/command_setting.hpp\
				  $(iquads_src)/manybody_expansion/request.hpp\
				  $(iquads_src)/manybody_expansion/report.hpp\
				  $(iquads_src)/manybody_expansion/config.hpp\
				  $(iquads_src)/manybody_expansion/manybody_expansion_template.hpp\
				  $(iquads_src)/manybody_expansion/expansion_formula_periodic_traits.hpp\
				  $(iquads_src)/manybody_expansion/expansion_formula_periodic_with_fragment_identification_traits.hpp\
				  $(iquads_src)/manybody_expansion/compute_expansion_term_periodic_traits.hpp\
				  $(iquads_src)/manybody_expansion/compute_expansion_term_periodic_with_fragment_identification_traits.hpp\
				  $(iquads_src)/manybody_expansion/compute_interaction_energy_traits.hpp\
				  $(iquads_src)/manybody_expansion/fragment_info_template.hpp\
				  $(iquads_src)/manybody_expansion/fragment_group_info_template.hpp\
				  $(iquads_src)/manybody_expansion/fragment_signature_database.hpp\
				  $(iquads_src)/manybody_expansion/fragment_signature_identifier_template.hpp\
				  $(iquads_src)/manybody_expansion/order_mask.hpp


cppsrcs_manybody_expansion	= \
				  $(iquads_src)/manybody_expansion/request.cpp\
				  $(iquads_src)/manybody_expansion/config.cpp\
				  $(iquads_src)/manybody_expansion/report.cpp\
				  $(iquads_src)/manybody_expansion/client.cpp\
				  $(iquads_src)/manybody_expansion/agent.cpp

cppobjs_manybody_expansion	= $(cppsrcs_manybody_expansion:.cpp=.o)

lib_manybody_expansion		= -L$(iquads_lib) -liquads_manybody_expansion -liquads_electron_correlation -liquads_third_party -liquads_matrix -liquads_blas_interface $(lib_iquads)
#  -L/home/intel/compilers_and_libraries/linux/lib/intel64 -liomp5 -lifcore -lifport -limf -lirc -lintlc

executable_manybody_expansion	= $(iquads_src)/manybody_expansion/iquads_manybody_expansion
library_manybody_expansion	= $(iquads_src)/manybody_expansion/libiquads_manybody_expansion.a
shared_library_manybody_expansion	= $(iquads_src)/manybody_expansion/libiquads_manybody_expansion.so

all: release_manybody_expansion

debug_manybody_expansion: 	cppopt_manybody_expansion += -g \
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
debug_manybody_expansion: library_manybody_expansion shared_library_manybody_expansion
debug_manybody_expansion: executable_manybody_expansion

release_manybody_expansion: cppopt_manybody_expansion += 
release_manybody_expansion: copt_manybody_expansion += 
release_manybody_expansion: fopt_manybody_expansion += 
release_manybody_expansion: library_manybody_expansion shared_library_manybody_expansion
release_manybody_expansion: executable_manybody_expansion

standalone: cppopt_manybody_expansion += -static
#standalone: deprecated we don't have static libary of boost ...
standalone: executable_manybody_expansion
standalone: library_manybody_expansion

clean_manybody_expansion:
	rm $(cppobjs_manybody_expansion); rm $(executable_manybody_expansion) $(library_manybody_expansion) $(shared_library_manybody_expansion);

executable_manybody_expansion:	\
		$(iquads_src)/manybody_expansion/main.o $(cppobjs_manybody_expansion)
	$(cpp_manybody_expansion) -o $(executable_manybody_expansion) $(cppflags_manybody_expansion) $(cppopt_manybody_expansion) $(iquads_src)/manybody_expansion/main.o $(cppobjs_manybody_expansion) $(lib_manybody_expansion)
	$(install_manybody_expansion) $(executable_manybody_expansion) $(iquads_bin)

library_manybody_expansion:	\
		$(cppobjs_manybody_expansion)
	$(ar_manybody_expansion) $(library_manybody_expansion)  $(cppobjs_manybody_expansion); $(install_manybody_expansion) $(library_manybody_expansion) $(iquads_lib)

shared_library_manybody_expansion:
	g++ -shared -o $(shared_library_manybody_expansion) $(cppobjs_manybody_expansion); $(install_manybody_expansion) $(shared_library_manybody_expansion) $(iquads_lib)

$(iquads_src)/blas/libiquads_blas_interface.a:
	cd $(iquads_src)/blas/; make release_blas # make debug_manybody_expansion_blas

$(iquads_src)/matrix/libiquads_matrix.a:
	cd $(iquads_src)/matrix/; make release_matrix  #make debug_manybody_expansion_matrix

$(iquads_src)/interface_to_third_party/libiquads_third_party.a:
	cd $(iquads_src)/interface_to_third_party/; make release_third_party  #make debug_manybody_expansion_third_party

$(iquads_src)/electron_correlation/libiquads_electron_correlation.a:
	cd $(iquads_src)/electron_correlation/; make release_electron_correlation  #make debug_manybody_expansion_electron_correlation

$(iquads_src)/manybody_expansion/main.o: $(iquads_src)/iquads/command_parser.hpp\
					$(iquads_src)/manybody_expansion/client.hpp\
					$(iquads_src)/manybody_expansion/client.cpp\
					$(iquads_src)/manybody_expansion/main.cpp
	$(cpp_manybody_expansion) -o $(iquads_src)/manybody_expansion/main.o -c $(cppopt_manybody_expansion) $(cppflags_manybody_expansion) $(iquads_src)/manybody_expansion/main.cpp

$(iquads_src)/manybody_expansion/request.o: $(iquads_src)/manybody_expansion/request.hpp\
					   $(iquads_src)/manybody_expansion/request.cpp
	$(cpp_manybody_expansion) -o $(iquads_src)/manybody_expansion/request.o -c $(cppopt_manybody_expansion) $(cppflags_manybody_expansion) $(iquads_src)/manybody_expansion/request.cpp

$(iquads_src)/manybody_expansion/config.o: $(iquads_src)/interface_to_third_party/program_mask.hpp\
					  $(iquads_src)/manybody_expansion/config.hpp\
					  $(iquads_src)/manybody_expansion/config.cpp
	$(cpp_manybody_expansion) -o $(iquads_src)/manybody_expansion/config.o -c $(cppopt_manybody_expansion) $(cppflags_manybody_expansion) $(iquads_src)/manybody_expansion/config.cpp

$(iquads_src)/manybody_expansion/report.o: $(iquads_src)/manybody_expansion/report.hpp\
					  $(iquads_src)/manybody_expansion/report.cpp
	$(cpp_manybody_expansion) -o $(iquads_src)/manybody_expansion/report.o -c $(cppopt_manybody_expansion) $(cppflags_manybody_expansion) $(iquads_src)/manybody_expansion/report.cpp

$(iquads_src)/manybody_expansion/client.o: $(iquads_src)/iquads/command_parser.hpp\
					  $(iquads_src)/manybody_expansion/command_setting.hpp\
					  $(iquads_src)/manybody_expansion/config.hpp\
					  $(iquads_src)/manybody_expansion/report.hpp\
					  $(iquads_src)/manybody_expansion/client.cpp
	$(cpp_manybody_expansion) -o $(iquads_src)/manybody_expansion/client.o -c $(cppopt_manybody_expansion) $(cppflags_manybody_expansion) $(iquads_src)/manybody_expansion/client.cpp

$(iquads_src)/manybody_expansion/agent.o: $(iquads_src)/interface_to_third_party/external_program_agent_base.hpp\
					 $(cppheads_manybody_expansion)\
					 $(iquads_src)/manybody_expansion/agent.cpp
	$(cpp_manybody_expansion) -o $(iquads_src)/manybody_expansion/agent.o -c $(cppopt_manybody_expansion) $(cppflags_manybody_expansion) $(iquads_src)/manybody_expansion/agent.cpp

