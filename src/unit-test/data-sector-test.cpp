#include "data-sector-test.hpp"
#include "storage\sector.hpp"
#include "storage\row-data.hpp"
#include "storage\data-sector.hpp"
#include "boot\boot.hpp"
#include "base\generic-operations.hpp"
#include "metadata\database-value.hpp"

#define INT32_ALIGNMENT 4

void DataSectorTest::check() {
	Table *t = new Table();
	BYTE row_data_buffer[SECTOR_MAX_SIZE + INT32_ALIGNMENT];

	t->AddAttribute("COD", DB_INTEGER);
	t->AddAttribute("NUME", DB_STRING);
	t->AddAttribute("PRENUME", DB_STRING);
	t->AddAttribute("VARSTA", DB_INTEGER);
	t->AddAttribute("ALTA_VARSTA", DB_INTEGER);
	t->AddAttribute("SCOR", DB_FLOAT); 
	t->AddAttribute("SCOR_NOU", DB_FLOAT);

	Boot::StartServer();

	void *buffer = malloc(SECTOR_MAX_SIZE*sizeof(BYTE));
	DataSector *ds = reinterpret_cast<DataSector*> (buffer);
	ds->UseDataSector(ds);

	RowData *rd = new RowData(t);
	BYTE *start = PTR_ALIGN_UPPER(row_data_buffer, INT32_ALIGNMENT);
	BYTE *ptr;
	std::string name;
	std::vector<DatabaseValue> v1;
	v1.push_back(DatabaseValue(17));
	name = "POPOESCU";
	v1.push_back(DatabaseValue(&name));
	name = "ANDREI";
	v1.push_back(DatabaseValue(&name));
	v1.push_back(DatabaseValue(25));
	v1.push_back(DatabaseValue(34));
	v1.push_back(DatabaseValue((float)2.7));
	v1.push_back(DatabaseValue((float)3.9));

	rd->set_data_values(v1);

	ptr = rd->SerializeRow(t, start);

	//insert first serialized row
	ds->Insert(start, ptr - start);
	
	RowData *rdd = new RowData(t);
	BYTE* where = ds->Select(0);
	ptr = rdd->DeserializeRow(t, where);

	std::vector<DatabaseValue> v2;
	v2.push_back(DatabaseValue(117));
	name = "1POPOESCU";
	v2.push_back(DatabaseValue(&name));
	name = "1ANDREI";
	v2.push_back(DatabaseValue());
	v2.push_back(DatabaseValue(125));
	v2.push_back(DatabaseValue());
	v2.push_back(DatabaseValue((float)12.7));
	v2.push_back(DatabaseValue((float)13.9));

	rd->set_data_values(v2);
	
	ptr = rd->SerializeRow(t, start);
	//insert second serialized row
	ds->Insert(start, ptr - start);
	rdd = new RowData(t);
	where = ds->Select(1);
	ptr = rdd->DeserializeRow(t, where);
	rdd = new RowData(t);
	where = ds->Select(1);
	ptr = rdd->DeserializeRow(t, where);
	rdd = new RowData(t);
	where = ds->Select(0);
	ptr = rdd->DeserializeRow(t, where);
	
	std::vector<BYTE*> res;
	res = ds->Select();

	for (int i = 0; i < res.size(); i++) {
		rdd = new RowData(t);
		ptr = rdd->DeserializeRow(t, res.at(i));
	}

}