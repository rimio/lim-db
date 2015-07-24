#include "data-sector-test.hpp"
#include "storage\sector.hpp"
#include "storage\row-data.hpp"
#include "storage\data-sector.hpp"
#include "boot\boot.hpp"

void DataSectorTest::check() {
	Table *t = new Table();
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
	ds->UseDataSector(ds,4096);

	RowData *rd = new RowData(t);

	BYTE *start = new BYTE;
	BYTE *keep = new BYTE;
	keep = start;
	
	std::vector<DatabaseValue*> v1;
	v1.push_back(new IntDatabaseValue(17));
	v1.push_back(new StringDatabaseValue("POPESCU"));
	v1.push_back(new StringDatabaseValue("ANDREI"));
	v1.push_back(new IntDatabaseValue(25));
	v1.push_back(new IntDatabaseValue(34));
	v1.push_back(new FloatDatabaseValue(2.7));
	v1.push_back(new FloatDatabaseValue(3.9));

	rd->set_data_values(v1);

	BYTE *end = rd->SerializeRow(t, start);
	//insert first serialized row
	ds->Insert(keep, end - keep );
	
	BYTE* where = ds->Select(0);
	end = rd->DeserializeRow(t, where);

	std::vector<DatabaseValue*> v2;
	v2.push_back(new IntDatabaseValue(117));
	v2.push_back(new StringDatabaseValue("1POPESCU"));
	v2.push_back(new StringDatabaseValue("1ANDREI"));
	v2.push_back(new IntDatabaseValue(125));
	v2.push_back(new IntDatabaseValue(134));
	v2.push_back(new FloatDatabaseValue(12.7));
	v2.push_back(new FloatDatabaseValue(13.9));

	rd->set_data_values(v2);
	
	end = rd->SerializeRow(t, start);
	//insert second serialized row
	ds->Insert(keep, end - keep);

	where = ds->Select(1);
	end = rd->DeserializeRow(t, where);

	where = ds->Select(1);
	end = rd->DeserializeRow(t, where);

	where = ds->Select(0);
	end = rd->DeserializeRow(t, where);

}