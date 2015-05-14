SHELL   = /bin/sh
INCLUDE = -I/usr/include/python -I./ -I../

HEADERS = interface.h \
	  py_value.h \
	  py_string.h\
	  py_structure.h\
	  py_vector.h\
	  py_api.h

LIBS    = -L/usr/lib64 -lpython2.7

CXX     = mpic++

CSRC    = interface.cpp\
	  py_value.cpp \
	  py_string.cpp \
	  py_structure.cpp\
	  py_vector.cpp\
	  testpy.cpp
COBJ    = $(CSRC:.cpp=.o)
COPT    = -O2

PGM     = testpy

$(PGM):	$(HEADERS) $(COBJ)
	$(CXX) $(COPT) -o $(PGM) $(INCLUDE) $(COBJ) $(LIBS)

py_value.o: py_value.h py_value.cpp
	$(CXX) $(COPT) -c $(INCLUDE) py_value.cpp

py_string.o: py_string.h py_string.cpp
	$(CXX) $(COPT) -c $(INCLUDE) py_string.cpp

py_structure.o:	py_structure.h py_structure.cpp
	$(CXX) $(COPT) -c $(INCLUDE) py_structure.cpp

py_vector.o: py_vector.h py_vector.cpp ../scf/scf_class_input_ao.h
	$(CXX) $(COPT) -c $(INCLUDE) py_vector.cpp

interface.o: interface.h interface.cpp
	$(CXX) $(COPT) -c $(INCLUDE) interface.cpp

testpy.o: interface.h  py_api.h py_value.h  testpy.cpp
	$(CXX) $(COPT) -c $(INCLUDE) testpy.cpp

clean:
	rm *.o; rm testpy;
