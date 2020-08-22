cls
DEL /F/Q/S build > NUL
mkdir build
cd build
cmake -G "MinGW Makefiles" ..
make
cd ..
PAUSE