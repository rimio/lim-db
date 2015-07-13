#include <cassert>
#include <cstdio>

#include "unit-test\sector-manager-test.hpp"

void SectorManagerTest::check() {
	SectorManager s1 = SectorManager();

	ErrorCode a[20];
	SectorID * b[20];
	//10 is the predefinied NUMBER_OF_SECTORS
	for (int i = 1; i <= 10; ++i)
		a[i] = s1.AllocateSector(b[i]);
	
	//Allocate more than available space
	a[11] = s1.AllocateSector(b[11]);
	bool result;
	/*if (z == -1)
		result = true;
	else
		result = false;
	assert(result);
	*/
	//Free a space
	result = s1.DeallocateSector(3);
	assert(result);

	//Free it again
	result = s1.DeallocateSector(3);
	assert(!result);

	//Free an unexistent space
	result = s1.DeallocateSector(20);
	assert(!result);

	//Only space free -> 3, allocate it
	a[12] = s1.AllocateSector(b[12]);
	if (*b[12] == 3)
		result = true;
	else
		result = false;
	assert(result);

}