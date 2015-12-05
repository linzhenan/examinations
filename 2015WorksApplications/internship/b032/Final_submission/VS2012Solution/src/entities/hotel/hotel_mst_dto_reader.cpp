#include "hotel_mst_dto_reader.h"
#include "hotel_mst_dto.h"
#include "constants/constants.h"
#include "entities/icsv_master_dto.h"
#include <string>
#include <vector>
#include <cstdlib>
using namespace std;

HotelMstDTOReader::HotelMstDTOReader() {
	this->file_address = kDefaultCsvFolder + "HOTEL_MST.csv";
	AbstractDTOReader::init();
}

HotelMstDTOReader::HotelMstDTOReader(string &file_address) {
	this->file_address = file_address;
	AbstractDTOReader::init();
}

string HotelMstDTOReader::get_file_address() {
	return this->file_address;
}

ICsvMasterDTO *HotelMstDTOReader::convert_array_to_dto(vector<string> &value) {
	long hotel_id = atol(value[COLUMN_INDEX_HOTEL_ID].c_str());
	string hotel_name = value[COLUMN_INDEX_HOTEL_NAME];
	string address = value[COLUMN_INDEX_ADDRESS];
	string tel = value[COLUMN_INDEX_TEL];
	ICsvMasterDTO *obj = new HotelMstDTO(hotel_id, hotel_name, address, tel, 0 /* stars */);
	return obj;
}

HotelMstDTOReader::~HotelMstDTOReader() {

}

