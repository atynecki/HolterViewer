
/** Head class HOLTER header file*/

#ifndef HOLTER_H_
#define HOLTER_H_

#include <memory>

#include "patient.h"
#include "recorder.h"
#include "ecg_signal.h"
#include "date.h"

using namespace std;

class Holter {
protected:
	Holter (Holter &holter);
	Holter & operator=(Holter &holter);
public:
	Date *test_date_;
	unique_ptr <Patient> patients_;
	Signal<int, int> *signal_;

	Holter();
	Holter(const Date &date, const Patient &patient, const Signal<int, int> &signal);

	virtual ~Holter();

	virtual void show_date () = 0;
	virtual void write_date (ofstream& file) = 0;
	virtual void read_date (ifstream& file) = 0;

};

class HolterEKG: public Holter {
	RecorderEKG new_recorder_;
	int signal_number_;
public:
	HolterEKG();
	HolterEKG(const Date &date, const Patient &patient, const Signal<int, int>* signal, const RecorderEKG recorder, int signal_num);
	HolterEKG(HolterEKG &holter);
	HolterEKG & operator=(HolterEKG &holter);

	virtual ~HolterEKG();

	virtual void show_date ();
	virtual void write_date (ofstream& file);
	virtual void read_date (ifstream& file);
};

class HolterABPM: public Holter {
	RecorderABPM new_recorder_;
	string mode_;
public:
	HolterABPM();
	HolterABPM(const Date &date, const Patient &patient, const Signal<int, int> &signal, const RecorderABPM recorder, string mode);
	HolterABPM(HolterABPM &holter);
	HolterABPM & operator=(HolterABPM &holter);

	virtual ~HolterABPM();

	virtual void show_date ();
	virtual void write_date (ofstream& file);
	virtual void read_date (ifstream& file);
};

#endif /* HOLTER_H_ */
