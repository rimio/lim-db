#include "storage\row-data.hpp"
RowData::RowData(Table *t) {
	std::vector<Attribute> attributes = t->get_table_attributes();

	for (std::vector<Attribute>::iterator atr = attributes.begin(); atr != attributes.end(); ++atr) 
		switch (atr->get_type()) {
			case DB_INTEGER:
				values_.push_back(new DatabaseValue(NULL));
				break;
			case DB_FLOAT:
				values_.push_back(new DatabaseValue(NULL));
				break;
			case DB_STRING:
				values_.push_back(new DatabaseValue(NULL));
				break;
		}
}

BYTE* RowData::SerializeRow(Table * t, BYTE* start) {
	std::vector<Attribute> attributes = t->get_table_attributes();
	// First 8 bytes allocated for 2 dummy variables
	// Starting position of the offset values
	BYTE *o_pos = start + 8;
	// Starting position of the integer values
	BYTE *i_pos = o_pos + 4 * (t->get_nr_string());
	// Starting position of the float values
	BYTE *f_pos = i_pos + 4 * (t->get_nr_int());
	// Starting position of the strings
	BYTE *s_pos = f_pos + 8 * (t->get_nr_float());

	for (int i = 0; i < values_.size(); i++) {
		(*values_.at(i)).set_type(attributes.at(i).get_type());
		switch (attributes.at(i).get_type()) {
			case DB_INTEGER:
				i_pos = (*values_.at(i)).Serialize(i_pos);
				break;
			case DB_FLOAT:
				f_pos = (*values_.at(i)).Serialize(f_pos);
				break;
			case DB_STRING:
				//Tracks where the string starts
				INT32 arg = s_pos - start;
				memcpy(o_pos, &arg, sizeof(arg));
				o_pos += 4;
				s_pos = (*values_.at(i)).Serialize(s_pos);
				break;
		}
	}
	return s_pos;
}

BYTE* RowData::DeserializeRow(Table *t, BYTE *start) {
	std::vector<Attribute> attributes = t->get_table_attributes();
	// First 8 bytes allocated for 2 dummy variables
	// Starting position of the offset values
	BYTE *o_pos = start + 8;
	// Starting position of the integer values
	BYTE *i_pos = o_pos + 4 * (t->get_nr_string());
	// Starting position of the float values
	BYTE *f_pos = i_pos + 4 * (t->get_nr_int());
	// Starting position of the strings
	BYTE *s_pos = f_pos + 8 * (t->get_nr_float());

	for (int i = 0; i < attributes.size(); i++) {
		(*values_.at(i)).set_type(attributes.at(i).get_type());
		switch (attributes.at(i).get_type())
		{
		case DB_INTEGER:
			i_pos = (*values_.at(i)).Deserialize(i_pos);
			break;
		case DB_FLOAT:
			f_pos = (*values_.at(i)).Deserialize(f_pos);
			break;
		case DB_STRING:
			s_pos = (*values_.at(i)).Deserialize(s_pos);
			break;
		default:
			break;
		}
	}
	return s_pos;
}

void RowData::set_data_values(std::vector<DatabaseValue*> values) {
	values_ = values;
}