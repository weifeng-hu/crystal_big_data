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
		  report.hpp\
		  setting.hpp\
		  quantity.hpp\
		  report.hpp\
		  correlation_level.hpp

CPPSRCS		= client.cpp\
		  setting.cpp\
		  report.cpp
		  
CPPOBJS		= $(CPPSRCS:.cpp=.o)\

target		= libiquads_electron_correlation.a

all: release

debug: 	CPPOPT += -g -O3\
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

setting.o: $(iquads_src)/iquads/sequence.hpp\
	   $(iquads_src)/structure/molecule.hpp\
	   $(iquads_src)/manybody_expansion/config.hpp\
	   $(iquads_src)/interface_to_third_party/program_mask.hpp\
	   $(iquads_src)/electron_correlation/setting.cpp
	$(CPP) -o setting.o -c $(CPPOPT) $(CPPFLAGS) setting.cpp

report.o: $(iquads_src)/structure/molecule.hpp\
	  $(iquads_src)/electron_correlation/correlation_level.hpp\
	  $(iquads_src)/interface_to_third_party/external_program_report.hpp\
	  $(iquads_src)/electron_correlation/report.cpp
	$(CPP) -o report.o -c $(CPPOPT) $(CPPFLAGS) report.cpp

client.o: $(iquads_src)/iquads/sequence.hpp\
	  $(iquads_src)/electron_correlation/correlation_level.hpp\
	  $(iquads_src)/electron_correlation/client.hpp\
	  $(iquads_src)/electron_correlation/client.cpp
	$(CPP) -o client.o -c $(CPPOPT) $(CPPFLAGS) client.cpp

