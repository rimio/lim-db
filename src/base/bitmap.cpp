#include "base\bitmap.hpp"

#include <stdio.h>

#define BITMAP_UNIT_SIZE 64

Bitmap::Bitmap(UINT64 length_of_array) {
	bits_number_ = (length_of_array - 1) / BITMAP_UNIT_SIZE + 1;
	bit_array_ = new UINT64[bits_number_];
	for (INT32 i = 0; i < bits_number_; ++i)
		bit_array_[i] = 0;
};

bool Bitmap::set_bit(UINT64 index) {
	
	//check if the desired sector is in range
	if (index >= 0 && index < bits_number_ * BITMAP_UNIT_SIZE) {
	 
		//locate the bit representing the sector
		UINT64 position_ = index / BITMAP_UNIT_SIZE;
		UINT64 remainder_ = index % BITMAP_UNIT_SIZE;
		
		//check if the bit is not already used
		if (!is_bit_set(index)) {
			// set the bit to acknowledge that the sector is used
			bit_array_[position_] |= ((UINT64)1LL << (BITMAP_UNIT_SIZE - 1 - remainder_));
			return true;
		}
		else
			return false;
	}
};

bool Bitmap::clear_bit(UINT64 index) {
	//check if the desired sector is in range
	if (index >= 0 && index < bits_number_ * BITMAP_UNIT_SIZE) {

		//locate the bit representing the sector
		UINT64 position_ = index / BITMAP_UNIT_SIZE;
		UINT64 remainder_ = index % BITMAP_UNIT_SIZE;

		//check if the bit is used
		if (is_bit_set(index)) {
			// set the bit to acknowledge that the sector is used
			//sectors_[position_] &= !((INT64)(1 << (63 - remainder_)));

			bit_array_[position_] &= (UINT64)~(1LL << (BITMAP_UNIT_SIZE - 1 - remainder_));
			return true;
		}
		else
			return false;
	}
};

bool Bitmap::is_bit_set(UINT64 index) {
	//check if the desired sector is in range
	if (index >= 0 && index < bits_number_ * BITMAP_UNIT_SIZE) {

		//locate the bit representing the sector
		UINT64 position_ = index / BITMAP_UNIT_SIZE;
		UINT64 remainder_ = index % BITMAP_UNIT_SIZE;

		return ((bit_array_[position_] >> (BITMAP_UNIT_SIZE - 1 - remainder_)) & 1);
	}
};

UINT64 Bitmap::bitset_count() {
	UINT64 result_ = 0;
	
	//counts the number of sectors used by iterating through each bit
	for (INT64 i = 0; i < bits_number_; ++i) {
		for (INT64 j = 0; j < BITMAP_UNIT_SIZE; ++j) {
			result_ += ((bit_array_[i] >> j) & 1);
		}
	}

	//for (INT64 i = 0; i < 10; i++) printf("%lld \n", bit_array_[i]);

	return result_;
}

