iquads_root	= $(DEV_ROOT)/iquads/
iquads_src	= $(iquads_root)/src/
iquads_bin	= $(iquads_root)/bin/

cc_manybody_expansion		= gcc
cpp_manybody_expansion		= g++
ar_manybody_expansion		= ar -r

cflags_manybody_expansion	= -I$(iquads_src) -I/usr/include
cppflags_manybody_expansion	= -std=c++11 -I$(iquads_src) -I/usr/include
cppopt_manybody_expansion	= 

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
libs_manybody_expansion		= $(iquads_src)/electron_correlation/libiquads_electron_correlation.a\
		  		  $(iquads_src)/interface_to_third_party/libiquads_third_party.a\
		  		  $(iquads_src)/matrix/libiquads_matrix.a\
		  		  $(iquads_src)/blas/libiquads_blas_interface.a\
		  		  -L/usr/lib64 -lboost_filesystem -lboost_date_time -lboost_system\
		  		  -L/home/intel/compiler_and_libraries/linux/mkl/lib/intel64 -lmkl_intel_lp64 -lmkl_sequential -lmkl_core -lpthread -lm\
			          -lgfortran 
	#  -L/home/intel/compilers_and_libraries/linux/lib/intel64 -liomp5 -lifcore -lifport -limf -lirc -lintlc

executable_manybody_expansion	= $(iquads_src)/manybody_expansion/iquads_manybody_expansion
library_manybody_expansion	= $(iquads_src)/manybody_expansion/libiquads_manybody_expansion.a

default: all

all: release_manybody_expansion

include $(iquads_src)/blas/makefile
include $(iquads_src)/matrix/makefile
include $(iquads_src)/interface_to_third_party/makefile
include $(iquads_src)/electron_correlation/makefile

debug_manybody_expansion: 	cppopt_manybody_expansion += -g -O0\
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
debug_manybody_expansion: library_manybody_expansion
debug_manybody_expansion: executable_manybody_expansion

release_manybody_expansion: cppopt_manybody_expansion +=  -O3 -fopenmp
release_manybody_expansion: cppopt_manybody_expansion += 
release_manybody_expansion: library_manybody_expansion
release_manybody_expansion: executable_manybody_expansion

standalone: cppopt_manybody_expansion += -static
#standalone: we don't have static libary of boost ...
standalone: executable_manybody_expansion
standalone: library_manybody_expansion

clean_manybody_expansion:
	rm *.o; rm $(executable_manybody_expansion) $(library_manybody_expansion);

distclean:
	make clean_blas; make clean_matrix; make clean_third_party; make clean_electron_correlation; make clean_manybody_expansion

executable_manybody_expansion:	\
		$(iquads_src)/blas/libiquads_blas_interface.a\
		$(iquads_src)/matrix/libiquads_matrix.a\
		$(iquads_src)/interface_to_third_party/libiquads_third_party.a\
		$(iquads_src)/electron_correlation/libiquads_electron_correlation.a\
		$(iquads_src)/manybody_expansion/main.o $(cppobjs_manybody_expansion)
	$(cpp_manybody_expansion) -o $(executable_manybody_expansion) $(cppflags_manybody_expansion) $(cppopt_manybody_expansion) $(iquads_src)/manybody_expansion/main.o $(cppobjs_manybody_expansion) $(libs_manybody_expansion)
	cp $(executable_manybody_expansion) $(iquads_bin)

library_manybody_expansion:	\
		$(iquads_src)/blas/libiquads_blas_interface.a\
		$(iquads_src)/matrix/libiquads_matrix.a\
		$(iquads_src)/interface_to_third_party/libiquads_third_party.a\
		$(iquads_src)/electron_correlation/libiquads_electron_correlation.a\
		$(cppobjs_manybody_expansion)
	$(ar_manybody_expansion) $(library_manybody_expansion)  $(cppobjs_manybody_expansion)

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

