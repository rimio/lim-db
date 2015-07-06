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

bool Bitmap::set_bit(const int index) {
	
	//Check if the desired bit is in range
	if (index >= 0 && index < bits_number_ ) {
	 
		//Locate the bit 
		int position = index / BITMAP_UNIT_SIZE;
		int remainder = index % BITMAP_UNIT_SIZE;
		
		//check if the bit is not already used
		if (!is_bit_set(index)) {
			// Set the bit to acknowledge that the bit is used
			bit_array_[position] |= 1ULL << remainder;
			return true;
		}
		else
			return false;
	}
	else
		return false;
};

bool Bitmap::clear_bit(const int index) {
	//Check if the desired bit is in range
	if (index >= 0 && index < bits_number_) {

		//Locate the bit 
		int position = index / BITMAP_UNIT_SIZE;
		int remainder = index % BITMAP_UNIT_SIZE;

		//Check if the bit is used
		if (is_bit_set(index)) {
			// Set the bit as being unused
			bit_array_[position] &= ~(1ULL << remainder);
			return true;
		}
		else
			return false;
	}
	else
		return false;
};

bool Bitmap::is_bit_set(const int index) {
	//Check if the desired bit is in range
	if (index >= 0 && index < bits_number_) {

		//locate the bit 
		int position = index / BITMAP_UNIT_SIZE;
		int remainder = index % BITMAP_UNIT_SIZE;

		return ((bit_array_[position] >> remainder) & 1);
	}
	else return false;
};

int Bitmap::bitset_count() {
	int result = 0;
	
	//Counts the number of bits used by iterating through the array
	for (int i = 0; i < bits_number_; ++i) {
		for (int j = 0; j < BITMAP_UNIT_SIZE; ++j) {
			result += ((bit_array_[i] >> j) & 1);
		}
	}

	return result;
}

int Bitmap::give_free_bit(const int last_used){
	int position = last_used / BITMAP_UNIT_SIZE;
	
	//Find an element with free bits
	while (bit_array_[position] == 0xffffffffffffffff) {
		++position;
		if (position == bits_array_size_) position = 0;
	}
	
	// Binary search for an unused bit
	UINT64 x = bit_array_[position];

	int right = 63;
	int left = 0;
	int middle = (right + left + 1) / 2;
	int half_power = middle - left;
	
	while (left < right) {
		UINT64 full = (1ULL << half_power) - 1;
	
		if ((((UINT64)(x >> left) >> half_power)&full) == full)
			right = middle-1;
		else
			left = middle;
	
		middle = (right + left + 1) / 2;
		half_power = middle - left;
	}

	set_bit(position * 64 + left);

	return position*64 + left;
}