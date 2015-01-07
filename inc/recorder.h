
/** Subobject Recorder header file */
#ifndef RECORDER_H_
#define RECORDER_H_

#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include "error.h"
#include "app_service.h"

using namespace std;

class Recorder {
public:
	string producer_;
	string model_;
	int serial_number_;
	double sampling_;

	Recorder();
	Recorder(string producer, string model, int serial_num, double samp);

	virtual ~Recorder() { }

	virtual void write_date(ofstream& file) = 0;
	virtual void read_date(ifstream& file) = 0;

};

class RecorderEKG: public Recorder {
	int channel_number_;
public:
	RecorderEKG();
	RecorderEKG(int channel_number, int serial_num, double samp, string producer, string model);
	RecorderEKG(const RecorderEKG & recorder);

	RecorderEKG & operator=(const RecorderEKG &recorder);

	friend ostream & operator<<(std::ostream & os, const RecorderEKG & recorder);

	virtual void write_date(ofstream& file);
	virtual void read_date(ifstream& file);
};

class RecorderABPM: public Recorder {
	string unit_;
public:
	RecorderABPM();
	RecorderABPM(string unit_, int serial_num, double samp, string producer, string model);
	RecorderABPM(const RecorderABPM & recorder);

	RecorderABPM & operator=(const RecorderABPM &recorder);

	friend ostream & operator<<(std::ostream & os, const RecorderABPM & recorder);

	virtual void write_date(ofstream& file);
	virtual void read_date(ifstream& file);
};
#endif /* RECORDER_H_ */
