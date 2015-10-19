IQUADS_ROOT     = /home/wh288/Development/iquads/
IQUADS_SRC      = $(IQUADS_ROOT)/src/
IQUADS_BIN      = $(IQUADS_ROOT)/bin/
CC              = gcc
CXX             = g++
COPT		= -g\
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
-Wwrite-strings -std=c++11
#-Wunused-parameter
#-Wconversion
#-Wcast-qual
CFLAGS          = -I/usr/include/ -I$(IQUADS_SRC)
CHEADS          =
CSRCS           = main.cpp\
		  client.cpp\
		  setting.cpp\
		  report.cpp\
		  molpro_agent.cpp
COBJS           = $(CSRCS:.cpp=.o)
LIBS            = -L/usr/lib64 -lboost_filesystem -lboost_system
PGM             = test_electron_correlation

$(PGM): $(COBJS)
	$(CXX) -o $(PGM) $(CFLAGS) $(COPT) $(COBJS) $(LIBS); cp $(PGM) $(IQUADS_BIN)

main.o: ../*.hpp ./main.cpp
	$(CXX) -c $(CFLAGS) $(COPT) ./main.cpp

setting.o: ../*.hpp
	$(CXX) -c $(CFLAGS) $(COPT) ../setting.cpp

client.o: ../*.hpp ../client.cpp
	$(CXX) -c $(CFLAGS) $(COPT) ../client.cpp

report.o: ../*.hpp ../report.cpp
	$(CXX) -c $(CFLAGS) $(COPT) ../report.cpp

molpro_agent.o: ../../interface_to_third_party/molpro_agent.cpp
	$(CXX) -c $(CFLAGS) $(COPT) ../../interface_to_third_party/molpro_agent.cpp

clean:
	rm *.o; rm $(PGM); rm $(IQUADS_BIN)/$(PGM)
