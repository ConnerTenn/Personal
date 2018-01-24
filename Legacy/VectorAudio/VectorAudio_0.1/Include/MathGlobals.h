
template<typename T> struct Point;

#ifndef _MATH_GLOBALS_
#define _MATH_GLOBALS_

#define PI (3.14159265358979323)
#define TAU (PI*2.0)

//change to templates
struct Int2
{
	int Value[2];

	int operator[](int i) { return Value[i]; }
	int X() { return Value[0]; }
	int Y() { return Value[1]; }
	int *Xp() { return &Value[0]; }
	int *Yp() { return &Value[1]; }
};

template<typename T>
struct Point
{
	T X;
	T Y;

	Point() : X(0), Y(0) {}
	Point(T x, T y) : X(x), Y(y) {}
	//Point(const Point<T> &point) : X(point.X), Y(point.Y) {}
	template<typename t> Point(const Point<t> &point) : X((T)point.X), Y((T)point.Y) {}

	void Translate(T x, T y);

	int operator[] (int i);
};

template<typename T> inline T Clamp(T value, T range);

#endif // !_MATH_GLOBALS_
