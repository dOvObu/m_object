#include "mobj.h"
#include <iostream>
#include <vector>







int main ()
{
	Mobj o3;
	o3.readFromFile ("test.jo");
	std::cout << o3 << '\n';
}
