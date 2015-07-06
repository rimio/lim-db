#ifndef BITMAP_HPP_
#define BITMAP_HPP_

#include "base\generic-type-definitions.hpp"


class Bitmap {
	public:
		//Constructor
		Bitmap(const int bits_number);

		//Marks the sector at the specified index as being used
		bool set_bit(const int index);

		//Marks the sector at the specified index as being unused
		bool clear_bit(const int index);

		//Checks wether the sector at the specified index is used
		bool is_bit_set(const int index);

		//Counts the total number of sectors used
		int bitset_count();

		//Returns a free bit
		int give_free_bit(const int last_used);

	protected:
	private:
		//Total number of sectors
		int bits_number_;
		//Keeps record of used and unused sectors
		UINT64 *bit_array_;
		//Length of the array that holds the usage of sectors
		int bits_array_size_;

};

#endif