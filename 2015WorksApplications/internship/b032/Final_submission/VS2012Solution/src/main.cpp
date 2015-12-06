#include<iostream>
#include<fstream>
#include <sstream>

#include "constants/constants.h"
#include "csv_parser/csv_context.h"

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
static void input_customer_name()
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
			int discount;
			string discount_str = "0";
			string price_str = ptr_csv_room->context[atoi(ptr_csv_room_status->context[i][ROOM_STATUS_MST_ROOM_TYPE_ID].c_str()) - 1][ROOM_MST_PRICE];
			int price = atoi(price_str.c_str());

			if (curr_hotel_id != atoi(ptr_csv_room_status->context[i][ROOM_STATUS_MST_HOTEL_ID].c_str()))
			{
				prices.push_back(0);
				continue;
			}
			if (ptr_csv_room_status->context[i][ROOM_STATUS_MST_ROOM_STATUS] != "available")
			{
				prices.push_back(0);
				continue;
			}
			for (int j = 0; j < ptr_csv_discount->context.size(); j++)
			{
				string str;
				stringstream stream;
				stream << curr_hotel_id;
				stream >> str;
				if (ptr_csv_discount->context[j][DISCOUNT_MST_HOTEL_ID] == str &&
					ptr_csv_discount->context[j][DISCOUNT_MST_ROOM_TYPE_ID] == ptr_csv_room_status->context[i][ROOM_STATUS_MST_ROOM_TYPE_ID])
					discount_str = ptr_csv_discount->context[j][DISCOUNT_MST_DISCOUNT].c_str();
			}
			cout <<
				ptr_csv_room_status->context[i][ROOM_STATUS_MST_ROOM_STATUS_ID] + ". " +
				ptr_csv_room->context[atoi(ptr_csv_room_status->context[i][ROOM_STATUS_MST_ROOM_TYPE_ID].c_str()) - 1][ROOM_MST_TYPE];
			if (discount_str != "0")
			{
				discount = atoi(discount_str.c_str());
				price = (int)(price * 1.0 * (100 - discount) / 100);
				stringstream stream;
				stream << price;
				stream >> price_str;
				cout << " " + price_str + kInfoPriceUnit;
				cout << " (" + discount_str + "% OFF!)\n";
			}
			else
			{
				stringstream stream;
				stream << price;
				stream >> price_str;
				cout << " " + price_str + kInfoPriceUnit + "\n";
			}
			prices.push_back(price);
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
		cout << kInfoSelectOption;
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
	int options_id = 0;
	input_customer_name();
	do
	{
		cout << kInfoCustomerOptions;
		cout << kInfoInputPrompt;
		cin >> options_id;
		switch (options_id)
		{
		case 1: select_hotel(); customer_book_room(); break;
		case 2: customer_see_order(); break;
		}
	}
	while (options_id != RETURN);
}

