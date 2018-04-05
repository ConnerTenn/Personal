
P = LinuxBuild/

all: Interconnect

Parser.o: Parser.cpp Parser.h
	g++ Parser.cpp -c -o $(P)Parser.o

InputParser.o: InputParser.cpp Parser.h
	g++ InputParser.cpp -c -o $(P)InputParser.o

Interconnect.o: Interconnect.cpp Interconnect.h
	g++ Interconnect.cpp -c -o $(P)Interconnect.o

Main.o: Main.cpp
	g++ Main.cpp -c -o $(P)Main.o

Interconnect: Main.o Interconnect.o InputParser.o Parser.o
	g++ $(P)Main.o $(P)Interconnect.o $(P)InputParser.o $(P)Parser.o -o $(P)Interconnect
