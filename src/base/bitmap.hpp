#ifndef BITMAP_HPP_
#define BITMAP_HPP_

#include "base\generic-type-definitions.hpp"


class Bitmap {
	public:
		//Constructor
		Bitmap(UINT64 length_of_array);

		//marks the sector at the specified index as being used
		bool set_bit(UINT64 index);

		//marks the sector at the specified index as being unused
		bool clear_bit(UINT64 index);

		//checks wether the sector at the specified index is used
		bool is_bit_set(UINT64 index);

		//counts the total number of sectors used
		UINT64 bitset_count();

	protected:
	private:
		//length of the array that holds the usage of sectors
		INT64 bits_number_;
		//keeps record of used and unused sectors
		UINT64 *bit_array_;

};

#endif