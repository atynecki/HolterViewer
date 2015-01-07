
/** Subobject Date header file*/

#ifndef DATE_H_
#define DATE_H_

#include <iostream>
#include <fstream>
#include <array>
#include <utility>

#include "error.h"
#include "app_service.h"

using namespace std;
const size_t array_size = 3;

class Date {
	array<int, array_size>date_;
public:
	Date();
	Date(int r, int m, int d);
	Date(const Date & date);

	Date & operator=(const Date &date);
	bool operator<(Date &date);

	friend ostream & operator<<(std::ostream & os, const Date & date);

	void write_date(ofstream& file);
	void read_date(ifstream& file);
};

#endif /* DATE_H_ */
