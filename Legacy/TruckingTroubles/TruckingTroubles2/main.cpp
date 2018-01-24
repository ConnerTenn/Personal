
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <time.h>

#ifndef MIN
#define MIN(a,b) ((a)<(b)?(a):(b))
#endif // !MIN

#ifndef MAX
#define MAX(a,b) ((a)>(b)?(a):(b))
#endif // !MIN


struct Segment
{
	int Pos1;
	int Pos2;
	int Value;
};

std::ofstream oFile;

//std::vector<Segment> SegmentList;
Segment *SegmentList;
//std::vector<int> DestinationList;
int *DestinationList;
int NumNodes;
int NumSegments;
int NumDestinations;

int ***Matrix;
int *Destinations;
//int MatAddr = 0;

std::string ConstantLength(std::string str, int length)
{
	str = str + std::string(MAX(0,length-(int)str.length()), ' ');
	str = str.substr(0, length);
	return str;
}

inline void InitMatrix(int matAddr)
{
	Matrix[matAddr] = new int *[NumNodes];
	for (int y = 0; y < NumNodes; y++)
	{
		Matrix[matAddr][y] = new int[NumNodes];
		for (int x = 0; x < NumNodes; x++)
		{
			Matrix[matAddr][y][x] = x == y ? -1 : -2;
		}
	}
}

inline void DeleteMatrix(int matAddr)
{
	for (int y = 0; y < NumNodes; y++)
	{
		delete[] Matrix[matAddr][y]; Matrix[matAddr][y] = 0;
	}
	delete[] Matrix[matAddr]; Matrix[matAddr] = 0;
}

inline void MatCopy(int src, int dest)
{
	for (int y = 0; y < NumNodes; y++)
	{
		for (int x = 0; x < NumNodes; x++)
		{
			Matrix[dest][y][x] = Matrix[src][y][x];
		}
	}
}

inline void MatSwap(int mat1, int mat2)
{
	int **reg = Matrix[mat1];
	Matrix[mat1] = Matrix[mat2];
	Matrix[mat2] = reg;
}

inline void MatClear(int mat)
{
	for (int y = 0; y < NumNodes; y++)
	{
		for (int x = 0; x < NumNodes; x++)
		{
			Matrix[mat][y][x] = (x == y ? -1 : -2);
		}
	}
}

inline void ParseIntoMatrix(int matAddr)
{
	for (int i = 0; i < NumSegments; i++)
	{
		Matrix[matAddr][SegmentList[i].Pos1][SegmentList[i].Pos2] = SegmentList[i].Value;
		Matrix[matAddr][SegmentList[i].Pos2][SegmentList[i].Pos1] = SegmentList[i].Value;
	}
}

/*void DisplayMatrix(int matAddr)
{
	oFile << "     "; for (int x = 0; x < NumNodes; x++) { oFile << ConstantLength(std::to_string(x),3); } oFile << "\n";
	for (int y = 0; y < NumNodes; y++)
	{
		oFile << ConstantLength(std::to_string(y),3) << ": ";
		for (int x = 0; x < NumNodes; x++)
		{
			std::string out = std::to_string(Matrix[matAddr][y][x]);
			if (out == "-1") { out = "-"; }
			else if (out == "-2") { out = "~"; }
			oFile << ConstantLength(out,3);
		}
		oFile << "\n";
	}
}*/

void DisplayMatrix(int matAddr)
{
	std::string out;
	out += "     "; for (int x = 0; x < NumNodes; x++) { out += ConstantLength(std::to_string(x), 3); } out += "\n";
	for (int y = 0; y < NumNodes; y++)
	{
		out += ConstantLength(std::to_string(y), 3) + ": ";
		for (int x = 0; x < NumNodes; x++)
		{
			std::string val = std::to_string(Matrix[matAddr][y][x]);
			if (val == "-1") { val = "-"; }
			else if (val == "-2") { val = "~"; }
			out += ConstantLength(val, 3);
		}
		out += "\n";
	}
	oFile << out;
}


inline void InitDestinations()
{
	Destinations = new int[NumNodes];
	for (int i = 0; i < NumNodes; i++) { Destinations[i] = -1; }
}

inline void UpdateDestinations(int src, int node = 0)
{
	for (int i = 0; i < NumNodes; i++)
	{
		Destinations[i] = MAX(Destinations[i], Matrix[src][node][i]);
	}
}

void DisplayDestinations()
{
	oFile << "DST: ";
	for (int i = 0; i < NumNodes; i++)
	{
		std::string out = std::to_string(Destinations[i]);
		if (out == "-1") { out = "-"; }
		oFile << ConstantLength(out, 3);
	}
}


