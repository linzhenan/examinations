#include<iostream>
#include<fstream>
#include <sstream>

#include "constants/constants.h"

#include "csv_parser/csv_context.h"

#include "entities/icsv_master_dto.h"
#include "entities/abstract_dto_reader.h"
#include "entities/customer/customer_dto.h"
#include "entities/customer/customer_dto_reader.h"
#include "entities/hotel/hotel_mst_dto.h"
#include "entities/hotel/hotel_mst_dto_reader.h"
#include "entities/region/region_mst_dto.h"
#include "entities/region/region_mst_dto_reader.h"
#include "entities/room/room_type.h"
#include "entities/staff/position_type.h"
#include "entities/staff/rank_type.h"
#include "entities/staff/staff_dto.h"
#include "entities/staff/staff_dto_reader.h"

using namespace std;

int curr_func_id = 0;
int curr_hotel_id = 0;
int curr_room_id = 0;
int curr_user_id = 0;
string curr_customer_name = "anonymous";

CSVContext *ptr_csv_hotel;
CSVContext *ptr_csv_room_status;
CSVContext *ptr_csv_room;
CSVContext *ptr_csv_discount;

void book_room()
{
	int id = 0;

	do 
	{
		int cnt = 0;

		cout << kInfoSelectRoom;
		for (int i = 0; i < ptr_csv_room_status->context.size(); i++)
		{
			string discount = "0";
			if (curr_hotel_id != atoi(ptr_csv_room_status->context[i][ROOM_STATUS_MST_HOTEL_ID].c_str()))
				continue;
			if (ptr_csv_room_status->context[i][ROOM_STATUS_MST_ROOM_STATUS] != "available")
				continue;
			for (int j = 0; j < ptr_csv_discount->context.size(); j++)
			{
				string str;
				stringstream stream;
				stream << curr_hotel_id;
				stream >> str;
				if (ptr_csv_discount->context[i][DISCOUNT_MST_HOTEL_ID] == str &&
					ptr_csv_discount->context[i][DISCOUNT_MST_ROOM_TYPE_ID] == ptr_csv_room_status->context[i][ROOM_STATUS_MST_ROOM_TYPE_ID])
					discount = ptr_csv_discount->context[i][DISCOUNT_MST_DISCOUNT].c_str();
			}
			cout <<
				ptr_csv_room_status->context[i][ROOM_STATUS_MST_ROOM_STATUS_ID] + ". " +
				ptr_csv_room->context[atoi(ptr_csv_room_status->context[i][ROOM_STATUS_MST_ROOM_TYPE_ID].c_str()) - 1][1];
			if (discount != "0")
				cout << " (" + discount + "% OFF!)\n";
			else
				cout << "\n";
			cnt++;
		}
		cout << "There are ";
		cout << cnt;
		cout << " rooms available.\n";
		cout << kInfoInputPrompt;
		cin >> id;
		if (id != RETURN)
		{
			ptr_csv_room_status->context[id - 1][ROOM_STATUS_MST_ROOM_STATUS] = "booked";
			ptr_csv_room_status->context[id - 1][ROOM_STATUS_MST_CUSTOMER_NAME] = curr_customer_name;
			cout << "Successfully.\n";
		}
	}
	while (id != RETURN);
}

void select_hotel()
{
	while (1)
	{
		cout << kInfoSelectHotel;
		cout << kInfoReturnOption;
		for (int i = 0; i < ptr_csv_hotel->context.size(); i++)
			cout << ptr_csv_hotel->context[i][HOTEL_ID] + ". " + ptr_csv_hotel->context[i][HOTEL_NAME] + "\n";
		cout << kInfoInputPrompt;
		cin >> curr_hotel_id;

		if (curr_hotel_id == RETURN)
		{
			return;
		}
		else if (0 < curr_hotel_id && curr_hotel_id <= ptr_csv_hotel->context.size())
		{
			switch (curr_hotel_id)
			{
			case CUSTOMER: book_room(); break;
			case RECEPTIONIST: break;
			case WAITER: break;
			case HR: break;
			case SALES_MANAGER: break;
			case HOTEL_MANAGER: break;
			case COMPANY_MANAGER: break;
			default: break;
			}
		}
	}
}

int main(int argc, char** argv)
{
	ptr_csv_hotel = new CSVContext("files/HOTEL_MST.csv");
	ptr_csv_room_status = new CSVContext("files/ROOM_STATUS_MST.csv");
	ptr_csv_room = new CSVContext("files/ROOM_MST.csv");
	ptr_csv_discount = new CSVContext("files/DISCOUNT_MST.csv");

	cout <<kInfoWelcome;
	do 
	{
		cout << kInfoSelectRole;
		cout << kInfoInputPrompt;
		cin >> curr_user_id;

		switch (curr_user_id)
		{
		case CUSTOMER:
			cout << kInfoInputCustomerName;
			cin >> curr_customer_name;
			select_hotel();
			break;
		case RECEPTIONIST: break;
		case WAITER: break;
		case HR: break;
		case SALES_MANAGER: break;
		case HOTEL_MANAGER: break;
		case COMPANY_MANAGER: break;
		default: break;
		}
	}
	while (curr_user_id != RETURN);

	ptr_csv_hotel->save();
	ptr_csv_room_status->save();
	ptr_csv_room->save();
	ptr_csv_discount->save();
}