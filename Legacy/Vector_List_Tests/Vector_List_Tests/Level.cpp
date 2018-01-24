

#include "stdafx.h"
#include<vector>
#include"Level.h"
#include"Object.h"

using namespace std;

int Level::Run()
{
	Object Object1;
	ObjectList.push_back(Object1);

	Object Object2;
	ObjectList.push_back(Object2);

	Object Object3;
	ObjectList.push_back(Object3);

	return ObjectList.size();
}