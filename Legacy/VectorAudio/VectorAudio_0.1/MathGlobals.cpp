
#include "Include\MathGlobals.h"


template <class T>
void Point<T>::Translate(T x, T y)
{
	X += x;
	Y += y;
}

template <class T>
int Point<T>::operator[] (int i)
{
	switch (i)
	{
	case 0:
		return X;
	case 1:
		return Y;
	default:
		throw 1;
	}
}



template<typename T> inline T Clamp(T value, T range)
{
	return value > range ? range : (value < -range ? -range : value);
}