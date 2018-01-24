// CollisionsOfTriangles2.cpp : main project file.

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <time.h>
#include <Windows.h>
#include <bitset>
#include <chrono>

using namespace std;

struct Plane
{
	Plane(double a, double b, double c, double d) : A(a), B(b), C(c), D(d) {}
	Plane() {}

	double A;
	double B;
	double C;
	double D;
};

struct Vector
{
	Vector(double x, double y, double z) : X(x), Y(y), Z(z) {}
	Vector() {}

	double X;
	double Y;
	double Z;


	static Vector Cross(Vector Vector1, Vector Vector2)
	{
		return
		{
			Vector1.Y * Vector2.Z - Vector1.Z * Vector2.Y,
			Vector1.Z * Vector2.X - Vector1.X * Vector2.Z,
			Vector1.X * Vector2.Y - Vector1.Y * Vector2.X
		};
	}
	static double Dot(Vector Vector1, Vector Vector2)
	{
		return
		{
			Vector1.X * Vector2.X + Vector1.Y * Vector2.Y + Vector1.Z * Vector2.Z
		};
	}
	static Vector Invert(Vector Vector1)
	{
		return
		{
			-Vector1.X,
			-Vector1.Y,
			-Vector1.Z
		};
	}

	Vector operator+(Vector Other)
	{
		return{ X + Other.X, Y + Other.Y, Z + Other.Z };
	}
	Vector operator-(Vector Other)
	{
		return{ X - Other.X, Y - Other.Y, Z - Other.Z };
	}
};

struct Triangle
{
	Triangle(Vector point1, Vector point2, Vector point3) : Point1(point1), Point2(point2), Point3(point3) {}
	Triangle() {}

	Vector Point1;
	Vector Point2;
	Vector Point3;
};

struct Line
{
	Line(double a, double b, double c) : A(a), B(b), C(c) {}
	Line() {}

	double A;
	double B;
	double C;
};

struct Segment
{
	Segment(Vector point1, Vector point2) : Point1(point1), Point2(point2) {}
	Segment() {}

	Vector Point1;
	Vector Point2;
};

Plane PlaneFromTriangle(Triangle _Triangle)
{
	Plane Plane1;
	Vector Vector1;
	Vector Vector2;
	Vector Normal;

	//Step 1
	Vector1 = _Triangle.Point3 - _Triangle.Point1;
	Vector2 = _Triangle.Point2 - _Triangle.Point1;

	//Step 2
	Normal = Vector::Cross(Vector1, Vector2);

	//Step 3
	Plane1 = 
	{ 
		Normal.X, 
		Normal.Y, 
		Normal.Z, 
		Normal.X * _Triangle.Point1.X + Normal.Y * _Triangle.Point1.Y + Normal.Z * _Triangle.Point1.Z
	};
	
	return Plane1;
}

Line LineFromPlanes(Plane Plane1, Plane Plane2)
{
	return
	{
		Plane2.C * Plane1.A - Plane1.C * Plane2.A,
		Plane2.C * Plane1.B - Plane1.C * Plane2.B,
		Plane1.C * Plane2.D - Plane2.C * Plane1.D
	};
}

