
#pragma once
#include "WinLib.h"
#include "Cell.h"
#include <random>
#include <thread>
//#include <vector>
//#include <stdlib.h>

//### Types ###

template<typename T>
struct Register
{
	T *Reg;
	int Size;
	int Position = 0;

	Register(int size)
	{
		Size = size;
		Reg = new T[Size];
	}
	void operator>>(int val)
	{
		Position = (Position - val) % Size;
		if (Position < 0) { Position = Size - 1; }
	}
	void operator<<(int val)
	{
		Position = (Position + val) % Size;
	}
	T& operator[](int pos)
	{
		return (Reg[(Position + pos) % Size]);
	}
	Register<T>& operator=(T val)
	{
		this->Reg[Position] = val;
	}
};


//### Window ###

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

int ElapsedTime = 0;
int MaxWindowDelta = 0;
int MaxUpdateThreadDelta = 0;
Register<int> WindowDeltaRegister(50);
Register<int> UpdateThreadDeltaRegister(50);

bool RenderEnable = true;
bool RenderEnableConfirm = false;
bool QuickRender = false;

bool Pause = false;


//### Environment ###

Cell *ActiveCell;
Neuron *ActiveNeuron;

int PlayWidth = 4000;//100000;
int PlayHeight = 4000;//100000;

double EnvironmentViewportX = 0;// -PlayWidth / 2;
double EnvironmentViewportY = 0;// -PlayHeight / 2;
double EnvironmentViewportScale = 0.071028412304986563;

double NetworkViewportX = 0;// -PlayWidth / 2;
double NetworkViewportY = 0;// -PlayHeight / 2;
double NetworkViewportScale = 0.9;

int CellHoldNum = 300;//1000;
std::vector<Cell *> CellList;
//std::vector<Cell *> DeadCellList;

int PlantWidthDevisionNum = 80;//PlayWidth / 80;
int PlantHeightDevisionNum = 80;//PlayHeight / 80;
//double **PlantArray = new double*[PlantWidthDevisionNum]; //[PlantHeightDevisionNum];
double **PlantArray;

//### Cell ###

double MinCellSize = 7.0;
double MaxCellSize = 60.0;
double MaxCellSpeed = 3.0;
double MaxInitialCellEnergy = 100;
double MinInitialCellEnergy = 50;
double MaxCellEnergy = 1000;
double MaxCellHealth = 10;// 100;
double MaxCellAge = 1000;
int NetworkWidth = 600;
int NetworkHeight = 300;
double MaxCellViewRange = 1000;
int MutationRate = 20;

//### Functions###

inline int Rand(int min, int max)
{
	//return min + rand() % ((max+1) -min);
	if (min == max) { return min; }
	return min + Random() % ((max+1) -min);
}

inline double DRand(double min, double max)
{
	//return min + ((double)rand() / RAND_MAX) * ((max + 1.0) - min);
	//unsigned int Max: 4294967295;
	//factor of num: 1114129;
	return min + ((double)(Random() % 1114129) / (1114129.0)) * ((max) - min);
}

inline int SRand(int min, int max)
{
	//return min + rand() % ((max+1) -min);
	return Rand(0, max - min) - (max + min) / 2;
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


