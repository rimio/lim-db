#include <cassert>
#include <cstdio>

#include "unit-test\sector-manager-test.hpp"

void SectorManagerTest::check() {
	SectorManager s1 = SectorManager(10);

	int a[20];
	//10 is the predefinied NUMBER_OF_SECTORS
	for (int i = 1; i <= 10; ++i)
		a[i] = s1.allocate_sector();
	
	//Allocate more than available space
	int z = s1.allocate_sector();
	bool result;
	if (z == -1)
		result = true;
	else
		result = false;
	assert(result);

	//Free a space
	result = s1.deallocate_sector(3);
	assert(result);

	//Free it again
	result = s1.deallocate_sector(3);
	assert(!result);

	//Free an unexistent space
	result = s1.deallocate_sector(20);
	assert(!result);

	//Only space free -> 3, allocate it
	z = s1.allocate_sector();
	if (z == 3)
		result = true;
	else
		result = false;
	assert(result);

}