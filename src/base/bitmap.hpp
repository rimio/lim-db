#ifndef BITMAP_HPP_
#define BITMAP_HPP_

#include "base\generic-type-definitions.hpp"
#include "base\serializable.hpp"

class Bitmap: Serializable {
	public:
		// Constructor which leaves all the bits unset
		Bitmap(int bits_number) : Bitmap(bits_number, false) {};
		
		// Constructor which gives the opportunity to initialize all the bits to either set or unset
		Bitmap(int bits_number, bool set_bits);

		// Destructor
		~Bitmap();

		// Marks the bit at the specified index as being used
		bool SetBit(int index);

		// Marks the bit at the specified index as being unused
		bool ClearBit(int index);

		// Checks wether the bit at the specified index is used
		bool IsBitSet(int index);

		// Counts the total number of bits used
		int BitsetCount();

		// Returns the position of a free bit or -1 if there is none left unused
		int GiveFreeBit(int last_used);

		// Serializes the array of bits
		BYTE* Serialize(BYTE *ptr) override;

		// Deserializez the array of bits
		BYTE* Deserialize(BYTE *ptr) override;

	private:
		// Total number of bits
		int bits_number_;
		// Keeps record of used and unused bits
		UINT64 *bit_array_;
		// Length of the array that holds the usage of bits
		int bits_array_size_;
		// Finds the position of an unset bit
		int find_unset_bit(UINT64 value);

};

#endif