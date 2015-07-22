#include "storage\row-data.hpp"

RowData::RowData(Table *t) {
	std::vector<Attribute> attributes = t->get_table_attributes();

	for (std::vector<Attribute>::iterator atr = attributes.begin(); atr != attributes.end(); ++atr) 
		switch (atr->get_type()) {
			case DB_INTEGER:
				values_.push_back(new IntDatabaseValue());
				break;
			case DB_FLOAT:
				values_.push_back(new FloatDatabaseValue());
				break;
			case DB_STRING:
				values_.push_back(new StringDatabaseValue());
				break;
		}
}

BYTE* RowData::SerializeRow(Table * t, BYTE* start) {
	std::vector<Attribute> attributes = t->get_table_attributes();
	// Starting position of the offset values
	BYTE *o_pos = start;
	// Starting position of the integer values
	BYTE *i_pos = o_pos + 4 * (t->get_nr_string());
	// Starting position of the float values
	BYTE *f_pos = i_pos + 4 * (t->get_nr_int());
	// Starting position of the strings
	BYTE *s_pos = f_pos + 8 * (t->get_nr_float());

	for (int i = 0; i < values_.size(); i++) {
		switch ((*values_.at(i)).get_type()) {
			case DB_INTEGER:
				i_pos = (*values_.at(i)).Serialize(i_pos);
				break;
			case DB_FLOAT:
				f_pos = (*values_.at(i)).Serialize(f_pos);
				break;
			case DB_STRING:
				//Tracks where the string starts
				INT32 *p = (INT32*)o_pos;
				*p = (INT32)(s_pos - start);
				o_pos += 4;
				s_pos = (*values_.at(i)).Serialize(s_pos);
			break;
		}
	}
	return s_pos;
}

BYTE* RowData::DeserializeRow(Table *t, BYTE *start) {
	std::vector<Attribute> attributes = t->get_table_attributes();
	// Starting position of the offset values
	BYTE *o_pos = start;
	// Starting position of the integer values
	BYTE *i_pos = o_pos + 4 * (t->get_nr_string());
	// Starting position of the float values
	BYTE *f_pos = i_pos + 4 * (t->get_nr_int());
	// Starting position of the strings
	BYTE *s_pos = f_pos + 8 * (t->get_nr_float());

	for (int i = 0; i < attributes.size(); i++) {
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