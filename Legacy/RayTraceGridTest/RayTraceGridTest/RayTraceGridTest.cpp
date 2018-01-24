// RayTraceGridTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
#include <limits> // for infinity
using namespace std;



void raytrace(double x0, double y0, double x1, double y1)
{
	double dx = fabs(x1 - x0);
	double dy = fabs(y1 - y0);

	int x = int(floor(x0));
	int y = int(floor(y0));

	int n = 1;
	int x_inc, y_inc;
	double error;

	if (dx == 0)
	{
		x_inc = 0;
		error = std::numeric_limits<double>::infinity();
	}
	else if (x1 > x0)
	{
		x_inc = 1;
		n += int(floor(x1)) - x;
		error = (floor(x0) + 1 - x0) * dy;
	}
	else
	{
		x_inc = -1;
		n += x - int(floor(x1));
		error = (x0 - floor(x0)) * dy;
	}

	if (dy == 0)
	{
		y_inc = 0;
		error -= std::numeric_limits<double>::infinity();
	}
	else if (y1 > y0)
	{
		y_inc = 1;
		n += int(floor(y1)) - y;
		error -= (floor(y0) + 1 - y0) * dx;
	}
	else
	{
		y_inc = -1;
		n += y - int(floor(y1));
		error -= (y0 - floor(y0)) * dx;
	}

	for (; n > 0; --n)
	{
		//visit(x, y);
		cout << "X:" << x << " Y:" << y << "\n";

		if (error > 0)
		{
			y += y_inc;
			error -= dx;
		}
		else
		{
			x += x_inc;
			error += dy;
		}
	}
}


void main()
{
	raytrace(1.0, 0.5, 1.5, 3.0);

	int a;
	cin >> a;
}



