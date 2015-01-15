
/** Subobject Recorder source file */

#include "recorder.h"

/** no arguments constructor */
Recorder::Recorder(): serial_number_(0), sampling_(0) { }

/** arguments constructor */
Recorder::Recorder(string producer, string model, int serial_num, double samp): producer_(producer), model_(model), serial_number_(serial_num), sampling_(samp) { }

/** no arguments constructor */
RecorderEKG::RecorderEKG(): Recorder(), channel_number_(0) { }

/** arguments constructor */
RecorderEKG::RecorderEKG(int channel_number, int serial_num, double samp, string producer, string model): Recorder(producer,model, serial_num, samp){
	channel_number_ = channel_number;
}

/** copy constructor */
RecorderEKG::RecorderEKG(const RecorderEKG & recorder){

	producer_ =recorder.producer_;
	model_ = recorder.model_;
	serial_number_=recorder.serial_number_;
	sampling_ = recorder.sampling_;
	channel_number_ = recorder.channel_number_;
}

/** operator "=" */
RecorderEKG & RecorderEKG::operator=(const RecorderEKG &recorder){

	if( this != &recorder ){
		producer_ =recorder.producer_;
		model_ = recorder.model_;
		serial_number_=recorder.serial_number_;
		sampling_ = recorder.sampling_;
		channel_number_ = recorder.channel_number_;
	}
	return *this;
}

/** friend method for operator "<<" */
ostream & operator<<(std::ostream & os, const RecorderEKG & recorder){

	os << "Producer: " << recorder.producer_<<endl;
	os << "Model: "<< recorder.model_<<endl;
	os << "Serial number: "<< recorder.serial_number_<<endl;
	os << "Sampling: "<< recorder.sampling_<<endl;
	os << "Channel number: "<< recorder.channel_number_<<endl;

	return os;
}

/** virtual method for write date to file */
void RecorderEKG::write_date(ofstream& file) {
	file<<producer_<<","<<model_<<","<<serial_number_<<","<<sampling_<<","<<channel_number_<<endl;
	if(!file)
		throw WriteFileError ("WRITE ERROR");
}

/** virtual method for read date from file */
void RecorderEKG::read_date(ifstream& file) {
	string read_temp;
	getline(file, read_temp);
	if(!file)
		throw ReadFileError ("READ ERROR");

	producer_ = find_word(read_temp, 1);
	model_ = find_word(read_temp, 2);
	serial_number_ = atoi(find_word(read_temp, 3).c_str());
	sampling_ = atoi(find_word(read_temp, 4).c_str());
	channel_number_ = atoi(find_word(read_temp, 5).c_str());
}

/** no arguments constructor */
RecorderABPM::RecorderABPM(): Recorder() { }

/** arguments constructor */
RecorderABPM::RecorderABPM(string unit, int serial_num, double samp, string producer, string model): Recorder(producer,model, serial_num, samp){
	unit_ = unit;
}

/** copy constructor */
RecorderABPM::RecorderABPM(const RecorderABPM & recorder){

	producer_ =recorder.producer_;
	model_ = recorder.model_;
	serial_number_=recorder.serial_number_;
	sampling_ = recorder.sampling_;
	unit_ = recorder.unit_;
}

/** operator "=" */
RecorderABPM & RecorderABPM::operator=(const RecorderABPM &recorder){

	if( this != &recorder ){
		producer_ =recorder.producer_;
		model_ = recorder.model_;
		serial_number_=recorder.serial_number_;
		sampling_ = recorder.sampling_;
		unit_ = recorder.unit_;;
	}
	return *this;
}

/** friend method for operator "<<" */
ostream & operator<<(std::ostream & os, const RecorderABPM & recorder){

	os << "Producer: " << recorder.producer_<<endl;
	os << "Model: "<< recorder.model_<<endl;
	os << "Serial number: "<< recorder.serial_number_<<endl;
	os << "Sampling: "<< recorder.sampling_<<endl;
	os << "Unit: "<< recorder.unit_<<endl;

	return os;
}

/** virtual method for write date to file */
void RecorderABPM::write_date(ofstream& file) {
	file<<producer_<<","<<model_<<","<<serial_number_<<","<<sampling_<<","<<unit_<<endl;
	if(!file)
		throw WriteFileError ("WRITE ERROR");
}

/** virtual method for read date from file */
void RecorderABPM::read_date(ifstream& file) {
	string read_temp;
	getline(file, read_temp);
	if(!file)
		throw ReadFileError ("READ ERROR");

	producer_ = find_word(read_temp, 1);
	model_ = find_word(read_temp, 2);
	serial_number_ = atoi(find_word(read_temp, 3).c_str());
	sampling_ = atoi(find_word(read_temp, 4).c_str());
	unit_ =find_word(read_temp, 5);
}
