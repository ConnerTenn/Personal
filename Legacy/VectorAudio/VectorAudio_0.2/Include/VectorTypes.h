
template<typename T> class Vector;
class VectorLine;

#ifndef _VECTOR_TYPES_
#define _VECTOR_TYPES_

#include <iostream>
#include <vector>
#include "MathGlobals.h"

/*class SampleData
{
std::vector<int> Samples;
int StartOffset;
};*/

template<typename T>
inline void AddToSTDVector(std::vector<T> *vector, T element)
{
	vector->push_back(element);
}

template<typename T>
inline void RemoveFromSTDVector(std::vector<T> *vector, T element)
{
	for (int i = 0; i < vector->size(); i++)
	{
		if ((*vector)[i] == element)
		{
			vector->erase(vector->begin() + i); i--;
			//i = ModuleList.size();
			//line removed; reason: will remove all instances of that object in case of duplicates
		}
	}
}


template<typename T>
class Vector
{
public:
	Point<T> Position;
	Point<T> Vector1;
	Point<T> Vector2;

	Vector() {}
	//Vector(const Vector<T> &vector) : Position(vector.Position), Vector1(vector.Vector1), Vector2(vector.Vector2) {}
	template<typename t> Vector(const Vector<t> &vector) : Position(vector.Position), Vector1(vector.Vector1), Vector2(vector.Vector2) {}

	void translate(T x, T y)
	{
		Position.Translate(x, y);
		Vector1.Translate(x, y);
		Vector2.Translate(x, y);
	}
};

//std::vector<double> getCubicRoots(double pa, double pb, double pc, double pd);
bool SingleSolution(Point<double> p1, Point<double> p2, Point<double> p3, Point<double> p4);
inline bool SingleSolution(Vector<double> vector1, Vector<double> vector2);
double GetRoot(double pa, double pb, double pc, double pd, bool &valid);
double GetIntersection(Point<double> p1, Point<double> p2, Point<double> p3, Point<double> p4, double x, bool &valid);
inline double GetIntersection(Vector<double> vector1, Vector<double> vector2, double x, bool &valid);

class VectorLine
{
private:
	std::vector<Vector<int>> VectorLineList;
	//Possible alternative storage?: Point, Vector, Vector, Point, Vector, Vector, Point...

public:
	VectorLine();

	inline bool PassVerticalTest(Vector<int> vector1, Vector<int> vector2);
	bool PassVerticalTest();

	inline void AddVector(Vector<int> vector);
	double Sample(int pos, bool &valid);

};




#endif // !_VECTOR_LINE_
