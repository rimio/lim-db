#include "base\bitmap.hpp"

#include <cstdio>
#include <cstring>
#include "base\generic-operations.hpp"

#define BITMAP_UNIT_SIZE 64

#define BITMAP_FULL_UNIT 0xFFFFFFFFFFFFFFFF
#define BITMAP_EMPTY_UNIT 0ULL

Bitmap::~Bitmap(){
	delete bit_array_;
}

Bitmap::Bitmap(int bits_number, bool set_bits) {
	bits_number_ = bits_number;
	bits_array_size_ = (bits_number_ - 1) / BITMAP_UNIT_SIZE + 1;
	bit_array_ = new UINT64[bits_array_size_];
	
	if (set_bits) {
		for (int i = 0; i < bits_array_size_; ++i)
			bit_array_[i] = BITMAP_FULL_UNIT;
	}
	else {
		for (int i = 0; i < bits_array_size_; ++i)
			bit_array_[i] = BITMAP_EMPTY_UNIT;
	}
	 
	// Bits that are out of range must be set to 1 (we could consider them used, therefore, inaccessible )
	// Reversed process if set_bits is true
	int i = bits_number - (bits_array_size_-1) * BITMAP_UNIT_SIZE;
	if (!set_bits) {
		if (i != BITMAP_UNIT_SIZE) bit_array_[bits_array_size_ - 1] = (BITMAP_FULL_UNIT << i);
	}
	else {
		if (i != BITMAP_UNIT_SIZE) bit_array_[bits_array_size_ - 1] = (BITMAP_FULL_UNIT >> (BITMAP_UNIT_SIZE - i));
	}
};

bool Bitmap::SetBit(int index) {
	
	//Check if the desired bit is in range
	if (index < 0 || index >= bits_number_)
		return false;

	//Locate the bit 
	int position = index / BITMAP_UNIT_SIZE;
	int remainder = index % BITMAP_UNIT_SIZE;
		
	//check if the bit is not already used
	if (IsBitSet(index))
		return false;
		
	// Set the bit to acknowledge that the bit is used
	bit_array_[position] |= 1ULL << remainder;
	return true;
};

bool Bitmap::ClearBit(int index) {
	//Check if the desired bit is in range
	if (index < 0 || index >= bits_number_)
		return false;

	//Locate the bit 
	int position = index / BITMAP_UNIT_SIZE;
	int remainder = index % BITMAP_UNIT_SIZE;

	//Check if the bit is used
	if (!IsBitSet(index))
		return false;

	// Set the bit as being unused
	bit_array_[position] &= ~(1ULL << remainder);
	return true;
};

bool Bitmap::IsBitSet(int index) {
	//Check if the desired bit is in range
	if (index < 0 || index >= bits_number_)
		return true;

	//locate the bit 
	int position = index / BITMAP_UNIT_SIZE;
	int remainder = index % BITMAP_UNIT_SIZE;

	return ((bit_array_[position] >> remainder) & 1);
};

int Bitmap::BitsetCount() {
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

int Bitmap::GiveFreeBit(int last_used){
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
	SetBit(position * 64 + left);

	return position*64 + left;
}

int Bitmap::find_unset_bit(UINT64 value) {
	int position = 0;
	int cond = 0;
	//The algorithm asserts that the input has at least one free bit
	//The algorithm finds an unsetted bit by constantly splitting a part in two halves
	//If the first half is full, choose to search in the second one
	//The algorithm stops when only one bit is considered, therefore it's a 0 and can not be splitted furthermore
	//It retreives the position of that bit
#define step(x) \
	do { \
		cond = !((value >> (x)) == (1ULL << (x)) - 1); \
		(value) = (value >> (cond * (x))); \
		(value) &= ((1ULL << (x)) - 1); \
		position = position + (cond * (x)); \
	} while (false)

	step(32);
	step(16);
	step(8);
	step(4);
	step(2);
	step(1);

#undef step

	return position;
}

BYTE* Bitmap::Serialize(BYTE *ptr) {
	memcpy(ptr, bit_array_, bits_array_size_ * 8 * sizeof(BYTE));
	return ptr + bits_array_size_ * 8;
}

BYTE* Bitmap::Deserialize(BYTE *ptr) {
	memcpy(bit_array_, ptr, bits_array_size_ * 8 * sizeof(BYTE));
	return ptr + bits_array_size_ * 8;
}