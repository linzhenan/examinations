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

static const string kInfoSelectRole =
	"\nSelect the user role: \n"
	"0. Return \n"
	"1. Customer \n"
	"2. Receptionist \n"
	"3. Waiter \n"
	"4. HR \n"
	"5. Sales Manager \n"
	"6. Hotel Manager \n"
	"7. Company Manager \n";
static const string kInfoSelectHotel =
	"\nSelect the hotel: \n";
static const string kInfoSelectRoom =
	"\nSelect the room: \n";
static const string kInfoReturnOption =
	"0. Return \n";

static const string kInfoInputPrompt =
	"Choose: ";
static const string kInfoInputCustomerName =
	"\nInput your name: ";

#endif /* MESSAGES_H_ */
