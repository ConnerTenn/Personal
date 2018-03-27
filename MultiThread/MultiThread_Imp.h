
#include "MultiThread.h"


template <class T>
Thread::Mutex<T>::Mutex()
{
	
}

template <class T>
Thread::Mutex<T>::Mutex(T &data)
{
	&Data = &data;
}

template <class T>
Thread::Mutex<T>::Mutex(T data)
{
	Data = data;
}

/*template <class T>
void Thread::Mutex<T>::operator=(Mutex &other)
{
	&Data = &other.Data;
	Mtx = other.Mtx;
}*/

template <class T>
void Thread::Mutex<T>::operator=(T &other)
{
	&Data = &other;
}

template <class T>
void Thread::Mutex<T>::operator=(T other)
{
	Data = other;
}

template <class T>
T &Thread::Mutex<T>::get()
{
	return Data;
}
