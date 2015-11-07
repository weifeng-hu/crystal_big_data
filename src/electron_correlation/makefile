iquads_root	= $(DEV_ROOT)/iquads/
iquads_src	= $(iquads_root)/src/
iquads_bin	= $(iquads_root)/bin/

cc_electron_correlation		= gcc
cpp_electron_correlation		= g++
ar_electron_correlation		= ar -r 

cflags_electron_correlation		= -I$(iquads_src) -I/usr/include
cppflags_electron_correlation	= -std=c++11 -I$(iquads_src) -I/usr/include
cppopt_electron_correlation		= 

cppheads_electron_correlation	= $(iquads_src)/electron_correlation/client.hpp\
		  		  $(iquads_src)/electron_correlation/report.hpp\
		  		  $(iquads_src)/electron_correlation/setting.hpp\
		  		  $(iquads_src)/electron_correlation/quantity.hpp\
		  		  $(iquads_src)/electron_correlation/report.hpp\
		  		  $(iquads_src)/electron_correlation/correlation_level.hpp

cppsrcs_electron_correlation	= $(iquads_src)/electron_correlation/client.cpp\
		  		  $(iquads_src)/electron_correlation/setting.cpp\
		  		  $(iquads_src)/electron_correlation/report.cpp
		  
cppobjs_electron_correlation		= $(cppsrcs_electron_correlation:.cpp=.o)\

target_electron_correlation		= $(iquads_src)/electron_correlation/libiquads_electron_correlation.a

all_electron_correlation: release_electron_correlation

debug_electron_correlation: 	cppopt_electron_correlation += -g -O0\
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
debug_electron_correlation: target_electron_correlation

release_electron_correlation: cppopt_electron_correlation +=  -O3
release_electron_correlation: target_electron_correlation

standalone_electron_correlation: cppopt_electron_correlation += -static
#standalone_electron_correlation: we don't have static libary of boost ...
standalone_electron_correlation: target_electron_correlation

clean_electron_correlation:
	rm $(iquads_src)/electron_correlation/*.o; rm $(target_electron_correlation)

target_electron_correlation:	$(cppobjs_electron_correlation)
	$(ar_electron_correlation) $(target_electron_correlation) $(cppobjs_electron_correlation)

$(iquads_src)/electron_correlation/setting.o: $(iquads_src)/iquads/sequence.hpp\
	   $(iquads_src)/structure/molecule.hpp\
	   $(iquads_src)/manybody_expansion/config.hpp\
	   $(iquads_src)/interface_to_third_party/program_mask.hpp\
	   $(iquads_src)/electron_correlation/setting.cpp
	$(cpp_electron_correlation) -o $(iquads_src)/electron_correlation/setting.o -c $(cppopt_electron_correlation) $(cppflags_electron_correlation) $(iquads_src)/electron_correlation/setting.cpp

$(iquads_src)/electron_correlation/report.o: $(iquads_src)/structure/molecule.hpp\
	  $(iquads_src)/electron_correlation/correlation_level.hpp\
	  $(iquads_src)/interface_to_third_party/external_program_report.hpp\
	  $(iquads_src)/electron_correlation/report.cpp
	$(cpp_electron_correlation) -o $(iquads_src)/electron_correlation/report.o -c $(cppopt_electron_correlation) $(cppflags_electron_correlation) $(iquads_src)/electron_correlation/report.cpp

$(iquads_src)/electron_correlation/client.o: $(iquads_src)/iquads/sequence.hpp\
	  $(iquads_src)/electron_correlation/correlation_level.hpp\
	  $(iquads_src)/electron_correlation/client.hpp\
	  $(iquads_src)/electron_correlation/client.cpp
	$(cpp_electron_correlation) -o $(iquads_src)/electron_correlation/client.o -c $(cppopt_electron_correlation) $(cppflags_electron_correlation) $(iquads_src)/electron_correlation/client.cpp

