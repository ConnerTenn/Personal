
#pragma once
#include "WinLib.h"
#include "Cell.h"
#include <random>
#include <thread>
//#include <vector>
//#include <stdlib.h>

//### Window ###

//int Seed = 0;
std::minstd_rand0 Random(0);

bool Done = false;

Window *Win;
	Container *EnvironmentSurface;
	Container *AttributeSurface;
	Container *ControlSurface;

int NumUpdateThreads = 2;
std::thread UpdateControlThread;
std::thread *UpdateThreads;
double UpdateThreadDelta;
int *UpdateThreadState = new int[NumUpdateThreads];
int *UpdateIndex = new int[NumUpdateThreads];
bool UpdateThreadExit = false;
//bool *ThreadSyncA = new bool[MaxUpdateThreads];
//bool *ThreadSyncB = new bool[MaxUpdateThreads];
//bool ProceedA = false;
//bool ProceedB = false;

//int MaxCellUpdateThreads = 3;
//std::thread *CellUpdateThread;// [MaxCellUpdateThreads];
//int NextCellUpdate = 0;
//bool *CellUpdated = new bool[MaxCells];


//### Environment ###

int MaxCells = 200;//1000;
std::vector<Cell *> CellList;
std::vector<Cell *> DeadCellList;
Cell *ActiveCell;
Neuron *ActiveNeuron;

int PlayWidth = 2000;//100000;
int PlayHeight = 2000;//100000;

double EnvironmentViewportX = 0;// -PlayWidth / 2;
double EnvironmentViewportY = 0;// -PlayHeight / 2;
double EnvironmentViewportScale = 1.0;

double NetworkViewportX = 0;// -PlayWidth / 2;
double NetworkViewportY = 0;// -PlayHeight / 2;
double NetworkViewportScale = 1.0;

//### Cell ###

double MinCellSize = 5.0;
double MaxCellSize = 50.0;
double MaxCellSpeed = 3.0;
int NumCellEyes = 1;
double InitialCellEnergy = 100;
double MaxCellHealth = 10;// 100;
int NetworkWidth = 600;
int NetworkHeight = 300;
double MaxCellViewRange = 1000;
int MutationRate = 50;

//### Functions ###

inline int Rand(int min, int max)
{
	//return min + rand() % ((max+1) -min);
	return min + Random() % ((max+1) -min);
}

inline double DRand(double min, double max)
{
	//return min + ((double)rand() / RAND_MAX) * ((max + 1.0) - min);
	//unsigned int Max: 4294967295;
	//factor of num: 1114129;
	return min + ((double)(Random() % 1114129) / (1114129.0)) * ((max) - min);
}

inline double QuadraticRandom(double min, double max, int power, int cycle = 1000)
{
	//return min + (pow(fmod(rand(), cycle), power) / pow(cycle, power - 1)) / cycle * (max - min);
	return min + (pow(fmod(Random(), cycle), power) / pow(cycle, power - 1)) / cycle * (max - min);
}

inline double ApplyTransform(double x, double offset, double scale, double screenCenter)
{
	return (x - offset) * scale + screenCenter;
}

inline double ReverseTransform(double x, double offset, double scale, double screenCenter)
{
	return (x - screenCenter) / scale + offset;
}

inline double Dist(double x1, double y1, double x2, double y2)
{
	return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

#define sgn(val) (val > 0) - (val < 0)

inline double GetAngleFromVertical(double x, double y)
{
	y = -y;
	double d = Dist(x, y, 0, 0);
	double x2 = x / d;
	double y2 = y / d;
	return acos(y2) * sgn(sgn(x2) + 1) + (2.0 * TAU / 4.0 + (TAU / 2.0 - acos(y2))) * (1 - sgn(sgn(x2) + 1));
}

inline double AngleBetweenPoints(double x0, double y0, double x1, double y1, double x2, double y2)
{
	y0 = -y0;
	y1 = -y1;
	y2 = -y2;
	return acos(
		(pow(Dist(x1, y1, x2, y2), 2) - (pow(Dist(x0, y0, x1, y1), 2) + pow(Dist(x0, y0, x2, y2), 2))) / 
		(-2 * Dist(x0, y0, x1, y1) * Dist(x0, y0, x2, y2)));
}