bool IntersectRayTriangle(Segment Segment1, Triangle Triangle1)
{
	Vector    u, v, n;              // triangle vectors
	Vector    dir, w0, w;           // ray vectors
	float     r, a, b;              // params to calc ray-plane intersect

									// get triangle edge vectors and plane normal
	//u = T.V1 - T.V0;
	u = Triangle1.Point2 - Triangle1.Point1;
	//v = T.V2 - T.V0;
	v = Triangle1.Point3 - Triangle1.Point1;
	//n = u * v;              // cross product
	//n = { u.Y * v.Z - u.Z * v.Y, u.Z * v.X - u.X * v.Z, u.X * v.Y - u.Y * v.X };
	n = Vector::Cross(u, v);
	//if (n == (Vector)0)             // triangle is degenerate
	//	return -1;                  // do not deal with this case
	if (n.X == 0 && n.Y == 0 && n.Z == 0) { return false; }

	//dir = R.P1 - R.P0;              // ray direction vector
	dir = Segment1.Point2 - Segment1.Point1;
	//w0 = R.P0 - T.V0;
	w0 = Segment1.Point1 - Triangle1.Point1;
	a = -Vector::Dot(n, w0);
	b = Vector::Dot(n, dir);
	if (fabs(b) < 0.00000001)
	{     // ray is  parallel to triangle plane
		if (a == 0)                 // ray lies in triangle plane
			return false;
		else return false;              // ray disjoint from plane
	}

	// get intersect point of ray with triangle plane
	r = a / b;
	if (r < 0.0)                    // ray goes away from triangle
		return false;                   // => no intersect
									// for a segment, also test if (r > 1.0) => no intersect
	if (r > 1.0)
		return false;

	//*I = R.P0 + r * dir;            // intersect point of ray and plane
	//Vector oo = AddPoints(R.P0, { r * dir.x, r * dir.y, r * dir.z });
	Vector Point = Segment1.Point1 + Vector({ r * dir.X, r * dir.Y, r * dir.Z });
	//*I = { oo.x, oo.y, oo.z };
	// is I inside T?
	float    uu, uv, vv, wu, wv, D;
	uu = Vector::Dot(u, u);
	uv = Vector::Dot(u, v);
	vv = Vector::Dot(v, v);
	//w = *I - T.V0;
	//w = SubPoints(*I, T.V0);
	w = Point - Triangle1.Point1;
	wu = Vector::Dot(w, u);
	wv = Vector::Dot(w, v);
	D = uv * uv - uu * vv;

	// get and test parametric coords
	float s, t;
	s = (uv * wv - vv * wu) / D;
	if (s < 0.0 || s > 1.0)         // I is outside T
		return false;
	t = (uv * wu - uu * wv) / D;
	if (t < 0.0 || (s + t) > 1.0)  // I is outside T
		return false;

	return true;                       // I is in T
}

#define dot(a,b) (a.X * b.X + a.Y * b.Y + a.Z + b.Z)

