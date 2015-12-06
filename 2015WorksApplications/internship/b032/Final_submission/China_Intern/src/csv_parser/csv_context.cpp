#include "csv_context.h"

using namespace std;

CSVContext::CSVContext(string file_name)
{
	this->file_name = file_name;
	this->column_num = 0;
	this->row_num = 0;

	this->in = ifstream(this->file_name);
	this->csv_reader = new CSVReader(this->in);
	this->csv_reader->read_next(this->column_name);
	vector<string> row_context;
	while(this->csv_reader->read_next(row_context))
		this->context.push_back(row_context);
	this->in.close();
}
void CSVContext::save()
{
	this->out = ofstream(this->file_name);
	this->csv_writer = new CSVWriter(this->out);
	this->csv_writer->write_next(this->column_name);
	this->csv_writer->write_all(this->context);
	this->out.close();
}
CSVContext::~CSVContext()
{
	this->save();
}