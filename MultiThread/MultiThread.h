
#include <thread>
#include <mutex>

namespace Thread
{
	template <class T>
	class Mutex
	{
	private:
		T Data;
		std::mutex Mtx;
	
	public:
		Mutex();
		Mutex(T data);
		
		operator=(Mutex other);
		operator=(T other);
		
		
	};
}