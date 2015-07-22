#ifndef DATA_SECTOR_HPP_
#define DATA_SECTOR_HPP_

#include "base\generic-constants.hpp"
#include "base\serializable.hpp"
#include "parser\statement-node.hpp"
#include "metadata\database-value.hpp"
#include "schema\attribute.hpp"
#include "schema\table.hpp"

#include <vector>

class DataSector {
public:
	//Constructor
	DataSector(INT32 sector_id);
	~DataSector();
	BYTE* Select(int row_number);
	BYTE* Select();
private:
	BYTE* starting_pointer_;
	std::vector<int> rows_;
};

#endif