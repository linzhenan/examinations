#ifndef MESSAGES_H_
#define MESSAGES_H_

#include <string>
using namespace std;

static const string kErrorCsvNotFound = "CSV File not found";
static const string kErrorReadCsv = "CSV Cannot be Read Correctly";
static const string kErrorCsvFileClose = "Error has occured when closing csv file";
static const string kErrorParseDate = "Parsing date string failed";
static const string kErrorWriteCsv = "Failed to Write Content as CSV File";

static const string kInfoWelcome =
	"Welcome to Hotel Sky :) \n";

static const string kInfoSelectUserRole = 
	"\nSelect the user role: \n";
static const string kInfoSelectHotel =
	"\nSelect the hotel: \n";
static const string kInfoSelectRoom =
	"\nSelect the room: \n";
static const string kInfoSelectOption =
	"\nSelect the option: \n";
static const string kInfoSelectOrder =
	"\nSelect the order: \n";
static const string kInfoSelectRoomType =
	"\nSelect the room type: \n";

static const string kInfoReturnOption =
	"0. Return \n";
static const string kInfoRoleOptions =
	kInfoSelectUserRole +
	kInfoReturnOption + 
	"1. Customer \n"
	"2. Receptionist \n"
	"3. Waiter (TBD)\n"
	"4. HR (TBD)\n"
	"5. Sales Manager \n"
	"6. Hotel Manager (TBD)\n"
	"7. Company Manager (TBD)\n";
static const string kInfoCustomerOptions =
	kInfoSelectOption +
	kInfoReturnOption +
	"1. Book room \n"
	"2. See order \n";

static const string kInfoReciptionistOptions =
	kInfoSelectOption +
	kInfoReturnOption +
	"1. Check rooms\n"
	"2. Check in\n"
	"3. Check out\n";
static const string kInfoSalesManagerOptions =
	kInfoSelectOption +
	kInfoReturnOption +
	"1. Check sales\n"
	"2. Make a discount\n";

static const string kInfoInputPrompt =
	"Choose: ";
static const string kInfoInputCustomerName =
	"\nInput your name: ";
static const string kInfoInputDiscount =
	"\nInput discount: ";

static const string kInfoPriceUnit =
	" dollars";

#endif /* MESSAGES_H_ */
