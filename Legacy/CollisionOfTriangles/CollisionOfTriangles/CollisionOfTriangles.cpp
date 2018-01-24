// CollisionOfTriangles.cpp : main project file.

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Vector
{
	double x;
	double y;
	double z;
};

struct Point
{
	double x;
	double y;
	double z;
};

struct Ray
{
	Point P0;
	Point P1;
};

struct Triangle
{
	Point V0;
	Point V1;
	Point V2;
};


// Assume that classes are already given for the objects:
//    Point and Vector with
//        coordinates {float x, y, z;}
//        operators for:
//            == to test  equality
//            != to test  inequality
//            (Vector)0 =  (0,0,0)         (null vector)
//            Point   = Point ± Vector
//            Vector =  Point - Point
//            Vector =  Scalar * Vector    (scalar product)
//            Vector =  Vector * Vector    (cross product)
//    Line and Ray and Segment with defining  points {Point P0, P1;}
//        (a Line is infinite, Rays and  Segments start at P0)
//        (a Ray extends beyond P1, but a  Segment ends at P1)
//    Plane with a point and a normal {Point V0; Vector  n;}
//    Triangle with defining vertices {Point V0, V1, V2;}
//    Polyline and Polygon with n vertices {int n;  Point *V;}
//        (a Polygon has V[n]=V[0])
//===================================================================


#define SMALL_NUM   0.00000001 // anything that avoids division overflow
// dot product (3D) which allows vector operations in arguments
#define dot(u,v)   ((u).x * (v).x + (u).y * (v).y + (u).z * (v).z)

Vector SubPoints(Point P0, Point P1)
{
	return { P0.x - P1.x, P0.y - P1.y, P0.z - P1.z };
}

Vector AddPoints(Point P0, Point P1)
{
	return{ P0.x + P1.x, P0.y + P1.y, P0.z + P1.z };
}

Vector MulPoints(Point P0, Point P1)
{
	return{ P0.x * P1.x, P0.y * P1.y, P0.z * P1.z };
}



// intersect3D_RayTriangle(): find the 3D intersection of a ray with a triangle
//    Input:  a ray R, and a triangle T
//    Output: *I = intersection point (when it exists)
//    Return: -1 = triangle is degenerate (a segment or point)
//             0 =  disjoint (no intersect)
//             1 =  intersect in unique point I1
//             2 =  are in the same plane
int Intersect3D_RayTriangle(Ray R, Triangle T, Point* I)
{
	//Point A = { 1, 0, 0 };
	//T.V0.x -= A.x; T.V0.y -= A.y; T.V0.z -= A.z;
	//T.V1.x -= A.x; T.V1.y -= A.y; T.V1.z -= A.z;
	//T.V1.x -= A.x; T.V1.y -= A.y; T.V1.z -= A.z;

	//R.x -= A.x; R.y -= A.y; R.z -= A.z;



	Vector    u, v, n;              // triangle vectors
	Vector    dir, w0, w;           // ray vectors
	float     r, a, b;              // params to calc ray-plane intersect

									// get triangle edge vectors and plane normal
	//u = T.V1 - T.V0;
	u = SubPoints(T.V1, T.V0);
	//v = T.V2 - T.V0;
	v = SubPoints(T.V2, T.V0);
	//n = u * v;              // cross product
	n = { u.y * v.z - u.z * v.y, u.z * v.x - u.x * v.z, u.x * v.y - u.y * v.x };
	//if (n == (Vector)0)             // triangle is degenerate
	//	return -1;                  // do not deal with this case
	if (n.x == 0 && n.y == 0 && n.z == 0) { return -1; }

	//dir = R.P1 - R.P0;              // ray direction vector
	dir = SubPoints(R.P1, R.P0);
	//w0 = R.P0 - T.V0;
	w0 = SubPoints(R.P0, T.V0);
	a = -dot(n, w0);
	b = dot(n, dir);
	if (fabs(b) < SMALL_NUM)
	{     // ray is  parallel to triangle plane
		if (a == 0)                 // ray lies in triangle plane
			return 2;
		else return 0;              // ray disjoint from plane
	}

	// get intersect point of ray with triangle plane
	r = a / b;
	if (r < 0.0)                    // ray goes away from triangle
		return 0;                   // => no intersect
									// for a segment, also test if (r > 1.0) => no intersect
	if (r > 1.0)
		return 0;

	//*I = R.P0 + r * dir;            // intersect point of ray and plane
	Vector oo = AddPoints(R.P0, { r * dir.x, r * dir.y, r * dir.z });
	*I = { oo.x, oo.y, oo.z };
									// is I inside T?
	float    uu, uv, vv, wu, wv, D;
	uu = dot(u, u);
	uv = dot(u, v);
	vv = dot(v, v);
	//w = *I - T.V0;
	w = SubPoints(*I, T.V0);
	wu = dot(w, u);
	wv = dot(w, v);
	D = uv * uv - uu * vv;

	// get and test parametric coords
	float s, t;
	s = (uv * wv - vv * wu) / D;
	if (s < 0.0 || s > 1.0)         // I is outside T
		return 0;
	t = (uv * wu - uu * wv) / D;
	if (t < 0.0 || (s + t) > 1.0)  // I is outside T
		return 0;

	return 1;                       // I is in T
}




void main()
{
	Point point;// = { NULL, NULL, NULL };
	//cout << "Intersect:" << Intersect3D_RayTriangle({ { 0, 1, 0 }, {0, 0, 0} }, { { 0, -2, 1 },{ -1, -2, -1 },{ 1, -2, -1 } }, &point) << "\n";

	cout << "Intersect:" << Intersect3D_RayTriangle({ { -1, 0, 0 },{ 0, 0, 2 } }, { { -2, -1, 1 },{ 2, -1, 1 },{ 0, 1, 1 } }, &point) << "\n";
	cout << "point: { " << point.x << ", " << point.y << ", " << point.z << " }\n";

	int a;
	cin >> a;
}

