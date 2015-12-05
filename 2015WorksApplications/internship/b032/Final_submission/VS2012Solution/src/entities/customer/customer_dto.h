#ifndef CUSTOMER_DTO_H_
#define CUSTOMER_DTO_H_

#include <string>
#include <iostream>
#include "entities/icsv_master_dto.h"
using namespace std;

class CustomerDTO: public ICsvMasterDTO {
public:
	CustomerDTO(long customer_id, string name, string gender,
			struct tm birthday, string nationality, string passport_no,
			string address, string email, string tel);
	long &get_customer_id();
	string &get_name();
	string &get_gender();
	struct tm &get_birthday();
	string &get_nationality();
	string &get_passport_no();
	string &get_address();
	string &get_email();
	string &get_tel();
	friend ostream &operator <<(ostream &out, CustomerDTO &obj);
	friend istream &operator >>(istream &in, CustomerDTO &obj);

private:
	long customer_id;
	string name;
	string gender;
	struct tm birthday;
	string nationality;
	string passport_no;
	string address;
	string email;
	string tel;
};

#endif /* CUSTOMER_DTO_H_ */
