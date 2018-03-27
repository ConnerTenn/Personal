
#include <iostream>
#include "MultiThread_Imp.h"

int main()
{
	
	Thread::Mutex<int> var1;
	
	var1 = 4;
	var1 = var1() + 3;
	
	std::cout << "var1:" << var1() << "\n";
	
	return 0;	
}
