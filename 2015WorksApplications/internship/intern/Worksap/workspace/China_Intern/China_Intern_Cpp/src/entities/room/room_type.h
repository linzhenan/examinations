#ifndef ROOM_TYPE_H_
#define ROOM_TYPE_H_

#include <string>
using namespace std;

enum RoomType {
	SINGLE, SEMIDOUBLE, DOUBLE
};

string room_type_to_string(RoomType type);
RoomType room_type_value_of_string(string src);

#endif /* ROOM_TYPE_H_ */