static void reciptionist_check_rooms()
{
	int selected_room_id = 0;

	do 
	{
		load();
		int cnt = 0;
		cout << kInfoSelectRoom;
		cout << kInfoReturnOption;

		for (int i = 0; i < ptr_csv_room_status->context.size(); i++)
		{
			if (curr_hotel_id != atoi(ptr_csv_room_status->context[i][ROOM_STATUS_MST_HOTEL_ID].c_str()))
				continue;

			cout <<
				ptr_csv_room_status->context[i][ROOM_STATUS_MST_ROOM_STATUS_ID] + ". " +
				ptr_csv_room->context[atoi(ptr_csv_room_status->context[i][ROOM_STATUS_MST_ROOM_TYPE_ID].c_str()) - 1][ROOM_MST_TYPE] + ", " +
				ptr_csv_room_status->context[i][ROOM_STATUS_MST_ROOM_STATUS];
			if (ptr_csv_room_status->context[i][ROOM_STATUS_MST_CUSTOMER_NAME] != "\"\"" &&
				ptr_csv_room_status->context[i][ROOM_STATUS_MST_CUSTOMER_NAME] != "")
				cout << ", " +
				ptr_csv_room_status->context[i][ROOM_STATUS_MST_CUSTOMER_NAME] + ", " +
				ptr_csv_room_status->context[i][ROOM_STATUS_MST_FEE] + kInfoPriceUnit + "\n";
			else
				cout << "\n";
		}
		cout << kInfoInputPrompt;
		cin >> selected_room_id;
	}
	while (selected_room_id != RETURN);
}
static void reciptionist_check_in()
{
	int selected_room_id = 0;

	input_customer_name();

	do 
	{
		load();
		int cnt = 0;
		cout << kInfoSelectRoom;
		cout << kInfoReturnOption;

		for (int i = 0; i < ptr_csv_room_status->context.size(); i++)
		{
			if (curr_hotel_id != atoi(ptr_csv_room_status->context[i][ROOM_STATUS_MST_HOTEL_ID].c_str()))
				continue;
			if (ptr_csv_room_status->context[i][ROOM_STATUS_MST_CUSTOMER_NAME] != curr_customer_name &&
				ptr_csv_room_status->context[i][ROOM_STATUS_MST_ROOM_STATUS] != "available")
				continue;
			cout <<
				ptr_csv_room_status->context[i][ROOM_STATUS_MST_ROOM_STATUS_ID] + ". " +
				ptr_csv_room->context[atoi(ptr_csv_room_status->context[i][ROOM_STATUS_MST_ROOM_TYPE_ID].c_str()) - 1][ROOM_MST_TYPE] + ", " +
				ptr_csv_room_status->context[i][ROOM_STATUS_MST_ROOM_STATUS];
			if (ptr_csv_room_status->context[i][ROOM_STATUS_MST_CUSTOMER_NAME] != "\"\"" &&
				ptr_csv_room_status->context[i][ROOM_STATUS_MST_CUSTOMER_NAME] != "")
				cout << ", " +
				ptr_csv_room_status->context[i][ROOM_STATUS_MST_CUSTOMER_NAME] + ", " +
				ptr_csv_room_status->context[i][ROOM_STATUS_MST_FEE] + kInfoPriceUnit + "\n";
			else
				cout << "\n";
		}
		cout << kInfoInputPrompt;
		cin >> selected_room_id;
		if (selected_room_id != RETURN && ptr_csv_room_status->context[selected_room_id - 1][ROOM_STATUS_MST_CUSTOMER_NAME] == curr_customer_name)
		{
			ptr_csv_room_status->context[selected_room_id - 1][ROOM_STATUS_MST_ROOM_STATUS] = "inused";
			cout << "Check-in successfully.\n";
			submit();
		}
	}
	while (selected_room_id != RETURN);
}
static void reciptionist_check_out()
{
	int selected_room_id = 0;

	input_customer_name();

	do 
	{
		load();
		int cnt = 0;
		cout << kInfoSelectRoom;
		cout << kInfoReturnOption;

		for (int i = 0; i < ptr_csv_room_status->context.size(); i++)
		{
			if (curr_hotel_id != atoi(ptr_csv_room_status->context[i][ROOM_STATUS_MST_HOTEL_ID].c_str()))
				continue;
			if (ptr_csv_room_status->context[i][ROOM_STATUS_MST_CUSTOMER_NAME] != curr_customer_name)
				continue;
			cout <<
				ptr_csv_room_status->context[i][ROOM_STATUS_MST_ROOM_STATUS_ID] + ". " +
				ptr_csv_room->context[atoi(ptr_csv_room_status->context[i][ROOM_STATUS_MST_ROOM_TYPE_ID].c_str()) - 1][ROOM_MST_TYPE] + ", " +
				ptr_csv_room_status->context[i][ROOM_STATUS_MST_ROOM_STATUS];
			if (ptr_csv_room_status->context[i][ROOM_STATUS_MST_CUSTOMER_NAME] != "\"\"" &&
				ptr_csv_room_status->context[i][ROOM_STATUS_MST_CUSTOMER_NAME] != "")
				cout << ", " +
				ptr_csv_room_status->context[i][ROOM_STATUS_MST_CUSTOMER_NAME] + ", " +
				ptr_csv_room_status->context[i][ROOM_STATUS_MST_FEE] + kInfoPriceUnit + "\n";
			else
				cout << "\n";
		}
		cout << kInfoInputPrompt;
		cin >> selected_room_id;
		if (selected_room_id != RETURN && ptr_csv_room_status->context[selected_room_id - 1][ROOM_STATUS_MST_CUSTOMER_NAME] == curr_customer_name)
		{
			ptr_csv_room_status->context[selected_room_id - 1][ROOM_STATUS_MST_CUSTOMER_NAME] = "";
			ptr_csv_room_status->context[selected_room_id - 1][ROOM_STATUS_MST_FEE] = "0";
			ptr_csv_room_status->context[selected_room_id - 1][ROOM_STATUS_MST_ROOM_STATUS] = "available";
			cout << "Check-out successfully.\n";
			submit();
		}
	}
	while (selected_room_id != RETURN);
}
static void reciptionist_options()
{
	int options_id = 0;
	select_hotel();
	do
	{
		cout << kInfoReciptionistOptions;
		cout << kInfoInputPrompt;
		cin >> options_id;
		switch (options_id)
		{
		case 1: reciptionist_check_rooms(); break;
		case 2: reciptionist_check_in(); break;
		case 3: reciptionist_check_out(); break;
		}
	}
	while (options_id != RETURN);
}

