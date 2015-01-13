
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
	Date test_date_;
	Patient patients_;
	vector <Signal<int, int>> signal_;

	Holter();
	Holter(const Date &date, const Patient &patient, const Signal<int, int> &signal);

	virtual ~Holter();

	virtual void show_date () = 0;
	virtual void write_date (string file_name) = 0;
	virtual void read_date (string file_name) = 0;

};

class HolterEKG: public Holter {
	unsigned signal_number_;
public:
	RecorderEKG new_recorder_;
	HolterEKG();
	HolterEKG(const Date &date, const Patient &patient, const Signal<int, int>* signal, const RecorderEKG recorder, int signal_num);
	HolterEKG(HolterEKG &holter);
	HolterEKG & operator=(HolterEKG &holter);

	virtual ~HolterEKG();

	inline unsigned get_signal_num () {return signal_number_;};
	virtual void show_date ();
	virtual void write_date (string file_name);
	virtual void read_date (string file_name);
};

class HolterABPM: public Holter {
	string mode_;
public:
	RecorderABPM new_recorder_;
	HolterABPM();
	HolterABPM(const Date &date, const Patient &patient, const Signal<int, int> &signal, const RecorderABPM recorder, string mode);
	HolterABPM(HolterABPM &holter);
	HolterABPM & operator=(HolterABPM &holter);

	virtual ~HolterABPM();

	virtual void show_date ();
	virtual void write_date (string file_name);
	virtual void read_date (string file_name);
};

#endif /* HOLTER_H_ */
