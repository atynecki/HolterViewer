
/** Subobject Patient header file */
#ifndef PATIENT_H_
#define PATIENT_H_

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class Person {
public:
	string name_;
	string last_name_;
	string pesel_;
	Person();
	Person(string name, string last_name, string pesel);
	virtual ~Person(){}

	virtual int set_id_number () = 0;

	virtual void write_date(ofstream file) = 0;
	virtual void read_date(ifstream file) = 0;
};

class Patient: public Person {
	int age_;
	int growth_;
	int weight_;
public:
	Patient();
	Patient(int age, int growth, int weight, string name, string last_name, string pesel);
	Patient (const Patient &patient);

	Patient & operator=(const Patient &patient);

	friend ostream & operator<<(std::ostream & os, const Patient & patient);

	virtual int set_id_number ();

	virtual void write_date(ofstream file);
	virtual void read_date(ifstream file);
};

#endif /* PATIENT_H_ */
