#include <cstdio>

#include "unit-test\bitmap-test.hpp"

void BitmapTest::check() {
	Bitmap t1 = Bitmap(10);
	Bitmap t2 = Bitmap(20);
	Bitmap t3 = Bitmap(100);
	Bitmap t4 = Bitmap(1000);

	printf("t1 initially: %d \n", t1.bitset_count());
	
	printf("bit shouldn't be set: %d \n", t1.is_bit_set(10));
	
	t1.set_bit(10);
	//t1.set_bit(100);
	//t1.set_bit(500);
	//t1.set_bit(1);
	//t1.set_bit(2);

	printf("t1 after 5 inserations: %d \n", t1.bitset_count());

	printf("bit should be set: %d \n", t1.is_bit_set(10));

	t1.clear_bit(10);

	printf("bit shouldn't be set: %d \n", t1.is_bit_set(10));

	t1.clear_bit(2);

	printf("t1 after two deletes: %d \n", t1.bitset_count());
	

};


