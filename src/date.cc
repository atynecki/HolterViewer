
/** Subobject Date source file*/

#include "date.h"

/** no arguments constructor */
Date::Date(): day_(1), month_(1), year_(1970){ }

/** arguments constructor */
Date::Date(int r, int m, int d): day_(d), month_(m), year_(r){ }

/** copy constructor */
Date::Date(const Date & date){

	day_ = date.day_;
	month_ = date.month_;
	year_ = date.year_;
}

/** operator "=" */
Date & Date:: operator=( const Date &date){

	if( this != &date ){
		day_ = date.day_;
		month_ = date.month_;
		year_ = date.year_;
	}
	return *this;
}

/** operator "<" */
bool Date::operator<(const Date &date)const{

	if (year_ < date.year_)
		return true;
	else if (year_ > date.year_)
		return false;
	else if (year_ == date.year_){
		if (month_ < date.month_)
			return true;
		else if (month_ > date.month_)
			return false;
		else if (month_ == date.month_){
			if (day_ < date.day_)
				return true;
			else if (day_ > date.day_)
				return false;
			else if (day_ == date.day_)
				return false;
		}
	}
}

/** friend method for operator "<<" */
ostream & operator<<(std::ostream & os, const Date & date){

	os << date.day_<<"."<<date.month_<<"."<<date.year_<<endl;
	return os;
}

/** virtual method for write date to file */
void Date::write_date(ofstream file) {
	file<<day_<<","<<month_<<","<<year_<<endl;
	if(!file)
		throw WriteFileError ("WRITE ERROR");

}

/** virtual method for read date from file */
void Date::read_date(ifstream file) {
	file>>day_>>month_>>year_;
	if(!file) { }
		throw ReadFileError ("READ ERROR");
}
