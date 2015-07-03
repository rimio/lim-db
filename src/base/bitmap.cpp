#include "base\bitmap.hpp"

#include <stdio.h>

Bitmap::Bitmap(INT64 length_of_array) {
	number_of_sectors_ = length_of_array;
	sectors_ = new INT64[length_of_array];
	for (INT32 i = 0; i < length_of_array; ++i)
		sectors_[i] = 0;
};

void Bitmap::set_bit(INT64 index) {
	
	//check if the desired sector is in range
	if (index >= 0 && index < number_of_sectors_ * 64) {
	 
		//locate the bit representing the sector
		INT64 position_ = index / 64;
		INT64 remainder_ = index % 64;
		
		//check if the bit is not already used
		if (!((sectors_[position_] >> (63 - remainder_)) & 1))
			// set the bit to acknowledge that the sector is used
			sectors_[position_] |= (INT64) 1 << (63 - remainder_);
	}

	//TODO signal if the method failed 
};

void Bitmap::clear_bit(INT64 index) {
	//check if the desired sector is in range
	if (index >= 0 && index < number_of_sectors_ * 64) {
		
		//locate the bit representing the sector
		INT64 position_ = index / 64;
		INT64 remainder_ = index % 64;
		
		//check if the bit is used
		if ((sectors_[position_] >> (63 - remainder_) & 1))
			// set the bit to acknowledge that the sector is used
			//sectors_[position_] &= !((INT64)(1 << (63 - remainder_)));
			//error here
			(INT64)sectors_[position_] &= ~(INT64)(1 << (63 - remainder_));
	}

	//TODO signal if the method failed 
};

bool Bitmap::is_bit_set(INT64 index) {
	//check if the desired sector is in range
	if (index >= 0 && index < number_of_sectors_ * 64) {

		//locate the bit representing the sector
		INT64 position_ = index / 64;
		INT64 remainder_ = index % 64;

		return ((sectors_[position_] >> (63 - remainder_)) & 1) ;
	}
	
	//TODO signal if the method failed
};

INT64 Bitmap::bitset_count() {
	INT64 result_ = 0;
	
	//counts the number of sectors used by iterating through each bit
	for (INT64 i = 0; i < number_of_sectors_; ++i) {
		for (INT64 j = 0; j < 64; ++j) {
			result_ += ((sectors_[i] >> j) & 1);
		}
	}

	for (INT64 i = 0; i < 10; i++) printf("%lld \n", sectors_[i]);

	return result_;
}

