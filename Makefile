CXX=g++
CXXFLAGS=-std=c++17 -Wall

all: mini_db

mini_db: main.o parser.o database.o
	$(CXX) $(CXXFLAGS) -o mini_db main.o parser.o database.o

main.o: main.cpp parser.hpp database.hpp
parser.o: parser.cpp parser.hpp
database.o: database.cpp database.hpp parser.hpp

clean:
	rm -f *.o mini_db
