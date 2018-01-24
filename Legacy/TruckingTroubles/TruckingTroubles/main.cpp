
#include <iostream>
#include <vector>
#include <fstream>
#include <string>

#ifndef MIN
#define MIN(a,b) (a<b?a:b)
#endif // !MIN

#ifndef MAX
#define MAX(a,b) (a>b?a:b)
#endif // !MIN


struct Segment
{
	int Pos1;
	int Pos2;
	int Value;
};

std::ofstream oFile;

std::vector<Segment> SegmentList;
std::vector<int> DestinationList;
int NumNodes;
int NumSegments;
int NumDestinations;

int **Matrix[2];
int MatAddr = 0;

void InitMatrix()
{
	for (int i = 0; i < 2; i++)
	{
		MatAddr = i;
		Matrix[MatAddr] = new int *[NumNodes];
		for (int y = 0; y < NumNodes; y++)
		{
			Matrix[MatAddr][y] = new int[NumNodes];
			for (int x = 0; x < NumNodes; x++)
			{
				Matrix[MatAddr][y][x] = x == y ? -1 : -2;
			}
		}
	}
}

void DeleteMatrix()
{
	for (int i = 0; i < 2; i++)
	{
		MatAddr = i;
		for (int y = 0; y < NumNodes; y++)
		{
			delete[] Matrix[MatAddr][y]; Matrix[MatAddr][y] = 0;
		}
		delete[] Matrix[MatAddr]; Matrix[MatAddr] = 0;
	}
}

void MatCopy(int src, int dest)
{
	for (int y = 0; y < NumNodes; y++)
	{
		for (int x = 0; x < NumNodes; x++)
		{
			Matrix[dest][y][x] = Matrix[src][y][x];
		}
	}
}

void MatClear(int mat)
{
	for (int y = 0; y < NumNodes; y++)
	{
		for (int x = 0; x < NumNodes; x++)
		{
			Matrix[mat][y][x] = x == y ? -1 : -2;
		}
	}
}

void Input()
{
	std::ifstream file;
	file.open("In.txt");
	std::string in;	std::getline(file, in);

	size_t pos = 0, found = 0;

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

		SegmentList.push_back({ pos1, pos2, value });
	}

	for (int i = 0; i < NumDestinations; i++)
	{
		std::getline(file, in);

		DestinationList.push_back(stoi(in) - 1);
	}

	file.close();
}

void DisplayMatrix()
{
	oFile << "   "; for (int x = 0; x < NumNodes; x++) { oFile << x << "  "; } oFile << "\n";
	for (int y = 0; y < NumNodes; y++)
	{
		oFile << y << ": ";
		for (int x= 0; x < NumNodes; x++)
		{
			std::string out = std::to_string(Matrix[MatAddr][y][x]);
			if (out == "-1") { out = "-"; } else if (out == "-2") { out = "~"; }
			out = out + std::string(3-out.length(), ' ');
			out = out.substr(0, 4);
			oFile << out;
		}
		oFile << "\n\n";
	}
}

void ParseIntoMatrix()
{
	for (int i = 0; i < SegmentList.size(); i++)
	{
		Matrix[MatAddr][SegmentList[i].Pos1][SegmentList[i].Pos2] = SegmentList[i].Value;
		Matrix[MatAddr][SegmentList[i].Pos2][SegmentList[i].Pos1] = SegmentList[i].Value;
	}
}

void CalculateNextDegree()
{
	MatClear(1 - MatAddr);
	for (int start = 0; start < NumNodes; start++)//horizontal
	{
		for (int destination = start + 1; destination < NumNodes; destination++)//horizontal
		{
			//find best route to destination
			int valueDown = -2;//stores best route value
			for (int y = 0; y < NumNodes; y++)
			{
				if (Matrix[MatAddr][y][start] >= 0 && Matrix[MatAddr][y][destination] >= 0)
				{
					//find the min across the horizontal
					//and the max between those min_horizontals 
					valueDown = MAX(valueDown, MIN(Matrix[MatAddr][y][start], Matrix[MatAddr][y][destination]));
				}
			}

			Matrix[1-MatAddr][start][destination] = valueDown;
			Matrix[1-MatAddr][destination][start] = valueDown;
		}
	}

	MatAddr = 1 - MatAddr;
}

void main()
{
	oFile.open("Out.txt");

	Input();
	
	InitMatrix();

	ParseIntoMatrix();

	oFile << "Base Matrix:\n1 Steps:\n";
	DisplayMatrix();

	for (int i = 0; i < NumNodes; i++)
	{
		CalculateNextDegree();

		oFile << i*2 + 2 << " Steps:\n";
		DisplayMatrix();
	}

	DeleteMatrix();

	//std::string out = "Press Enter To Continue";
	//oFile << out;
	//std::getline(std::cin, out);
	oFile.close();
}
