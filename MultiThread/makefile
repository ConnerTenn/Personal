
GPP = g++ -std=c++17

Test.obj: main.cpp
	$(GPP) main.cpp -c -o Test.obj

Test: Test.obj
	$(GPP) Test.obj -o test.o

clean:
	rm *.obj *.o -f

FORCE: clean Test
