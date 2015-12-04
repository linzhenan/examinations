#include "room_type.h"
#include <string>
#include <stdexcept>
using namespace std;

string room_type_to_string(RoomType type) {
	switch (type) {
	case SINGLE:
		return "SINGLE";
	case SEMIDOUBLE:
		return "SEMIDOUBLE";
	case DOUBLE:
		return "DOUBLE";
	default:
		return "";
	}
}

RoomType room_type_value_of_string(string src) {
	// convert the string, src, in its upper case
	for (string::iterator it = src.begin(); it != src.end(); it++) {
		*it = toupper(*it);
	}

	if (src == "DOUBLE") {
		return DOUBLE;
	}

	if (src == "SEMIDOUBLE") {
		return SEMIDOUBLE;
	}

	if (src == "SINGLE") {
		return SINGLE;
	}

	throw invalid_argument("Unknown Room Type : " + src);
}

