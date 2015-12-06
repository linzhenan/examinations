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

static void load()
{
	ptr_csv_hotel = new CSVContext("files/HOTEL_MST.csv");
	ptr_csv_room_status = new CSVContext("files/ROOM_STATUS_MST.csv");
	ptr_csv_room = new CSVContext("files/ROOM_MST.csv");
	ptr_csv_discount = new CSVContext("files/DISCOUNT_MST.csv");
}
static void submit()
{
	ptr_csv_hotel->save();
	ptr_csv_room_status->save();
	ptr_csv_room->save();
	ptr_csv_discount->save();
}

static void select_hotel()
{
	do
	{
		load();
		cout << kInfoSelectHotel;
		for (int i = 0; i < ptr_csv_hotel->context.size(); i++)
			cout << ptr_csv_hotel->context[i][HOTEL_MST_HOTEL_ID] + ". " + ptr_csv_hotel->context[i][HOTEL_MST_HOTEL_NAME] + "\n";
		cout << kInfoInputPrompt;
		cin >> curr_hotel_id;
	}
	while (curr_hotel_id < 0 || curr_hotel_id > ptr_csv_hotel->context.size());
}
static void input_name()
{
	cout << kInfoInputCustomerName;
	cin >> curr_customer_name;
}

static void customer_book_room()
{
	int selected_room_id = 0;

	do 
	{
		load();
		int cnt = 0;
		cout << kInfoSelectRoom;
		cout << kInfoReturnOption;
		vector<int> prices;
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
				if (ptr_csv_discount->context[j][DISCOUNT_MST_HOTEL_ID] == str &&
					ptr_csv_discount->context[j][DISCOUNT_MST_ROOM_TYPE_ID] == ptr_csv_room_status->context[i][ROOM_STATUS_MST_ROOM_TYPE_ID])
					discount = ptr_csv_discount->context[j][DISCOUNT_MST_DISCOUNT].c_str();
			}
			cout <<
				ptr_csv_room_status->context[i][ROOM_STATUS_MST_ROOM_STATUS_ID] + ". " +
				ptr_csv_room->context[atoi(ptr_csv_room_status->context[i][ROOM_STATUS_MST_ROOM_TYPE_ID].c_str()) - 1][ROOM_MST_TYPE];
			if (discount != "0")
			{
				int discount_percent = atoi(discount.c_str());
				int price = atoi(ptr_csv_room->context[atoi(ptr_csv_room_status->context[i][ROOM_STATUS_MST_ROOM_TYPE_ID].c_str()) - 1][ROOM_MST_PRICE].c_str());
				price = (int)(price * 1.0 * (100 - discount_percent) / 100);
				prices.push_back(price);
				cout << " " + price;
				cout << " (" + discount + "% OFF!)\n";
			}
			else
			{
				int price = atoi(ptr_csv_room->context[atoi(ptr_csv_room_status->context[i][ROOM_STATUS_MST_ROOM_TYPE_ID].c_str()) - 1][ROOM_MST_PRICE].c_str());
				prices.push_back(price);
				cout << " " + price;
				cout << "\n";
			}
			cnt++;
		}
		cout << "There are ";
		cout << cnt;
		cout << " rooms available.\n";
		cout << kInfoInputPrompt;
		cin >> selected_room_id;
		if (selected_room_id != RETURN)
		{
			ptr_csv_room_status->context[selected_room_id - 1][ROOM_STATUS_MST_CUSTOMER_NAME] = curr_customer_name;
			string price_str;
			stringstream stream;
			stream << prices[selected_room_id - 1];
			stream >> price_str;
			ptr_csv_room_status->context[selected_room_id - 1][ROOM_STATUS_MST_ROOM_STATUS] = "booked";
			ptr_csv_room_status->context[selected_room_id - 1][ROOM_STATUS_MST_FEE] = price_str;
			cout << "Successfully.\n";
			submit();
		}
	}
	while (selected_room_id != RETURN);
}
static void customer_see_order()
{
	int selected_order_id = 0;

	do 
	{
		load();
		cout << kInfoSelectOperation;
		cout << kInfoReturnOption;
		for (int i = 0; i < ptr_csv_room_status->context.size(); i++)
		{
			if (ptr_csv_room_status->context[i][ROOM_STATUS_MST_CUSTOMER_NAME] == curr_customer_name)
			{
				cout << ptr_csv_room_status->context[i][ROOM_STATUS_MST_ROOM_STATUS_ID] + ". ";
				for (int j = 0; j < ptr_csv_hotel->context.size(); j++)
					if (ptr_csv_room_status->context[i][ROOM_STATUS_MST_HOTEL_ID] ==
						ptr_csv_hotel->context[j][HOTEL_MST_HOTEL_ID])
					{
						cout << ptr_csv_hotel->context[j][HOTEL_MST_HOTEL_NAME] + ", ";
						break;
					}
				for (int j = 0; j < ptr_csv_room->context.size(); j++)
					if (ptr_csv_room_status->context[i][ROOM_STATUS_MST_ROOM_TYPE_ID] ==
						ptr_csv_room->context[j][ROOM_MST_ID])
					{
						cout << ptr_csv_room->context[j][ROOM_MST_TYPE] + ", ";
						break;
					}
				cout << ptr_csv_room_status->context[i][ROOM_STATUS_MST_FEE] + "\n";
			}
		}
		cout << kInfoInputPrompt;
		cin >> selected_order_id;
	}
	while (selected_order_id != RETURN);
}
static void customer_options()
{
	int customer_options_id = 0;
	input_name();
	do
	{
		cout << kInfoCustomerOptions;
		cout << kInfoInputPrompt;
		cin >> customer_options_id;
		switch (customer_options_id)
		{
		case 1: select_hotel(); customer_book_room(); break;
		case 2: customer_see_order(); break;
		}
	}
	while (customer_options_id != RETURN);
}

int main(int argc, char** argv)
{
	load();

	cout <<kInfoWelcome;
	do 
	{
		load();
		cout << kInfoRoleOptions;
		cout << kInfoInputPrompt;
		cin >> curr_user_id;
		switch (curr_user_id)
		{
		case CUSTOMER: customer_options(); break;
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

	submit();
}