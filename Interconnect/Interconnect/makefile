
P = LinuxBuild/

all: main

Parser.o: Parser.cpp Parser.h
	g++ Parser.cpp -c -o $(P)Parser.o

InputParser.o: InputParser.cpp Parser.h
	g++ InputParser.cpp -c -o $(P)InputParser.o

Interconnect.o: Interconnect.cpp Interconnect.h
	g++ Interconnect.cpp -c -o $(P)Interconnect.o

main: Interconnect.o InputParser.o Parser.o
	g++ Main.cpp $(P)Interconnect.o $(P)InputParser.o $(P)Parser.o -o $(P)Interconnect
