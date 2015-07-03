#ifndef BITMAP_HPP_
#define BITMAP_HPP_

#include "base\generic-type-definitions.hpp"


class Bitmap {
	public:
		//Constructor
		Bitmap(INT64 length_of_array);

		//marks the sector at the specified index as being used
		void set_bit(INT64 index);

		//marks the sector at the specified index as being unused
		void clear_bit(INT64 index);

		//checks wether the sector at the specified index is used
		bool is_bit_set(INT64 index);

		//counts the total number of sectors used
		INT64 bitset_count();

	protected:
	private:
		//length of the array that holds the usage of sectors
		INT64 number_of_sectors_;
		//keeps record of used and unused sectors
		INT64 *sectors_;

};

#endif