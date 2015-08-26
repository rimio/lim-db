#include "data-sector-test.hpp"
#include "storage\sector.hpp"
#include "storage\row-data.hpp"
#include "storage\data-sector.hpp"
#include "boot\boot.hpp"
#include "base\generic-operations.hpp"
#include "metadata\database-value.hpp"
#include "parser\parser-context.hpp"

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
	DatabaseValue dbv = DatabaseValue(17);
	v1.push_back(dbv);
	name = "POPESCU";
	dbv.set_string_value(&name,true);
	v1.push_back(dbv);
	name = "ANDREI";
	DatabaseValue ddbv;
	ddbv.set_string_value(&name, true);
	v1.push_back(ddbv);
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
	name = "1POPESCU";
	dbv.set_string_value(&name, true);
	v2.push_back(DatabaseValue());
	name = "AAAANDREI";
	dbv.set_string_value(&name, true);
	v2.push_back(dbv);
	v2.push_back(DatabaseValue(125));
	v2.push_back(DatabaseValue());
	v2.push_back(DatabaseValue((float)12.7));
	v2.push_back(DatabaseValue((float)13.9));

	rd->set_data_values(v2);
	
	ptr = rd->SerializeRow(t, start);
	//insert second serialized row
	ds->Insert(start, ptr - start);
	
	where = ds->Select(1);
	ptr = rdd->DeserializeRow(t, where);
	
	where = ds->Select(1);
	ptr = rdd->DeserializeRow(t, where);
	
	where = ds->Select(0);
	ptr = rdd->DeserializeRow(t, where);
	
	std::vector<BYTE*> res;
	res = ds->Select();

	for (int i = 0; i < res.size(); i++) {
		ptr = rdd->DeserializeRow(t, res.at(i));
	}

	// Check Insert statement
	std::vector <std::string> scenario;
	std::string line;
	line = "Create table t (a int, b float, c string)";
	scenario.push_back(line);

	// Random checks
	line = "Insert into t(a) values (2)";
	scenario.push_back(line);
	line = "Insert into t values (2, null, 3+ null)";
	scenario.push_back(line);
	line = "Insert into t values (2.3, 4+ 5.9, not(null))";
	scenario.push_back(line);
	line = "Insert into t(a,c) values (9>5,2 > null)";
	scenario.push_back(line);

	// INT VALUE

	// Compare expressions
	line = "Insert into t(a) values (2>3)";
	scenario.push_back(line);
	line = "Insert into t(a) values (2>=3)";
	scenario.push_back(line);
	line = "Insert into t(a) values (2<3)";
	scenario.push_back(line);
	line = "Insert into t(a) values (2<=3)";
	scenario.push_back(line);
	line = "Insert into t(a) values (2=3)";
	scenario.push_back(line);
	line = "Insert into t(a) values (2!=3)";
	scenario.push_back(line);

	// Arithmetic expressions
	line = "Insert into t(a) values (2+3)";
	scenario.push_back(line);
	line = "Insert into t(a) values (2-3)";
	scenario.push_back(line);
	line = "Insert into t(a) values (2*3)";
	scenario.push_back(line);
	line = "Insert into t(a) values (8 /3)";
	scenario.push_back(line);
	line = "Insert into t(a) values (8 MOD 3)";
	scenario.push_back(line);

	// FLOAT VALUE

	// Compare expressions
	line = "Insert into t(b) values (2>3)";
	scenario.push_back(line);
	line = "Insert into t(b) values (2>=3)";
	scenario.push_back(line);
	line = "Insert into t(b) values (2<3)";
	scenario.push_back(line);
	line = "Insert into t(b) values (2<=3)";
	scenario.push_back(line);
	line = "Insert into t(b) values (2=3)";
	scenario.push_back(line);
	line = "Insert into t(b) values (2!=3)";
	scenario.push_back(line);

	// Arithmetic expressions
	line = "Insert into t(b) values (2+3)";
	scenario.push_back(line);
	line = "Insert into t(b) values (2-3)";
	scenario.push_back(line);
	line = "Insert into t(b) values (2*3)";
	scenario.push_back(line);
	line = "Insert into t(b) values (8 /3)";
	scenario.push_back(line);
	line = "Insert into t(b) values (8 MOD 3)";
	scenario.push_back(line);

	// STRING VALUE
	line = "Insert into t(c) values ('string')";
	scenario.push_back(line);
	line = "Insert into t(b) values (12 + '12')";
	scenario.push_back(line);
	line = "Insert into t(b) values (12.3 * '14.5')";
	scenario.push_back(line);

	line = "Insert into t(c) values ('abd'>'cd')";
	scenario.push_back(line);
	line = "Insert into t(c) values ('abd'>='cd')";
	scenario.push_back(line);
	line = "Insert into t(c) values ('abd'<'cd')";
	scenario.push_back(line);
	line = "Insert into t(c) values ('abd'<='cd')";
	scenario.push_back(line);
	line = "Insert into t(c) values ('abd'='cd')";
	scenario.push_back(line);
	line = "Insert into t(c) values ('abd'!='cd')";
	scenario.push_back(line);


	line = "drop table t";
	scenario.push_back(line);

	ErrorCode er = NO_ERROR;
	ParserContext context;
	ParserRoot *root;
	for (auto l : scenario)
	{
		er = context.parseString(l);
		root = context.getRootNode();
		root->Process();
	}

	delete root;

}