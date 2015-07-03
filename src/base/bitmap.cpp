#include "base\bitmap.hpp"

#include <stdio.h>

#define BITMAP_UNIT_SIZE 64

Bitmap::Bitmap(int bits_number) {
	bits_number_ = bits_number;
	bits_array_size_ = (bits_number_ - 1) / BITMAP_UNIT_SIZE + 1;
	bit_array_ = new UINT64[bits_number_];
	for (int i = 0; i < bits_number_; ++i)
		bit_array_[i] = 0;
};

bool Bitmap::set_bit(int index) {
	
	//check if the desired bit is in range
	if (index >= 0 && index < bits_number_ ) {
	 
		//locate the bit representing the sector
		int position_ = index / BITMAP_UNIT_SIZE;
		int remainder_ = index % BITMAP_UNIT_SIZE;
		
		//check if the bit is not already used
		if (!is_bit_set(index)) {
			// set the bit to acknowledge that the bit is used
			bit_array_[position_] |= 1ULL << remainder_;
			return true;
		}
		else
			return false;
	}
	else
		return false;
};

bool Bitmap::clear_bit(int index) {
	//check if the desired bit is in range
	if (index >= 0 && index < bits_number_) {

		//locate the bit 
		int position_ = index / BITMAP_UNIT_SIZE;
		int remainder_ = index % BITMAP_UNIT_SIZE;

		//check if the bit is used
		if (is_bit_set(index)) {
			// set the bit as being unused
			bit_array_[position_] &= ~(1ULL << remainder_);
			return true;
		}
		else
			return false;
	}
	else
		return false;
};

bool Bitmap::is_bit_set(int index) {
	//check if the desired bit is in range
	if (index >= 0 && index < bits_number_) {

		//locate the bit 
		int position_ = index / BITMAP_UNIT_SIZE;
		int remainder_ = index % BITMAP_UNIT_SIZE;

		return ((bit_array_[position_] >> remainder_) & 1);
	}
};

int Bitmap::bitset_count() {
	int result = 0;
	
	//counts the number of bits used by iterating through the array
	for (int i = 0; i < bits_number_; ++i) {
		for (int j = 0; j < BITMAP_UNIT_SIZE; ++j) {
			result += ((bit_array_[i] >> j) & 1);
		}
	}

	return result;
}

