
/** Subobject Date source file*/

#include "date.h"

/** no arguments constructor */
Date::Date(){
	date_[0] = 1;
	date_[1] = 1;
	date_[2] = 1970;
}

/** arguments constructor */
Date::Date(int r, int m, int d){
	date_[0] = d;
	date_[1] = m;
	date_[2] = r;
}

/** copy constructor */
Date::Date(const Date & date){
	date_[0] = date.date_[0];
	date_[1] = date.date_[1];
	date_[2] = date.date_[2];
}

/** operator "=" */
Date & Date:: operator=( const Date &date){

	if( this != &date ){
		date_[0] = date.date_[0];
		date_[1] = date.date_[1];
		date_[2] = date.date_[2];
	}
	return *this;
}

/** operator "<" */
bool Date::operator<(Date &date){

	pair<array<int, array_size>::iterator,array<int, array_size>::iterator> pair_not_equal;
	pair_not_equal = mismatch(date_.begin(), date_.end(), date.date_.begin());
	if(*pair_not_equal.first < *pair_not_equal.second)
		return true;
	else
		return false;
}

/** friend method for operator "<<" */
ostream & operator<<(std::ostream & os, const Date & date){
	os << date.date_[0]<<"."<<date.date_[1]<<"."<<date.date_[2]<<endl;
	return os;
}

/** virtual method for write date to file */
void Date::write_date(ofstream& file) {
	for(auto n: date_)
		file<<n<<",";
	file<<endl;
	if(!file)
		throw WriteFileError ("WRITE ERROR");

}

/** virtual method for read date from file */
void Date::read_date(ifstream& file) {
	string read_temp;
	getline(file, read_temp);
	if(!file)
		throw ReadFileError ("READ ERROR");
	for(size_t i =0; i < array_size; ++i)
		date_[i] = stoi(find_word(read_temp, i+1));
}
