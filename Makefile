CXXFLAGS = -Wall -Wextra
CXX = g++
VPATH = src

.PHONY : clean

all: 02_pointer

02_pointer: 02-pointer.cpp
	$(CXX) $(CXXFLAGS) $? -o bin/$@

clean:
	rm -rf bin/*
