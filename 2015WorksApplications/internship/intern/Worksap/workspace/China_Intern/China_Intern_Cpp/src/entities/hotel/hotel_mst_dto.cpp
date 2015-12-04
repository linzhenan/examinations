#include "hotel_mst_dto.h"
#include <iostream>
using namespace std;

HotelMstDTO::HotelMstDTO(long hotel_id, string hotel_name, string address,
		string tel, int stars) {
	this->hotel_id = hotel_id;
	this->hotel_name = hotel_name;
	this->address = address;
	this->tel = tel;
}

long &HotelMstDTO::get_hotel_id() {
	return hotel_id;
}

string &HotelMstDTO::get_hotel_name() {
	return hotel_name;
}

string &HotelMstDTO::get_address() {
	return address;
}

string &HotelMstDTO::get_tel() {
	return tel;
}

ostream &operator <<(ostream &out, HotelMstDTO &obj) {
	out << obj.hotel_id << " " << obj.hotel_name << " " << obj.address << " "
			<< obj.tel;
	return out;
}

istream &operator >>(istream &in, HotelMstDTO &obj) {
	in >> obj.hotel_id >> obj.hotel_name >> obj.address >> obj.tel;
	return in;
}

