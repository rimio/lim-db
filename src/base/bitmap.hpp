#ifndef BITMAP_HPP_
#define BITMAP_HPP_

#include "base\generic-type-definitions.hpp"


class Bitmap {
	public:
		//Constructor which leaves all the bits unset
		Bitmap(int bits_number);
		
		//Constructor which gives the opportunity to initialize all the bits to either set or unset
		Bitmap(int bits_number, bool set_bits);

		//Marks the sector at the specified index as being used
		bool set_bit(int index);

		//Marks the sector at the specified index as being unused
		bool clear_bit(int index);

		//Checks wether the sector at the specified index is used
		bool is_bit_set(int index);

		//Counts the total number of sectors used
		int bitset_count();

		//Returns the position of a free bit or -1 if there is none left unused
		int give_free_bit(int last_used);

	protected:
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