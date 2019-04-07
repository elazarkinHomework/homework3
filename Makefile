#!make -f

all: test
	./$<

demo: PhysicalNumberDemo.o PhysicalNumber.o
	clang++-5.0 -std=c++17 $^ -o demo

test: PhysicalNumberTest.o PhysicalNumber.o
	clang++-5.0 -std=c++17 $^ -o test

%.o: %.cpp
	clang++-5.0 -std=c++17 --compile $< -o $@

PhysicalNumber.o: PhysicalNumber.h Unit.h

PhysicalNumberDemo.o: PhysicalNumber.cpp Unit.h

PhysicalNumberTest.o: PhysicalNumber.cpp Unit.h badkan.hpp

clean:
	rm -f *.o demo test
