#include <cassert>
#include <cstdio>

#include "unit-test\bitmap-test.hpp"

void BitmapTest::check() {
	Bitmap t1 = Bitmap(640, false);
	Bitmap t2 = Bitmap(20, true);
	Bitmap t3 = Bitmap(100, true);
	Bitmap t4 = Bitmap(1000,false);
	
	bool result = t1.set_bit(100);

	assert(result);

	result = t1.set_bit(10);
	assert(result);

	//Error if i try to use an already used bit
	result = t1.set_bit(10);
	assert(!result);

	result = t1.set_bit(520);
	assert(result);
	result = t1.set_bit(1);
	assert(result);
	result = t1.set_bit(100000);
	assert(!result);


	if (t1.bitset_count() == 4)
		result = true;
	else
		result = false;
	assert(result);

	//Bit should be set: 
	result = t1.is_bit_set(10);
	assert(result);
	//Erase used bit
	result = t1.clear_bit(10);
	assert(result);
	//Erase unused bit
	result = t1.clear_bit(7);
	assert(!result);

	result = t1.is_bit_set(10);
	assert(!result);

	result = t1.clear_bit(0);
	assert(!result);

	if (t1.bitset_count() == 3)
		result = true;
	else
		result = false;
	assert(result);

	//When bit is out of range
	result = t1.is_bit_set(5000);
	assert(!result);
	
	//Ocuppy first 500 places 
	for (int i = 0; i < 500; i++) t1.set_bit(i);
	
	//Assign another 140
	int x = t1.give_free_bit(499);
	for (int i = 1; i < 139; i++) {
		x = t1.give_free_bit(x);
		
	}

	//it should be full now
	assert(t1.bitset_count() == 640);

	result = t2.is_bit_set(12);
	assert(result);
};