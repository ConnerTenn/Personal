
#include "Include\VectorTypes.h"

/*std::vector<double> getCubicRoots(double pa, double pb, double pc, double pd)
{
	std::vector<double> out;

	double d = (-pa + 3.0 * pb - 3.0 * pc + pd);
	double a = (3.0 * pa - 6.0 * pb + 3.0 * pc) / d;
	double b = (-3.0 * pa + 3.0 * pb) / d;
	double c = pa / d;

	double p = (3.0 * b - a * a) / 3.0;
	double p3 = p / 3.0;
	double q = (2.0*a*a*a - 9.0*a*b + 27.0*c) / 27.0;
	double q2 = q / 2.0;
	double discriminant = q2*q2 + p3*p3*p3;

	double u1, v1, root1, root2, root3;

	//three real roots
	if (discriminant < 0.0)
	{
		double mp3 = -p / 3.0;
		double mp33 = mp3*mp3*mp3;
		double r = sqrt(mp33);
		double t = -q / (2.0*r);
		double cosphi = t < -1.0 ? -1 : (t > 1.0 ? 1 : t);
		double phi = acos(cosphi);
		double crct = cbrt(r);
		double t1 = 2.0 * crct;
		root1 = t1 * cos(phi / 3.0) - a / 3.0;
		root2 = t1 * cos((phi + 2.0 * PI) / 3.0) - a / 3.0;
		root3 = t1 * cos((phi + 4.0 * PI) / 3.0) - a / 3.0;
		if (0.0 <= root1 && root1 <= 1.0) { out.push_back(root1); }
		if (0.0 <= root2 && root2 <= 1.0) { out.push_back(root2); }
		if (0.0 <= root3 && root3 <= 1.0) { out.push_back(root3); }
		return out;
	}
	//three real roots, two of them are the same
	else if (discriminant == 0.0)
	{
		u1 = q2 < 0.0 ? cbrt(-q2) : -cbrt(q2);
		root1 = 2.0 * u1 - a / 3.0;
		root2 = -u1 - a / 3.0;
		if (0.0 <= root1 && root1 <= 1.0) { out.push_back(root1); }
		if (0.0 <= root2 && root2 <= 1.0) { out.push_back(root2); }
		return out;
	}

	//one real root
	double sd = sqrt(discriminant);
	u1 = cbrt(sd - q2);
	v1 = cbrt(sd + q2);
	root1 = u1 - v1 - a / 3.0;
	if (0.0 <= root1 && root1 <= 1.0) { out.push_back(root1); }
	return out;
}*/

bool SingleSolution(Point<double> p1, Point<double> p2, Point<double> p3, Point<double> p4)
{
	double v1 = 3.0 * (p2.X - p1.X);
	double v2 = 3.0 * (p3.X - p2.X);
	double v3 = 3.0 * (p4.X - p3.X);

	//(v1-2.0*v2+v3)*x*x + 2.0*(v2-v1)*x+v1
	//(-b+-sqrt(b^2-4*a*c))/(2*a)
	double root = (2.0*(v2 - v1))*(2.0*(v2 - v1)) - 4.0*(v1 - 2.0*v2 + v3)*v1;//calculate roots of derivitive
	if (root <= 0)
	{
		return true;//no roots or only 1 root means that there is only 1 vertical solution
	}
	else
	{
		return false;//multiple roots: multiple vertical solutions
	}
}

bool SingleSolution(Vector<double> vector1, Vector<double> vector2)
{
	return SingleSolution(vector1.Position, vector1.Vector2, vector2.Vector1, vector2.Position);
}

