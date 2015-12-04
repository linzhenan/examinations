#include "customer_dto.h"
#include "util/utilities.h"
#include <string>
using namespace std;

CustomerDTO::CustomerDTO(long customer_id, string name, string gender,
		struct tm birthday, string nationality, string passport_no,
		string address, string email, string tel) {
	this->customer_id = customer_id;
	this->name = name;
	this->gender = gender;
	this->birthday = birthday;
	this->nationality = nationality;
	this->passport_no = passport_no;
	this->address = address;
	this->email = email;
	this->tel = tel;
}

long &CustomerDTO::get_customer_id() {
	return customer_id;
}

string &CustomerDTO::get_name() {
	return name;
}

string &CustomerDTO::get_gender() {
	return gender;
}

struct tm &CustomerDTO::get_birthday() {
	return birthday;
}

string &CustomerDTO::get_nationality() {
	return nationality;
}

string &CustomerDTO::get_passport_no() {
	return passport_no;
}

string &CustomerDTO::get_address() {
	return address;
}

string &CustomerDTO::get_email() {
	return email;
}

string &CustomerDTO::get_tel() {
	return tel;
}

ostream &operator <<(ostream &out, CustomerDTO &obj) {
	out << obj.customer_id << " " << obj.name << " " << obj.gender << " "
			<< Utilities::format_date(obj.birthday) << " " << obj.nationality << " "
			<< obj.passport_no << " " << obj.address << " " << obj.email << " " << obj.tel;
	return out;
}

istream &operator >>(istream &in, CustomerDTO &obj) {
	in >> obj.customer_id >> obj.name >> obj.gender;
	string birthday;
	in >> birthday;
	obj.birthday = Utilities::parse_date_str(birthday);
	in >> obj.nationality >> obj.passport_no >> obj.address >> obj.email
			>> obj.tel;
	return in;
}

