#include "mobj.h"
#include <iostream>

int main ()
{
	Mobj o1 = "Hello, ";
	Mobj o2 = 42;
	Mobj o3 = 3.141f;
	std::cout << o << ' ' << o2 << ' ' << o3 << ' ';
	o3 = " mobj!";
	std::cout << o3 << '\n';
}