double GetRoot(double pa, double pb, double pc, double pd, bool &valid)
{
	double root;
	valid = false;

	double d = (-pa + 3.0 * pb - 3.0 * pc + pd);
	double a = (3.0 * pa - 6.0 * pb + 3.0 * pc) / d;
	double b = (-3.0 * pa + 3.0 * pb) / d;
	double c = pa / d;

	double p = (3.0 * b - a * a) / 3.0;
	double p3 = p / 3.0;
	double q = (2.0*a*a*a - 9.0*a*b + 27.0*c) / 27.0;
	double q2 = q / 2.0;
	double discriminant = q2*q2 + p3*p3*p3;

	double u1, v1, root1, root2, root3;

	//three real roots
	if (discriminant < 0.0)
	{
		double mp3 = -p / 3.0;
		double mp33 = mp3*mp3*mp3;
		double r = sqrt(mp33);
		double t = -q / (2.0*r);
		//double cosphi = t < -1.0 ? -1 : (t > 1.0 ? 1 : t);
		//double phi = acos(cosphi);
		double phi = acos((t < -1.0 ? -1 : (t > 1.0 ? 1 : t)));
		//double crct = cbrt(r);
		//double t1 = 2.0 * crct;
		double t1 = 2.0 * cbrt(r);
		root1 = t1 * cos(phi / 3.0) - a / 3.0;
		root2 = t1 * cos((phi + 2.0 * PI) / 3.0) - a / 3.0;
		root3 = t1 * cos((phi + 4.0 * PI) / 3.0) - a / 3.0;
		if (0.0 <= root1 && root1 <= 1.0) { root = root1; valid = true; }
		if (0.0 <= root2 && root2 <= 1.0) { root = root2; if (valid) { valid = false; } else { valid = true; } } //opertaions with valid to ensure valid only if 1 root within range
		if (0.0 <= root3 && root3 <= 1.0) { root = root3; if (valid) { valid = false; } else { valid = true; } } //opertaions with valid to ensure valid only if 1 root within range
		return root;
	}
	//three real roots, two of them are the same
	else if (discriminant == 0.0)
	{
		u1 = q2 < 0.0 ? cbrt(-q2) : -cbrt(q2);
		root1 = 2.0 * u1 - a / 3.0;
		root2 = -u1 - a / 3.0;
		if (0.0 <= root1 && root1 <= 1.0) { root = root1; valid = true; }
		if (0.0 <= root2 && root2 <= 1.0) { root = root2; if (valid) { valid = false; } else { valid = true; } } //opertaions with valid to ensure valid only if 1 root within range
		return root;
	}

	//one real root
	double sd = sqrt(discriminant);
	u1 = cbrt(sd - q2);
	v1 = cbrt(sd + q2);
	root1 = u1 - v1 - a / 3.0;
	if (0.0 <= root1 && root1 <= 1.0) { root = root1; valid = true; }
	return root;
}

double GetIntersection(Point<double> p1, Point<double> p2, Point<double> p3, Point<double> p4, double x, bool &valid)
{
	//initial Transforms
	p1.X = p1.X - x;
	p2.X = p2.X - x;
	p3.X = p3.X - x;
	p4.X = p4.X - x;
	
	//Point<double> p1r(p1.Y, -p1.X);
	//Point<double> p2r(p2.Y, -p2.X);
	//Point<double> p3r(p3.Y, -p3.X);
	//Point<double> p4r(p4.Y, -p4.X);

	//double root = GetRoot(p1r.Y, p2r.Y, p3r.Y, p4r.Y, valid);
	double root = GetRoot(-p1.X, -p2.X, -p3.X, -p4.X, valid);


	return (1.0 - root) * (1.0 - root) * (1.0 - root) * p1.Y + 3.0 * (1.0 - root) * (1.0 - root) * root * p2.Y + 3.0 * (1.0 - root) * root * root * p3.Y + root * root * root * p4.Y;
}

double GetIntersection(Vector<double> vector1, Vector<double> vector2, double x, bool &valid)
{
	return GetIntersection(vector1.Position, vector1.Vector2, vector2.Vector1, vector2.Position, x, valid);
}





VectorLine::VectorLine()
{

}

inline bool VectorLine::PassVerticalTest(Vector<int> vector1, Vector<int> vector2)
{
	return SingleSolution(vector1, vector2);
}

bool VectorLine::PassVerticalTest()
{
	for (int i = 0; i < VectorLineList.size() - 1; i++)
	{
		if (!PassVerticalTest(VectorLineList[i], VectorLineList[i + 1]))//check that each line passes the test.
		{
			return false;
		}
		else if (VectorLineList[i].Position.X < VectorLineList[i + 1].Position.X)//check that there is no "back tracking"
		{
			return false;
		}
	}
	return true;
}

inline void VectorLine::AddVector(Vector<int> vector)
{
	VectorLineList.push_back(vector);
}

double VectorLine::Sample(int pos, bool &valid)
{
	valid = false;
	for (int i = 0; i < VectorLineList.size()-1; i++)
	{
		//find correct segment to sample
		if (pos > VectorLineList[i].Position.X && pos < VectorLineList[i + 1].Position.X)
		{
			return GetIntersection(VectorLineList[i], VectorLineList[i + 1], pos, valid);
		}
	}
	return 0;
}