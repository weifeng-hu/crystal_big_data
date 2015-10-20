iquads_root     = $(DEV_ROOT)/iquads/
iquads_src      = $(iquads_root)/src/
iquads_bin      = $(iquads_root)/bin/
CC              = gcc
CPP             = g++
CPPOPT		= -g -O0 -std=c++11
CPPFLAGS        = -I/usr/include -I$(iquads_src)
CHEADS          =
CPPSRCS         =\
		main.cpp
CPPOBJS         = $(CPPSRCS:.cpp=.o)
LIBS            = $(iquads_src)/manybody_expansion/libiquads_manybody_expansion.a\
		  $(iquads_src)/electron_correlation/libiquads_electron_correlation.a\
		  $(iquads_src)/interface_to_third_party/libiquads_third_party.a\
		  -L/usr/lib64 -lboost_filesystem -lboost_date_time -lboost_system
executable      = test

$(executable): $(CPPOBJS)
	$(CPP) -o $(executable) $(CPPFLAGS) $(CPPOPT) $(CPPOBJS) $(LIBS)

main.o: ../*.hpp main.cpp
	$(CPP) -o main.o -c $(CPPFLAGS) $(CPPOPT) main.cpp

clean:
	rm *.o; rm $(executable);
