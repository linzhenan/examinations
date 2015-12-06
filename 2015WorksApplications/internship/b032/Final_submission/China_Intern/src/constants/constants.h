#ifndef CONSTANTS_H_
#define CONSTANTS_H_

#include "messages.h"
#include "user_type.h"
#include "data_relationship.h"

#include <string>
using namespace std;

/** Directory name of CSV files for read */
static const string kDefaultCsvFolder = "files/";

/** Directory name of CSV files to write in */
static const string kDefaultCsvOutputFolder = "output/";

/** Default csv separator */
static const char kDefaultCsvSeparator = ',';

/** default csv quote char */
static const char kDefaultCsvQuotechar = '\"';

#define RETURN 0


#endif /* CONSTANTS_H_ */
