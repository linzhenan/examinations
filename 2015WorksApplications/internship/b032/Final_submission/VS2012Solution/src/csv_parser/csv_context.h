#include "csv_reader.h"
#include "csv_writer.h"
#include <iostream>
#include <fstream>

class CSVContext
{
private:
	string file_name;
	CSVReader *csv_reader;
	CSVWriter *csv_writer;
	ifstream in;
	ofstream out;
public:
	int column_num;
	int row_num;
	vector<string> column_name;
	vector<vector<string>> context;
	CSVContext(string file_name);
	~CSVContext();
	void save();
};