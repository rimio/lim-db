#include <cassert>
#include <cstdio>

#include "unit-test\bitmap-test.hpp"

void BitmapTest::check() {
	Bitmap t1 = Bitmap(640);
	Bitmap t2 = Bitmap(20);
	Bitmap t3 = Bitmap(100);
	Bitmap t4 = Bitmap(1000);
	
	bool result = t1.set_bit(100);

	assert(result);

	result = t1.set_bit(10);
	assert(result);

	//error if i try to use an already used bit
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

	//bit should be set: 
	result = t1.is_bit_set(10);
	assert(result);
	//erase used bit
	result = t1.clear_bit(10);
	assert(result);
	//erase unused bit
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

	//when bit is out of range
	result = t1.is_bit_set(5000);
	assert(!result);
	
	//ocuppy first 500 places 
	for (int i = 0; i < 500; i++)
		t1.set_bit(i);
	
	//assign another 140
	int x = t1.give_free_bit(499);
	for (int i = 1; i < 139; i++) {
		x = t1.give_free_bit(x);
	}

	//it should be full now
	assert(t1.bitset_count() == 640);
};