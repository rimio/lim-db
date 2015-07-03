#ifndef BITMAP_HPP_
#define BITMAP_HPP_

#include "base\generic-type-definitions.hpp"


class Bitmap {
	public:
		//Constructor
		Bitmap(int bits_number);

		//marks the sector at the specified index as being used
		int set_bit(int index);

		//marks the sector at the specified index as being unused
		int clear_bit(int index);

		//checks wether the sector at the specified index is used
		int is_bit_set(int index);

		//counts the total number of sectors used
		int bitset_count();

	protected:
	private:
		//total number of sectors
		int bits_number_;
		//keeps record of used and unused sectors
		UINT64 *bit_array_;
		//length of the array that holds the usage of sectors
		int bits_array_size_;

};

#endif