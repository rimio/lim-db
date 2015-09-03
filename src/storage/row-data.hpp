#ifndef ROW_DATA_HPP_
#define ROW_DATA_HPP_

#include "metadata\database-value.hpp"
#include "schema\attribute.hpp"
#include "schema\table.hpp"
#include "storage\data-sector.hpp"
#include "parser\parser-column.hpp"

#include <vector>

class RowData {
public:
	RowData (Table *t);
	~RowData () {};
	// Serializes a row starting at the location of *start
	// Retreives a pointer to the end of serialization
	BYTE* SerializeRow (BYTE* start);
	// Deserializes a row starting at the location of *start
	// Retreives a pointer to the end of deserialization
	BYTE* DeserializeRow (BYTE* start);
	void set_data_values (std::vector<DatabaseValue> values, std::vector<Attribute> columns);
	std::vector<DatabaseValue> values() { return values_; }
private:
	std::vector<DatabaseValue> values_;
	Table *table_;
};

#endif