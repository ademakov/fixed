CXXFLAGS=-std=c++17 -Wall

LINK.o=$(LINK.cc)

.PHONY: all
all:	fixed

fixed:	fixed.o

.PHONY: clean
clean:
	rm -fv *.o fixed

