#include "storage\row-data.hpp"

#include "base\generic-constants.hpp"
#include "base\generic-operations.hpp"
#include "base\bitmap.hpp"

RowData::RowData(Table *t) {
	values_.clear();
	values_.resize(t->get_number_of_attributes(),DatabaseValue());
}

BYTE* RowData::SerializeRow(Table * t, BYTE* start) {
	std::vector<Attribute> attributes = t->get_table_attributes();
	// First 8 bytes allocated for 2 dummy variables
	// Starting position of the is_null_ values
	BYTE *n_pos = start + 8;
	// Starting position of the offset values
	int n_bytes = (t->get_number_of_attributes() + BYTE_UNIT_SIZE - 1) / BYTE_UNIT_SIZE;
	BYTE *o_pos = n_pos + ALIGN_SIZE(n_bytes, 8);
	// Starting position of the integer values
	BYTE *i_pos = o_pos + 4 * (t->get_nr_string());
	// Starting position of the float values
	BYTE *f_pos = i_pos + 4 * (t->get_nr_int());
	// Starting position of the strings
	BYTE *s_pos = f_pos + 8 * (t->get_nr_float());
	
	Bitmap bmp = Bitmap(t->get_number_of_attributes());

	for (int i = 0; i < values_.size(); i++) {
		values_.at(i).set_type(attributes.at(i).get_type());
		
		// Set is_null value
		INT32 empty = values_.at(i).is_null();
		if (empty)
			bmp.SetBit(i);
		else
			bmp.ClearBit(i);

		// Set value
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

	BYTE *is_null_list = (BYTE*)bmp.bit_array();
	memcpy(n_pos, is_null_list, ALIGN_SIZE(n_bytes, 8) * sizeof(BYTE));

	return s_pos;
}

BYTE* RowData::DeserializeRow(Table *t, BYTE *start) {
	std::string dummy_string = " ";
	std::vector<Attribute> attributes = t->get_table_attributes();
	// First 8 bytes allocated for 2 dummy variables
	// Starting position of the is_null_ values
	BYTE *n_pos = start + 8;
	// Starting position of the offset values
	int n_bytes = (t->get_number_of_attributes() + BYTE_UNIT_SIZE - 1) / BYTE_UNIT_SIZE;
	BYTE *o_pos = n_pos + ALIGN_SIZE(n_bytes, 8);
	// Starting position of the integer values
	BYTE *i_pos = o_pos + 4 * (t->get_nr_string());
	// Starting position of the float values
	BYTE *f_pos = i_pos + 4 * (t->get_nr_int());
	// Starting position of the strings
	BYTE *s_pos = f_pos + 8 * (t->get_nr_float());

	Bitmap bmp = Bitmap(t->get_number_of_attributes());
	
	bmp.SetBits((UINT64*)n_pos, t->get_number_of_attributes());
	
	for (int i = 0; i < attributes.size(); i++) {
		values_.at(i).set_type(attributes.at(i).get_type());

		// Get is_null value
		INT32 empty;
		
		empty = bmp.IsBitSet(i);

		if (empty)
			values_.at(i).set_is_null();

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
			if (!empty) {
				values_.at(i).set_string_value(&dummy_string, true);
				s_pos = values_.at(i).Deserialize(s_pos);
			}
			break;
		default:
			break;
		}
	}

	return s_pos;
}

void RowData::set_data_values(std::vector<DatabaseValue> values) {
	values_.assign(values.begin(),values.end());
}