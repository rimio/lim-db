#ifndef DATA_SECTOR_HPP_
#define DATA_SECTOR_HPP_

#include "base\generic-constants.hpp"
#include "base\serializable.hpp"
#include "parser\statement-node.hpp"
#include "metadata\database-value.hpp"
#include "schema\attribute.hpp"
#include "schema\table.hpp"
#include "storage\sector.hpp"

#include <vector>

class DataSector: Sector {
	struct Slot {
		UINT16 offset;
		UINT16 length;
	};

public:
	~DataSector();
	BYTE* Select(int row_number);
	BYTE* Select();
private:
	BYTE* starting_pointer_;
	INT16 num_rows_;
	Slot slots_[1];

};

#endif