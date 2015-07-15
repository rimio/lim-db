#ifndef BITMAP_HPP_
#define BITMAP_HPP_

#include "base\generic-type-definitions.hpp"


class Bitmap {
	public:
		//Constructor which leaves all the bits unset
		Bitmap(int bits_number);
		
		//Constructor which gives the opportunity to initialize all the bits to either set or unset
		Bitmap(int bits_number, bool set_bits);

		//Destructor
		~Bitmap();

		//Marks the sector at the specified index as being used
		bool SetBit(int index);

		//Marks the sector at the specified index as being unused
		bool ClearBit(int index);

		//Checks wether the sector at the specified index is used
		bool IsBitSet(int index);

		//Counts the total number of sectors used
		int BitsetCount();

		//Returns the position of a free bit or -1 if there is none left unused
		int GiveFreeBit(int last_used);

	private:
		//Total number of sectors
		int bits_number_;
		//Keeps record of used and unused sectors
		UINT64 *bit_array_;
		//Length of the array that holds the usage of sectors
		int bits_array_size_;
		//finds the position of an unset bit
		int find_unset_bit(UINT64 value);

};

#endif