static void salesmanager_check_sales()
{
	int option_id = 0;
	do
	{
		load();
		for (int i = 0; i < ptr_csv_room->context.size(); i++)
		{
			cout << ptr_csv_room->context[i][ROOM_MST_TYPE] + " : ";
			int booked = 0; string booked_str;
			int inused = 0; string inused_str;
			int available = 0; string available_str;
			int unavailable = 0; string unavailable_str;
			int total = 0; string total_str;
			double vacancy = 0; string vacancy_str;

			for (int j = 0; j < ptr_csv_room_status->context.size(); j++)
			{
				if (atoi(ptr_csv_room_status->context[j][ROOM_STATUS_MST_HOTEL_ID].c_str()) != curr_hotel_id)
					continue;
				if (ptr_csv_room_status->context[j][ROOM_STATUS_MST_ROOM_TYPE_ID] != ptr_csv_room->context[i][ROOM_MST_ID])
					continue;
				if (ptr_csv_room_status->context[j][ROOM_STATUS_MST_ROOM_STATUS] == "booked")
					booked++;
				else if (ptr_csv_room_status->context[j][ROOM_STATUS_MST_ROOM_STATUS] == "inused")
					inused++;
				else if (ptr_csv_room_status->context[j][ROOM_STATUS_MST_ROOM_STATUS] == "available")
					available++;
				else if (ptr_csv_room_status->context[j][ROOM_STATUS_MST_ROOM_STATUS] == "unavailable")
					unavailable++;
				total++;
			}
			vacancy = available * 1.0 / total * 100;
			stringstream stream;
			stream.clear(); stream << booked; stream >> booked_str;
			stream.clear(); stream << inused; stream >> inused_str;
			stream.clear(); stream << available; stream >> available_str;
			stream.clear(); stream << unavailable; stream >> unavailable_str;
			stream.clear(); stream << vacancy; stream >> vacancy_str;
			stream.clear(); stream << total; stream >> total_str;
			cout << "booked " + booked_str + ", ";
			cout << "inused " + inused_str + ", ";
			cout << "available " + available_str + ", ";
			cout << "unavailable " + unavailable_str + ", ";
			cout << "total " + total_str + ", ";
			cout << "vacancy " + vacancy_str + "%\n";
		}
		cout << kInfoInputPrompt;
		cin >> option_id;
	}
	while (option_id != RETURN);
	
}
static void salesmanager_make_discount()
{
	int option_id = 0;
	do
	{
		cout << kInfoSelectRoomType;
		cout << kInfoReturnOption;
		for (int i = 0; i < ptr_csv_discount->context.size(); i++)
		{
			if (atoi(ptr_csv_discount->context[i][DISCOUNT_MST_HOTEL_ID].c_str()) != curr_hotel_id)
				continue;
			cout << ptr_csv_discount->context[i][DISCOUNT_MST_ID] + ". ";

			int room_type_id = atoi(ptr_csv_discount->context[i][DISCOUNT_MST_ROOM_TYPE_ID].c_str());
			string room_type;
			for (int j = 0; j < ptr_csv_room->context.size(); j++)
				if (ptr_csv_room->context[j][ROOM_MST_ID] == ptr_csv_discount->context[i][DISCOUNT_MST_ROOM_TYPE_ID])
					cout << ptr_csv_room->context[j][ROOM_MST_TYPE] + ": ";
			cout << ptr_csv_discount->context[i][DISCOUNT_MST_DISCOUNT] + "%\n";
		}
		cout << kInfoInputPrompt;
		cin >> option_id;

		if (option_id != RETURN)
		{
			string curr_discount;
			cout << kInfoInputDiscount;
			cin >> curr_discount;

			ptr_csv_discount->context[option_id - 1][DISCOUNT_MST_DISCOUNT] = curr_discount;
			submit();
			cout << "Successfully\n";
		}
	}
	while (option_id != RETURN);
}
static void salesmanager_options()
{
	int options_id = 0;
	select_hotel();
	do
	{
		cout << kInfoSalesManagerOptions;
		cout << kInfoInputPrompt;
		cin >> options_id;
		switch (options_id)
		{
		case 1: salesmanager_check_sales(); break;
		case 2: salesmanager_make_discount(); break;
		}
	}
	while (options_id != RETURN);
}

int main(int argc, char** argv)
{
	load();

	cout <<kInfoWelcome;
	do 
	{
		cout << kInfoRoleOptions;
		cout << kInfoInputPrompt;
		cin >> curr_user_id;
		switch (curr_user_id)
		{
		case CUSTOMER: customer_options(); break;
		case RECEPTIONIST: reciptionist_options(); break;
		case WAITER: break;
		case HR: break;
		case SALES_MANAGER: salesmanager_options(); break;
		case HOTEL_MANAGER: break;
		case COMPANY_MANAGER: break;
		default: break;
		}
	}
	while (curr_user_id != RETURN);

	submit();
}