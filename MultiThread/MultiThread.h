
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
		Mutex(T &data);
		Mutex(T data);
		
		/*void operator=(Mutex &other);*/
		void operator=(T &other);
		void operator=(T other);
		
		T &get();
		
	};
}

