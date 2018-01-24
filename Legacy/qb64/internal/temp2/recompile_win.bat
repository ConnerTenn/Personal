@echo off
cd %0\..\
echo Recompiling...
cd ../c
c_compiler\bin\g++ -s -Wfatal-errors -w -Wall qbx2.cpp  libqb\os\win\libqb_0_980_000000.o -lws2_32 -lwinspool parts\core\os\win\src.a -lopengl32 -lglu32 -lwinmm -lgdi32 -mwindows -static-libgcc -static-libstdc++ -D FREEGLUT_STATIC -lksguid -lole32 -lwinmm -ldxguid -o "..\..\Soon_Gravity.exe"
pause