bool IntersectRayTriangleOPT(Segment Segment1, Triangle Triangle1)
{
	Vector    u, v, n;              // triangle vectors
	Vector    dir, w0, w;           // ray vectors
	float     r, a, b;              // params to calc ray-plane intersect

									// get triangle edge vectors and plane normal
	//u = T.V1 - T.V0;
	u = { Triangle1.Point2.X - Triangle1.Point1.X, Triangle1.Point2.Y - Triangle1.Point1.Y, Triangle1.Point2.Z - Triangle1.Point1.Z };
	//v = T.V2 - T.V0;
	v = { Triangle1.Point3.X - Triangle1.Point1.X, Triangle1.Point3.Y - Triangle1.Point1.Y, Triangle1.Point3.Z - Triangle1.Point1.Z };
	//n = u * v;              // cross product
	n = { u.Y * v.Z - u.Z * v.Y, u.Z * v.X - u.X * v.Z, u.X * v.Y - u.Y * v.X };
	//n = Vector::Cross(u, v);
	//if (n == (Vector)0)             // triangle is degenerate
	//	return -1;                  // do not deal with this case
	if (n.X == 0 && n.Y == 0 && n.Z == 0) { return false; }

	//dir = R.P1 - R.P0;              // ray direction vector
	//dir = Segment1.Point2 - Segment1.Point1;
	dir = { Segment1.Point2.X - Segment1.Point1.X, Segment1.Point2.Y - Segment1.Point1.Y, Segment1.Point2.Z - Segment1.Point1.Z };
	//w0 = R.P0 - T.V0;
	//w0 = Segment1.Point1 - Triangle1.Point1;
	w0 = { Segment1.Point1.X - Triangle1.Point1.X, Segment1.Point1.Y - Triangle1.Point1.Y, Segment1.Point1.Z - Triangle1.Point1.Z };
	a = -dot(n, w0);
	b = dot(n, dir);
	if (fabs(b) < 0.00000001)
	{     // ray is  parallel to triangle plane
		if (a == 0)                 // ray lies in triangle plane
			return false;
		else return false;              // ray disjoint from plane
	}

	// get intersect point of ray with triangle plane
	r = a / b;
	if (r < 0.0)                    // ray goes away from triangle
		return false;                   // => no intersect
										// for a segment, also test if (r > 1.0) => no intersect
	if (r > 1.0)
		return false;

	//*I = R.P0 + r * dir;            // intersect point of ray and plane
	//Vector oo = AddPoints(R.P0, { r * dir.x, r * dir.y, r * dir.z });
	Vector Point = { Segment1.Point1.X + Vector({ r * dir.X, r * dir.Y, r * dir.Z }).X, Segment1.Point1.Y + Vector({ r * dir.X, r * dir.Y, r * dir.Z }).Y, Segment1.Point1.Z + Vector({ r * dir.X, r * dir.Y, r * dir.Z }).Z };
	//Vector Point = Segment1.Point1 + Vector({ r * dir.X, r * dir.Y, r * dir.Z });
	//*I = { oo.x, oo.y, oo.z };
	// is I inside T?
	float    uu, uv, vv, wu, wv, D;
	uu = dot(u, u);
	uv = dot(u, v);
	vv = dot(v, v);
	//w = *I - T.V0;
	//w = SubPoints(*I, T.V0);
	w= { Point.X - Triangle1.Point1.X, Point.Y - Triangle1.Point1.Y, Point.Z - Triangle1.Point1.Z };
	wu = dot(w, u);
	wv = dot(w, v);
	D = uv * uv - uu * vv;

	// get and test parametric coords
	float s, t;
	s = (uv * wv - vv * wu) / D;
	if (s < 0.0 || s > 1.0)         // I is outside T
		return false;
	t = (uv * wu - uu * wv) / D;
	if (t < 0.0 || (s + t) > 1.0)  // I is outside T
		return false;

	return true;                       // I is in T
}






void main()
{
	auto start = chrono::high_resolution_clock::now();

	Triangle Triangle1({ 1, 2, 3 }, { 4, 6, 9 }, { 12, 11, 9 });
	Triangle Triangle2({ 2, 3, 5 }, { 5, 7, 11 }, { 6, 7, 2 });
	//Triangle Triangle1({ -1, 0, 0 }, { 1, 0, 0 }, { 0, 0, 2 });
	//Triangle Triangle2({ -2, -1, 1 }, { 2, -1, 1 }, { 0, 1, 1 });


	if (
		IntersectRayTriangle({ Triangle1.Point1, Triangle1.Point2 }, Triangle2) ||
		IntersectRayTriangle({ Triangle1.Point2, Triangle1.Point3 }, Triangle2) ||
		IntersectRayTriangle({ Triangle1.Point1, Triangle1.Point3 }, Triangle2) ||

		IntersectRayTriangle({ Triangle2.Point1, Triangle2.Point2 }, Triangle1) ||
		IntersectRayTriangle({ Triangle2.Point2, Triangle2.Point3 }, Triangle1) ||
		IntersectRayTriangle({ Triangle2.Point1, Triangle2.Point3 }, Triangle1)
		)
	{
		cout << "TRUE!\n";
	}
	else
	{
		cout << "FALSE!\n";
	}

	//Plane Plane1 = PlaneFromTriangle(Triangle1);
	//Plane Plane2 = PlaneFromTriangle(Triangle2);
	//Line LinePlaneIntersect = LineFromPlanes(Plane1, Plane2);
	//cout << "\n" << Plane1.A << " * X + " << Plane1.B << " * Y + " << Plane1.C << " * Z = " << Plane1.D << "\n";

	auto elapsed = chrono::high_resolution_clock::now() - start;
	long long microseconds = chrono::duration_cast<chrono::microseconds>(elapsed).count();
	cout << "Time: " << microseconds / 1000.0 << "ms\n";

	cout << "\n";
	
	int a;
	cin >> a;
}

