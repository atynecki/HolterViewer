
/** Subobject Date header file*/

#ifndef DATE_H_
#define DATE_H_

#include <iostream>
#include <fstream>

using namespace std;

class Date {
	//przerobić na kontener
	int day_;
	int month_;
	int year_;
public:
	Date();
	Date(int r, int m, int d);
	Date(const Date & date);

	Date & operator=(const Date &date);
	bool operator<(const Date &date)const;

	friend ostream & operator<<(std::ostream & os, const Date & date);

	void write_date(ofstream file);
	void read_date(ifstream file);
};

#endif /* DATE_H_ */
