
#include <iostream>
#include "MultiThread_Imp.h"

int main()
{
	
	Thread::Mutex<int> var1;
	
	var1 = 4;
	
	std::cout << "var1:" << var1.get() << "\n";
	
	return 0;	
}
