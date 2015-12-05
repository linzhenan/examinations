#ifndef HOTEL_MST_DTO_READER_H_
#define HOTEL_MST_DTO_READER_H_

#include "entities/abstract_dto_reader.h"
#include "hotel_mst_dto.h"
#include "entities/icsv_master_dto.h"

class HotelMstDTOReader: public AbstractDTOReader {
public:
	HotelMstDTOReader();
	HotelMstDTOReader(string &file_address);
	ICsvMasterDTO *convert_array_to_dto(vector<string> &value);
	string get_file_address();
	~HotelMstDTOReader();

private:
	string file_address;
	static const int COLUMN_INDEX_HOTEL_ID = 0;
	static const int COLUMN_INDEX_HOTEL_NAME = 1;
	static const int COLUMN_INDEX_ADDRESS = 2;
	static const int COLUMN_INDEX_TEL = 3;
};

#endif /* HOTEL_MST_DTO_READER_H_ */
