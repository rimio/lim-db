#include "storage\row-data.hpp"
RowData::RowData(Table *t) {
	values_.clear();
	table_ = t;
	values_.resize(t->get_number_of_attributes(),DatabaseValue());
}

BYTE* RowData::SerializeRow(BYTE* start) {
	std::vector<Attribute> attributes = table_->get_table_attributes();
	// First 8 bytes allocated for 2 dummy variables
	// Starting position of the is_null_ values
	BYTE *n_pos = start + 8;
	// Starting position of the offset values
	BYTE *o_pos = n_pos + 4 * table_->get_number_of_attributes();
	// Starting position of the integer values
	BYTE *i_pos = o_pos + 4 * (table_->get_nr_string());
	// Starting position of the float values
	BYTE *f_pos = i_pos + 4 * (table_->get_nr_int());
	// Starting position of the strings
	BYTE *s_pos = f_pos + 8 * (table_->get_nr_float());

	for (int i = 0; i < values_.size(); i++) {
		values_.at(i).set_type(attributes.at(i).get_type());
		
		INT32 empty = values_.at(i).is_null();
		memcpy(n_pos, &empty, sizeof(INT32));
		n_pos += 4;
		
		switch (attributes.at(i).get_type()) {
			case DB_INTEGER:
				if (empty) 
					i_pos += 4;
				else 
					i_pos = values_.at(i).Serialize(i_pos);
				break;
			case DB_FLOAT:
				if (empty) 
					f_pos += 8;
				else 
					f_pos = values_.at(i).Serialize(f_pos);
				break;
			case DB_STRING:
				//Tracks where the string starts
				INT32 arg = s_pos - start;
				if (!empty) {
					memcpy(o_pos, &arg, sizeof(arg));
					s_pos = values_.at(i).Serialize(s_pos);
				}
				o_pos += 4;
			break;
		}
	}
	return s_pos;
}

BYTE* RowData::DeserializeRow(BYTE *start) {
	std::vector<Attribute> attributes = table_->get_table_attributes();
	// First 8 bytes allocated for 2 dummy variables
	// Starting position of the is_null_ values
	BYTE *n_pos = start + 8;
	// Starting position of the offset values
	BYTE *o_pos = n_pos + 4 * table_->get_number_of_attributes();
	// Starting position of the integer values
	BYTE *i_pos = o_pos + 4 * (table_->get_nr_string());
	// Starting position of the float values
	BYTE *f_pos = i_pos + 4 * (table_->get_nr_int());
	// Starting position of the strings
	BYTE *s_pos = f_pos + 8 * (table_->get_nr_float());

	for (int i = 0; i < attributes.size(); i++) {
		values_.at(i).set_type(attributes.at(i).get_type());

		INT32 empty;
		n_pos = Serializable::DeserializeInt(n_pos, &empty);
		if (empty)
			values_.at(i).set_is_null(true);
		else
			values_.at(i).set_is_null(false);
		switch (attributes.at(i).get_type())
		{
		case DB_INTEGER:
			if (empty)
				i_pos += 4;
			else
				i_pos = values_.at(i).Deserialize(i_pos);
			break;
		case DB_FLOAT:
			if (empty)
				f_pos += 8;
			else
				f_pos = values_.at(i).Deserialize(f_pos);
			break;
		case DB_STRING:
			if (!empty)
				s_pos = values_.at(i).Deserialize(s_pos);
			break;
		default:
			break;
		}
	}
	printf("\n");
	return s_pos;
}

void RowData::set_data_values(std::vector<DatabaseValue> values, std::vector<Attribute> columns) {
	auto attributes = table_->get_table_attributes();
	bool right_order = true;
	
	// Check if all the columns are used and in right order
	if (table_->get_number_of_attributes() == values.size()) {
		for (int i = 0; i < values.size(); i++)
			if (attributes.at(i).get_name() != columns.at(i).get_name()) {
				right_order = false;
				break;
			}
	}
	else {
		right_order = false;
	}
	
	if (right_order) {
		values_.assign(values.begin(), values.end());
		return;
	}
	
	// Otherwise fill them with NULL values and/or reorder them
	for (int i = 0; i < columns.size(); i++) {
		values_[columns.at(i).get_position() - 1].Clone(values[i]);
		}

	return;
}