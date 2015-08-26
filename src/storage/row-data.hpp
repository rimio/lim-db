#ifndef ROW_DATA_HPP_
#define ROW_DATA_HPP_

#include "metadata\database-value.hpp"
#include "schema\attribute.hpp"
#include "schema\table.hpp"
#include "storage\data-sector.hpp"

#include <vector>

class RowData {
public:
	RowData(Table *t);
	~RowData() {};
	// Serializes a row starting at the location of *start
	// Retreives a pointer to the end of serialization
	BYTE* SerializeRow(Table *t, BYTE* start);
	// Deserializes a row starting at the location of *start
	// Retreives a pointer to the end of deserialization
	BYTE* DeserializeRow(Table *t, BYTE* start);
	void set_data_values(std::vector<DatabaseValue> values);
private:
	std::vector<DatabaseValue> values_;
};

#endif