void Input()
{
	std::ifstream file;
	file.open("In.txt");
	std::string in;	std::getline(file, in);

	size_t pos = 0, found = 0;
	//SegmentList.clear();
	
	found = in.find(" ", pos);
	NumNodes = stoi(in.substr(pos, found - pos));
	pos = found + 1;

	found = in.find(" ", pos);
	NumSegments = stoi(in.substr(pos, found - pos));
	pos = found + 1;

	found = in.find(" ", pos);
	NumDestinations = stoi(in.substr(pos, found - pos));
	pos = found + 1;
	
	oFile << "Nodes:" << NumNodes << " Segments:" << NumSegments << " Destinations:" << NumDestinations << "\n";
	SegmentList = new Segment[NumSegments];
	DestinationList = new int[NumDestinations];
	
	
	for (int i = 0; i < NumSegments; i++)
	{
		std::getline(file, in);
		pos = 0, found = 0;

		found = in.find(" ", pos);
		int pos1 = stoi(in.substr(pos, found - pos)) - 1;
		pos = found + 1;

		found = in.find(" ", pos);
		int pos2 = stoi(in.substr(pos, found - pos)) - 1;
		pos = found + 1;

		found = in.find(" ", pos);
		int value = stoi(in.substr(pos, found - pos));
		pos = found + 1;

		//SegmentList.push_back({ pos1, pos2, value });
		SegmentList[i] = { pos1, pos2, value };
	}

	for (int i = 0; i < NumDestinations; i++)
	{
		std::getline(file, in);

		//DestinationList.push_back(stoi(in) - 1);
		DestinationList[i] = stoi(in) - 1;
	}

	file.close();
}

inline void DeleteLists()
{
	delete[] Destinations; Destinations = 0;
	delete[] SegmentList;
	delete[] DestinationList;
}




void CalculateNextDegree(int src1, int src2, int dest)
{
	//int reg1, reg2;
	//MatClear(dest);
	for (int start = 0; start < NumNodes; start++)//horizontal
	{
		for (int destination = start + 1; destination < NumNodes; destination++)//horizontal
		{
			//find best route to destination
			int valueDown = -2;//stores best route value. initilizes to invalid pos
			for (int y = 0; y < NumNodes; y++)
			{
				if (Matrix[src1][y][start] >= 0 && Matrix[src2][y][destination] >= 0)//if position is valid
				{
					//find the min across the horizontal
					//and the max between those min_horizontals 
					valueDown = MAX(valueDown, MIN(Matrix[src1][y][start], Matrix[src2][y][destination]));

					//reg1 = Matrix[src1][y][start]; reg2 = Matrix[src2][y][destination];
					//valueDown = MAX(valueDown, MIN(reg1, reg2));
				}
			}
			
			//record the current best into matrix
			Matrix[dest][start][destination] = valueDown;
			Matrix[dest][destination][start] = valueDown;
		}
	}
}



void main()
{
	int beginTime = clock();

	oFile.open("Out.txt");

	Input();
	
	Matrix = new int **[3]; for (int i = 0; i < 3; i++) { InitMatrix(i); }
	InitDestinations();
	
	/*
	Matrix Assignments:

	Matrix[0]: Base Matrix
	Matrix[1]: current Matrix
	Matrix[2]: Destination (Reg)
	*/

	ParseIntoMatrix(0);
	MatCopy(0, 1);
	UpdateDestinations(0);

	oFile << "Base Matrix:\n1 Steps:\n";
	DisplayMatrix(0); oFile << "\n";
	DisplayDestinations(); oFile << "\n\n";

	for (int i = 0; i < NumNodes - 1; i++)
	{
		//0 is the original matrix
		//1 is the active matrix
		CalculateNextDegree(0,1,2); //store in 2
		MatSwap(1, 2); //copy 2 into 1
		UpdateDestinations(1);

		oFile << i + 2 << " Steps:\n";
		DisplayMatrix(1); oFile << "\n";
		DisplayDestinations(); oFile << "\n\n";
	}

	{/*Calculate Result*/}
	{
		int result = Destinations[DestinationList[0]];
		for (int i = 1; i < NumDestinations; i++)
		{
			result = MIN(result, Destinations[DestinationList[i]]);
		}

		oFile << "\nResult:" << result << "\nTime:" << double((clock()-beginTime))/1000.0 << "\n";
	}
	
	//cleanup
	for (int i = 0; i < 3; i++) { DeleteMatrix(i); } delete[] Matrix;  Matrix = 0;
	DeleteLists();

	//std::string out = "Press Enter To Continue";
	//oFile << out;
	//std::getline(std::cin, out);
	oFile.close();
}
