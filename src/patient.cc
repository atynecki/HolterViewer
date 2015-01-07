
/** Subobject Patient source file */

#include "patient.h"

/** no arguments constructor */
Person::Person(){ }

/** arguments constructor */
Person::Person(string name, string last_name, string pesel): name_(name), last_name_(last_name), pesel_(pesel){ }

/** no arguments constructor */
Patient::Patient(): Person(), age_(0), growth_(0), weight_(0), id_number_(0) { };

/** arguments constructor */
Patient::Patient(int age, int growth, int weight, string name, string last_name, string pesel): Person (name, last_name, pesel){
	age_ = age;
	growth_ = growth;
	weight_ = weight;
	id_number_= 0;
}

/** copy constructor */
Patient::Patient (const Patient &patient){
	name_ = patient.name_;
	last_name_ = patient.last_name_;
	pesel_ = patient.pesel_;
	age_ = patient.age_;
	growth_ = patient.growth_;
	weight_ = patient.weight_;
	id_number_ = patient.id_number_;
}

/** operator "=" */
Patient & Patient::operator=(const Patient &patient ){

	if( this != &patient ){
		name_ = patient.name_;
		last_name_ = patient.last_name_;
		pesel_ = patient.pesel_;
		age_ = patient.age_;
		growth_ = patient.growth_;
		weight_ = patient.weight_;
		id_number_ = patient.id_number_;
	}
	return *this;
}

/** friend method for operator "<<" */
ostream & operator<<(std::ostream & os, const Patient & patient){

	os << "Name: "<< patient.name_<<endl;
	os << "Last name: "<< patient.last_name_<<endl;
	os << "Age: "<< patient.age_<<endl;
	os << "ID: "<< patient.id_number_ <<endl;
	return os;
}

int Patient::set_id_number(){

	id_number_ = age_*1000000 + growth_*1000 + weight_;

	return id_number_;
}

/** virtual method for write date to file */
void Patient::write_date(ofstream& file) {
	file<<name_<<","<<last_name_<<","<<pesel_<<","<<age_<<","<<growth_<<","<<weight_<<","<<id_number_<<endl;
	if(!file)
		throw WriteFileError ("WRITE ERROR");
}

/** virtual method for read date from file */
void Patient::read_date(ifstream& file) {
	string read_temp;
	getline(file, read_temp);
	if(!file)
		throw ReadFileError ("READ ERROR");

	name_ = find_word(read_temp, 1);
	last_name_ = find_word(read_temp, 2);
	pesel_ = find_word(read_temp, 3);
	age_ = atoi(find_word(read_temp, 4).c_str());
	growth_ = atoi(find_word(read_temp, 5).c_str());
	weight_ = atoi(find_word(read_temp, 6).c_str());
	id_number_ = atoi(find_word(read_temp, 7).c_str());
}
