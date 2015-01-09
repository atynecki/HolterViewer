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
Holter::Holter(){ }

/** arguments (all) constructor */
Holter::Holter(const Date &date, const Patient &patient,const Signal<int, int> &signal){
	test_date_ = date;
	patients_= patient;
	signal_.push_back(signal);
}

/** destructor */
Holter::~Holter(){ }

										/** HOLTER EKG CLASS */
/** no arguments constructor */
HolterEKG::HolterEKG(): Holter (), signal_number_(0){ }

/** arguments (all) constructor */
HolterEKG::HolterEKG(const Date &date, const Patient &patient,const Signal<int, int>* signal, const RecorderEKG recorder, int signal_num){

	signal_number_ = signal_num;
	new_recorder_ = recorder;
	test_date_ = date;
	patients_= patient;

	for (int i=0; i<signal_num;++i){
		signal_.push_back(signal[i]);
	}
}

/** copy constructor */
HolterEKG::HolterEKG (HolterEKG &holter){

	signal_number_ = holter.signal_number_;
	new_recorder_ = holter.new_recorder_;
	test_date_ = holter.test_date_;
	patients_ =holter.patients_;

	signal_ = holter.signal_;
}

/** destructor */
HolterEKG::~HolterEKG(){ }

/** operator "=" */
HolterEKG & HolterEKG::operator=(HolterEKG &holter){

	if( this != &holter ){
		signal_number_ = holter.signal_number_;
		new_recorder_ = holter.new_recorder_;
		test_date_ = holter.test_date_;
		patients_ =holter.patients_;

		signal_ = holter.signal_;
	}
	return *this;
}

/** virtual method for show date*/
void HolterEKG::show_date() {
	cout<<"HOLTER EKG DATE"<<endl;

	cout<<"Patient info:"<<endl;
	cout<<patients_;

	cout<<"Recorder info:"<<endl;
	cout<<new_recorder_;

	cout<<"Test date:"<<endl;
	cout<<test_date_;

	cout<<"Signal number: "<<signal_number_<<endl;

	for (unsigned i=0; i<signal_number_; i++){
		cout<<"Signal "<< i+1<<endl;
		signal_[i].show_date();
	}
}

/** virtual method for write date to file */
void HolterEKG::write_date() {
	ofstream plikWyj ( "Holter_EKG_result.txt" ) ;
	if(!plikWyj)
		throw OpenFileError ("FILE NOT OPEN");

	plikWyj<< "HOLTER_EKG_DATE"<<endl;
	if(!plikWyj)
			throw WriteFileError ("WRITE ERROR");

	plikWyj<< "Signal_number: " <<signal_number_<<endl;
	if(!plikWyj)
		throw WriteFileError ("WRITE ERROR");

	new_recorder_.write_date(plikWyj);
	patients_.write_date(plikWyj);
	test_date_.write_date(plikWyj);
	for (unsigned i=0; i<signal_number_; i++){
			signal_[i].write_date(plikWyj);
			plikWyj<<"0,0"<<endl;
	}

	plikWyj.close();
}

/** virtual method for read date from file */
void HolterEKG::read_date() {
	string tmp;
	pair<int,int> signal_end(0,0);
	Signal<int, int> signal_tab;
	Signal<int ,int> signal_result;
	vector<pair<int,int>> signal_tmp;
	vector<pair<int, int>>::iterator head;
	vector<pair<int, int>>::iterator tail;

	ifstream plikWej ( "Holter_EKG_result.txt" ) ;
	if(!plikWej)
		throw OpenFileError ("FILE NOT OPEN");

	getline(plikWej, tmp);
	getline(plikWej, tmp);
	if(!plikWej)
		throw ReadFileError ("READ ERROR");

	signal_number_= atoi(tmp.substr(14).c_str());

	if(!plikWej)
		throw ReadFileError ("READ ERROR");

	new_recorder_.read_date(plikWej);
	patients_.read_date(plikWej);
	test_date_.read_date(plikWej);

	signal_tab.read_date(plikWej);
	head = signal_tab.signal_.begin();
	for(unsigned i = 0; i<signal_number_; ++i){
		tail = signal_tab.signal_.end();
		tail = find(head, tail, signal_end);
		signal_tmp = signal_tab.signal_;
		signal_tmp.assign(head, tail);
		Signal<int ,int> signal_result(signal_tmp);
		signal_.push_back(signal_result);
		head = ++tail;
	}

	plikWej.close();
}

									/** HOLTER ABPM CLASS */
/** no arguments constructor */
HolterABPM::HolterABPM(): Holter () { }

/** arguments (all) constructor */
HolterABPM::HolterABPM(const Date &date, const Patient &patient, const Signal<int, int> &signal, const RecorderABPM recorder, string mode) {

	mode_ = mode;
	new_recorder_ = recorder;
	test_date_ = date;
	patients_= patient;

	signal_.push_back(signal);
}

/** copy constructor */
HolterABPM::HolterABPM (HolterABPM &holter){

	mode_ = holter.mode_;
	new_recorder_ = holter.new_recorder_;
	test_date_ = holter.test_date_;
	patients_ = holter.patients_;

	signal_ = holter.signal_;
}

/** destructor */
HolterABPM::~HolterABPM(){ }

/** operator "=" */
HolterABPM & HolterABPM::operator=(HolterABPM &holter){

	if( this != &holter ){
		mode_ = holter.mode_;
		new_recorder_ = holter.new_recorder_;
		test_date_ = holter.test_date_;
		patients_ = holter.patients_;

		signal_ = holter.signal_;
	}
	return *this;
}

/** virtual method for show date*/
void HolterABPM::show_date() {
	cout<<"HOLTER ABPM DATE"<<endl;

	cout<<"Patient info:"<<endl;
	cout<<patients_;

	cout<<"Recorder info:"<<endl;
	cout<<new_recorder_;

	cout<<"Recorder mode:"<<mode_<<endl;

	cout<<"Test date:"<<endl;
	cout<<test_date_;

	signal_[0].show_date();
}

/** virtual method for write date to file */
void HolterABPM::write_date() {
	ofstream plikWyj ( "Holter_ABPM_result.txt" ) ;
	if(!plikWyj)
		throw OpenFileError ("FILE NOT OPEN");

	plikWyj<< "HOLTER_ABPM_DATE"<<endl;
	if(!plikWyj)
		throw WriteFileError ("WRITE ERROR");

	plikWyj<< "Mode: " <<mode_<<endl;
	if(!plikWyj)
		throw WriteFileError ("WRITE ERROR");

	new_recorder_.write_date(plikWyj);
	patients_.write_date(plikWyj);
	test_date_.write_date(plikWyj);
	signal_[0].write_date(plikWyj);

	plikWyj.close();
}

/** virtual method for read date from file */
void HolterABPM::read_date() {
	string tmp;
	ifstream plikWej ( "Holter_ABPM_result.txt" ) ;
	if(!plikWej)
		throw OpenFileError ("FILE NOT OPEN");

	getline(plikWej, tmp);
	getline(plikWej, tmp);
	if(!plikWej)
		throw ReadFileError ("READ ERROR");

	mode_ = tmp.substr(6);

	new_recorder_.read_date(plikWej);
	patients_.read_date(plikWej);
	test_date_.read_date(plikWej);

	if(signal_.empty()){
		Signal<int, int> signal_tmp;
		signal_.push_back(signal_tmp);
	}

	signal_[0].read_date(plikWej);

	plikWej.close();
}
