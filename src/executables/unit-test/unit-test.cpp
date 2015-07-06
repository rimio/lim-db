#include <stdio.h>

#include "unit-test\bitmap-test.hpp"
#include "unit-test\sector-manager-test.hpp"

int main ()
{
	BitmapTest::check();
	//SectorManagerTest::check();
	return 0;
}