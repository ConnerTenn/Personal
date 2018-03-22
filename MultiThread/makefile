
MultiThread.obj: MultiThread.h MultiThread.cpp
	g++ MultiThread.cpp -c -o MultiThread.obj

Test: main.cpp MultiThread.obj
	g++ main.cpp MultiThread.obj -o test.o

clean:
	rm *.obj *.o

FORCE: clean Test
