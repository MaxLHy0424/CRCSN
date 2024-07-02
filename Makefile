pathMsys2 = C:\Software\MSYS2
compiler = g++.exe
argv = -fexec-charset=GBK -std=gnu++23 -Wall -Wextra -static -Ofast -Os -flto -o
branch = dev
main:
	$(pathMsys2)\mingw64\bin\$(compiler) main.cpp $(argv) .\bin\$(branch)_msvcrt64.exe
	$(pathMsys2)\ucrt64\bin\$(compiler) main.cpp $(argv) .\bin\$(branch)_ucrt64.exe