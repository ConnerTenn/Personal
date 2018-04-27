
P = Build/
gpp=g++ -std=c++17

all: Interconnect

Parser.o: Parser.cpp Parser.h
	$(gpp) Parser.cpp -c -o $(P)Parser.o

InputParser.o: InputParser.cpp Parser.h
	$(gpp) InputParser.cpp -c -o $(P)InputParser.o

Interconnect.o: Interconnect.cpp Interconnect.h
	$(gpp) Interconnect.cpp -c -o $(P)Interconnect.o

Main.o: Main.cpp
	$(gpp) Main.cpp -c -o $(P)Main.o

Interconnect: Main.o Interconnect.o InputParser.o Parser.o
	$(gpp) $(P)Main.o $(P)Interconnect.o $(P)InputParser.o $(P)Parser.o -o $(P)Interconnect

