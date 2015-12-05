#ifndef HOTEL_DTO_H_
#define HOTEL_DTO_H_

#include "entities/icsv_master_dto.h"
#include <string>
using namespace std;

class HotelMstDTO: public ICsvMasterDTO {
public:
	HotelMstDTO(long hotel_id, string hotel_name, string address, string tel,
			int stars);
	long &get_hotel_id();
	string &get_hotel_name();
	string &get_address();
	string &get_tel();

	friend ostream &operator <<(ostream &out, HotelMstDTO &obj);
	friend istream &operator >>(istream &in, HotelMstDTO &obj);

private:
	long hotel_id;
	string hotel_name;
	string address;
	string tel;
};

#endif /* HOTEL_DTO_H_ */
