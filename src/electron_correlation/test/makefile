IQUADS_ROOT     = /home/wh288/Development/iquads/
IQUADS_SRC      = $(IQUADS_ROOT)/src/
IQUADS_BIN      = $(IQUADS_ROOT)/bin/
CC              = gcc
CXX             = g++
COPT		= -g\
-Wextra -Wcast-align \
-Wcast-qual -Wconversion \
-Wdisabled-optimization \
-Wfloat-equal -Wformat=2 \
-Wformat-nonliteral -Wformat-security  \
-Wformat-y2k \
-Wimport  -Winit-self  -Winline \
-Winvalid-pch   \
-Wlong-long \
-Wmissing-field-initializers -Wmissing-format-attribute   \
-Wmissing-include-dirs -Wmissing-noreturn \
-Wpacked  -Wpointer-arith \
-Wredundant-decls \
-Wstack-protector \
-Wstrict-aliasing=2 -Wswitch-default \
-Wswitch-enum \
-Wunreachable-code \
-Wunused-parameter \
-Wvariadic-macros \
-Wwrite-strings -std=c++11
CFLAGS          = -I$(IQUADS_SRC)
CHEADS          =
CSRCS           = main.cpp\
		  client.cpp\
		  molpro_agent.cpp
COBJS           = $(CSRCS:.cpp=.o)
LIBS            =
PGM             = test_electron_correlation

$(PGM): $(COBJS)
	$(CXX) -o $(PGM) $(CFLAGS) $(COPT) $(COBJS) $(LIBS); cp $(PGM) $(IQUADS_BIN)

main.o: ../*.hpp ./main.cpp
	$(CXX) -c $(CFLAGS) $(COPT) ./main.cpp

client.o: ../*.hpp ../client.cpp
	$(CXX) -c $(CFLAGS) $(COPT) ../client.cpp

molpro_agent.o: ../../interface_to_third_party/molpro_agent.cpp
	$(CXX) -c $(CFLAGS) $(COPT) ../../interface_to_third_party/molpro_agent.cpp

clean:
	rm *.o; rm $(PGM); rm $(IQUADS_BIN)/$(PGM)
