#include "data-sector-test.hpp"
#include "storage\sector.hpp"
#include "storage\row-data.hpp"
#include "storage\data-sector.hpp"
#include "boot\boot.hpp"
#include "base\generic-operations.hpp"

#define INT32_ALIGNMENT 4

void DataSectorTest::check() {
	Table *t = new Table();
	BYTE row_data_buffer[SECTOR_MAX_SIZE + INT32_ALIGNMENT];

	t->AddAttribute("COD", DB_INTEGER, 1);
	t->AddAttribute("NUME", DB_STRING, 2);
	t->AddAttribute("PRENUME", DB_STRING, 3);
	t->AddAttribute("VARSTA", DB_INTEGER, 4);
	t->AddAttribute("ALTA_VARSTA", DB_INTEGER, 5);
	t->AddAttribute("SCOR", DB_FLOAT, 6); 
	t->AddAttribute("SCOR_NOU", DB_FLOAT, 7);

	t->set_nr_float(2);
	t->set_nr_int(3);
	t->set_nr_string(2);

	Boot::StartServer();

	void *buffer = malloc(SECTOR_MAX_SIZE*sizeof(BYTE));
	DataSector *ds = reinterpret_cast<DataSector*> (buffer);
	ds->UseDataSector(ds);

	RowData *rd = new RowData(t);

	BYTE *start = PTR_ALIGN_UPPER(row_data_buffer, INT32_ALIGNMENT);
	BYTE *ptr;
	
	std::vector<DatabaseValue*> v1;
	v1.push_back(new IntDatabaseValue(17));
	v1.push_back(new StringDatabaseValue("POPESCU"));
	v1.push_back(new StringDatabaseValue("ANDREI"));
	v1.push_back(new IntDatabaseValue(25));
	v1.push_back(new IntDatabaseValue(34));
	v1.push_back(new FloatDatabaseValue(2.7));
	v1.push_back(new FloatDatabaseValue(3.9));

	rd->set_data_values(v1);

	ptr = rd->SerializeRow(t, start);

	//insert first serialized row
	ds->Insert(start, ptr - start);
	
	BYTE* where = ds->Select(0);
	ptr = rd->DeserializeRow(t, where);

	std::vector<DatabaseValue*> v2;
	v2.push_back(new IntDatabaseValue(117));
	v2.push_back(new StringDatabaseValue("1POPESCU"));
	v2.push_back(new StringDatabaseValue("1ANDREI"));
	v2.push_back(new IntDatabaseValue(125));
	v2.push_back(new IntDatabaseValue(134));
	v2.push_back(new FloatDatabaseValue(12.7));
	v2.push_back(new FloatDatabaseValue(13.9));

	rd->set_data_values(v2);
	
	ptr = rd->SerializeRow(t, start);
	//insert second serialized row
	ds->Insert(start, ptr - start);
	
	where = ds->Select(1);
	ptr = rd->DeserializeRow(t, where);

	where = ds->Select(1);
	ptr = rd->DeserializeRow(t, where);

	where = ds->Select(0);
	ptr = rd->DeserializeRow(t, where);
	
	std::vector<BYTE*> res;
	res = ds->Select();

	for (int i = 0; i < res.size(); i++) {
		ptr = rd->DeserializeRow(t, res.at(i));
	}

}