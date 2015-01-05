/*
 * rower.cc
 *
 *  Created on: 24 paź 2014
 *      Author: tynio
 */

/** Head class HOLTER source file*/

#include <iostream>
#include <string>
#include "holter.h"

using namespace std;

/** HOLTER CLASS */
/** no arguments constructor */
Holter::Holter(){

	test_date_ = nullptr;
	signal_ = nullptr;
	patients_ = nullptr;
}

/** arguments (all) constructor */
Holter::Holter(const Date &date, const Patient &patient,const Signal<int, int> &signal){

	test_date_ = new Date;
	*test_date_ = date;

	patients_ = unique_ptr<Patient> (new Patient);
	*patients_= patient;

	signal_ = new Signal<int, int>;
	*signal_ = signal;

}

/** destructor */
Holter::~Holter(){

	patients_.reset();
	delete test_date_;
	delete signal_;

}

										/** HOLTER EKG CLASS */
/** no arguments constructor */
HolterEKG::HolterEKG(): Holter (), signal_number_(0){ }

/** arguments (all) constructor */
HolterEKG::HolterEKG(const Date &date, const Patient &patient,const Signal<int, int>* signal, const RecorderEKG recorder, int signal_num){

	signal_number_ = signal_num;
	new_recorder_ = recorder;

	test_date_ = new Date;
	*test_date_ = date;

	patients_ = unique_ptr<Patient> (new Patient);
	*patients_= patient;

	signal_ = new Signal<int, int> [signal_num];
	for (int i=0; i<signal_num;++i){
		signal_[i] = signal[i];
	}

}

/** copy constructor */
HolterEKG::HolterEKG (HolterEKG &holter){

	signal_number_ = holter.signal_number_;
	new_recorder_ = holter.new_recorder_;

	patients_ = move(holter.patients_);

	test_date_ = new Date;
	test_date_ = holter.test_date_;

	signal_ = new Signal<int, int>[holter.signal_number_];
	for (int i=0; i<holter.signal_number_;++i){
		signal_[i] = holter.signal_[i];
	}

}

/** destructor */
HolterEKG::~HolterEKG(){

	patients_.reset();
	delete test_date_;
	delete [] signal_;

}

/** operator "=" */
HolterEKG & HolterEKG::operator=(HolterEKG &holter){

	if( this != &holter ){
		signal_number_ = holter.signal_number_;
		new_recorder_ = holter.new_recorder_;

		patients_ = move(holter.patients_);

		delete test_date_;
		test_date_ = new Date;
		test_date_ = holter.test_date_;

		delete [] signal_;
		signal_ = new Signal<int, int> [holter.signal_number_];
		for (int i=0; i<holter.signal_number_;++i){
			signal_[i] = holter.signal_[i];
		}
	}
	return *this;
}

/** virtual method for show date*/
void HolterEKG::show_date() {
	cout<<"HOLTER EKG DATE"<<endl;

	cout<<"Patient info:"<<endl;
	cout<<*patients_;

	cout<<"Recorder info:"<<endl;
	cout<<new_recorder_;

	cout<<"Test date:"<<endl;
	cout<<test_date_;

	cout<<"Signal number: "<<signal_number_<<endl;

	for (int i=0; i<signal_number_; i++){
		cout<<"Signal "<< i+1<<endl;
		cout<<signal_ [i];
	}
}

/** virtual method for write date to file */
void HolterEKG::write_date() {
	ofstream plikWyj ( "Holter_EKG_result.txt" ) ;
	if(!plikWyj)
		throw OpenFileError ("FILE NOT OPEN");

	plikWyj<< "Signal number: " <<signal_number_<<endl;
	if(!plikWyj)
		throw WriteFileError ("WRITE ERROR");

	new_recorder_.write_date(plikWyj);
	patients_->write_date(plikWyj);
	test_date_->write_date(plikWyj);
	signal_->write_date(plikWyj);

	plikWyj.close();
}

/** virtual method for read date from file */
void HolterEKG::read_date() {
	ifstream plikWej ( "Holter_EKG_result.txt" ) ;
	string tmp;
	if(!plikWej)
		throw OpenFileError ("FILE NOT OPEN");

	plikWej>>tmp;
	plikWej>>signal_number_;
	if(!plikWej)
		throw ReadFileError ("READ ERROR");

	new_recorder_.read_date(plikWej);
	patients_->read_date(plikWej);
	test_date_->read_date(plikWej);
	signal_->read_date(plikWej);

	plikWej.close();
}

									/** HOLTER ABPM CLASS */
/** no arguments constructor */
HolterABPM::HolterABPM(): Holter () { }

/** arguments (all) constructor */
HolterABPM::HolterABPM(const Date &date, const Patient &patient, const Signal<int, int> &signal, const RecorderABPM recorder, string mode) {

	mode_ = mode;
	new_recorder_ = recorder;

	test_date_ = new Date;
	*test_date_ = date;

	patients_ = unique_ptr<Patient> (new Patient);
	*patients_= patient;

	signal_ = new Signal<int, int>;
	*signal_ = signal;
}

/** copy constructor */
HolterABPM::HolterABPM (HolterABPM &holter){

	mode_ = holter.mode_;
	new_recorder_ = holter.new_recorder_;

	patients_ = move(holter.patients_);

	test_date_ = new Date;
	test_date_ = holter.test_date_;

	signal_ = new Signal<int, int>;
	signal_ = holter.signal_;

}

/** destructor */
HolterABPM::~HolterABPM(){

	patients_.reset();
	delete test_date_;
	delete signal_;

}

/** operator "=" */
HolterABPM & HolterABPM::operator=(HolterABPM &holter){

	if( this != &holter ){
		mode_ = holter.mode_;
		new_recorder_ = holter.new_recorder_;

		patients_ = move(holter.patients_);

		delete test_date_;
		test_date_ = new Date;
		test_date_ = holter.test_date_;

		delete signal_;
		signal_ = new Signal<int, int>;
		signal_ = holter.signal_;
	}
	return *this;
}

/** virtual method for show date*/
void HolterABPM::show_date() {
	cout<<"HOLTER ABPM DATE"<<endl;

	cout<<"Patient info:"<<endl;
	cout<<*patients_;

	cout<<"Recorder info:"<<endl;
	cout<<new_recorder_;

	cout<<"Recorder mode:"<<endl;
	cout<<mode_;

	cout<<"Test date:"<<endl;
	cout<<test_date_;

	cout<<"Signal:"<<endl;
	cout<<signal_;
}

/** virtual method for write date to file */
void HolterABPM::write_date() {
	ofstream plikWyj ( "Holter_ABPM_result.txt" ) ;
	if(!plikWyj)
		throw OpenFileError ("FILE NOT OPEN");

	plikWyj<< "Mode: " <<mode_<<endl;
	if(!plikWyj)
		throw WriteFileError ("WRITE ERROR");

	new_recorder_.write_date(plikWyj);
	patients_->write_date(plikWyj);
	test_date_->write_date(plikWyj);
	signal_->write_date(plikWyj);

	plikWyj.close();
}

/** virtual method for read date from file */
void HolterABPM::read_date() {
	ifstream plikWej ( "Holter_ABPM_result.txt" ) ;
	string tmp;
	if(!plikWej)
		throw OpenFileError ("FILE NOT OPEN");

	plikWej>>tmp;
	plikWej>>mode_;
	if(!plikWej)
		throw ReadFileError ("READ ERROR");

	new_recorder_.read_date(plikWej);
	patients_->read_date(plikWej);
	test_date_->read_date(plikWej);
	signal_->read_date(plikWej);

	plikWej.close();
}
