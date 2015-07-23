#include "data-sector-test.hpp"
#include "storage\row-data.hpp"


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

	//DataSector *ds = new DataSector();
	RowData *rd = new RowData(t);

	BYTE *start = new BYTE;
	//start = ds->Select();
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
	end = rd->DeserializeRow(t, keep);
}