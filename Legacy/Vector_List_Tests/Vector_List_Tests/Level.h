

#ifndef _LEVEL_H_
#define _LEVEL_H_

#include<vector>
#include"Object.h"

using namespace std;

class Level
{
public:

	int Run();

	vector<Object> ObjectList;
};
#endif