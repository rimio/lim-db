#include "base\bitmap.hpp"

#include <stdio.h>

#define BITMAP_UNIT_SIZE 64

Bitmap::Bitmap(int bits_number) {
	bits_number_ = bits_number;
	bits_array_size_ = (bits_number_ - 1) / BITMAP_UNIT_SIZE + 1;
	bit_array_ = new UINT64[bits_array_size_];
	for (int i = 0; i < bits_array_size_; ++i)
		bit_array_[i] = 0;
	//Bits that are out of range must be set to 1 (we could consider them used, therefore, inaccessible )
	for (int i = bits_number; i < bits_array_size_ * BITMAP_UNIT_SIZE; i++)
		set_bit(i);
};

bool Bitmap::set_bit(int index) {
	
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

bool Bitmap::clear_bit(int index) {
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

bool Bitmap::is_bit_set(int index) {
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
	for (int i = 0; i < bits_array_size_-1; ++i) {
		for (int j = 0; j < BITMAP_UNIT_SIZE; ++j) {
			result += ((bit_array_[i] >> j) & 1);
		}
	}
	int length = bits_number_ % BITMAP_UNIT_SIZE;
	if (length == 0)  length = BITMAP_UNIT_SIZE;
	for (int j = 0; j < length; ++j) {
		result += ((bit_array_[bits_array_size_-1] >> j) & 1);
	}

	return result;
}

int Bitmap::give_free_bit(int last_used){
	bool full_search = false;
	int position = last_used / BITMAP_UNIT_SIZE;

	//Check that allocation table is not full

	//Find an element with free bits
	while (bit_array_[position] == 0xffffffffffffffff) {
		++position;
		if (position == bits_array_size_) {
			full_search = true;
			position = 0;
		}
		//Check that allocation table is not full
		if (full_search && position == last_used / BITMAP_UNIT_SIZE) return -1;
	}

	int left = find_unset_bit(bit_array_[position]);
	set_bit(position * 64 + left);

	return position*64 + left;
}

int Bitmap::find_unset_bit(UINT64 value) {
	int position = 0;
	//The algorithm asserts that the input has at least one free bit
	//The algorithm finds an unsetted bit by constantly splitting a part in two halves
	//If the first half is full, choose to search in the second one
	//The algorithm stops when only one bit is considered, therefore it's a 0 and can not be splitted furthermore
	//It retreives the position of that bit
	if ((value >> 32) == 0xffffffff) {
		value = (value & 0xffffffff);
	}
	else {
		value = value >> 32;
		position += 32;
	}
	
	if ((value >> 16) == 0x0000ffff) {
		value = (value & 0x0000ffff);
	}
	else {
		value = value >> 16;
		position += 16;
	}

	if ((value >> 8)  == 0x000000ff) {
		value = (value & 0x000000ff);
	}
	else {
		value = value >> 8;
		position += 8;
	}

	if ((value >> 4) == 0x0000000f) {
		value = (value & 0x0000000f);
	}
	else {
		value = value >> 4;
		position += 4;
	}

	if ((value >> 2)  == 0x00000003) {
		value = (value & 0x00000003);
	}
	else {
		value = value >> 2;
		position += 2;
	}

	if ((value >> 1)  == 0x00000001) {
		value = (value & 0x0000001);
	}
	else {
		value = value >> 1;
		position += 1;
	}
	return position;
}