
/** Subobject Signal source file */

#include "ecg_signal.h"

/** no arguments constructor */
template < class Elt1, class Elt2 >
Signal<Elt1, Elt2>::Signal(): sample_num_(0){

	sample_ = nullptr;
	time_ = nullptr;
}

/** arguments (size) constructor */
template < class Elt1, class Elt2 >
Signal<Elt1, Elt2>::Signal(int sample_number): sample_num_ (sample_number) {

	sample_ = new Elt1 [sample_number];
	time_ = new Elt2 [sample_number];
}

/** arguments (all) constructor */
template < class Elt1, class Elt2 >
Signal<Elt1, Elt2>::Signal(int sample_number, Elt1 *sample, Elt2 *time): sample_num_ (sample_number) {

	sample_ = new Elt1 [sample_number];
	time_ = new Elt2 [sample_number];
	for(int i=0;i<sample_number;i++){
		sample_[i] = sample[i];
		time_ [i] = time[i];
	}
}

/** copy constructor */
template < class Elt1, class Elt2 >
Signal<Elt1, Elt2>::Signal(const Signal &signal){

	sample_num_ = signal.sample_num_;

	sample_ = new Elt1 [signal.sample_num_];
	time_ = new Elt2 [signal.sample_num_];
	for (int i=0; i<signal.sample_num_;i++){
		sample_ [i] = signal.sample_[i];
		time_ [i] = signal.time_[i];
	}
}

/** destructor */
template < class Elt1, class Elt2 >
Signal<Elt1, Elt2>::~Signal(){

	delete [] sample_;
	delete [] time_;
}

/** operator "=" */
template < class Elt1, class Elt2 >
Signal<Elt1, Elt2> & Signal<Elt1, Elt2>::operator=(const Signal &signal){

	if( this != &signal ){
		delete [] sample_;
		delete [] time_;
		sample_num_ = signal.sample_num_;
		sample_ = new Elt1 [signal.sample_num_];
		time_ = new Elt2 [signal.sample_num_];
		for (int i=0; i<signal.sample_num_;i++){
			sample_ [i] = signal.sample_[i];
			time_ [i] = signal.time_[i];
		}
	}
	return *this;
}

/** operator "+" */
template < class Elt1, class Elt2 >
Signal<Elt1, Elt2> Signal<Elt1, Elt2>::operator+(const Signal& sig) const {

	int sample_sum_num = sample_num_ + sig.sample_num_;
	Signal tmp(sample_sum_num);
	for (int i=0;i < sample_num_; i++){
		tmp.sample_ [i] = sample_ [i];
		tmp.time_ [i] = time_ [i];
	}

	for (int i=0;i < sig.sample_num_; i++){
		tmp.sample_ [sample_num_+i] = sig.sample_ [i];
		tmp.time_ [sample_num_+i] = sig.time_ [i];
	}
	return tmp;
}

/** operator "( )" */
template < class Elt1, class Elt2 >
Signal<Elt1, Elt2> Signal<Elt1, Elt2>::operator()(int sample, int time) const {

	int sample_add_num = sample_num_ + 1;
	Signal tmp(sample_add_num);
	for (int i=0;i < sample_num_; i++){
		tmp.sample_ [i] = sample_ [i];
		tmp.time_ [i] = time_ [i];
	}
	tmp.sample_ [sample_num_] = sample;
	tmp.time_ [sample_num_] = time;

	return tmp;
}

/** friend method for operator "<<" */
template < class Elt1, class Elt2 >
ostream & operator<<(std::ostream & os, const Signal<Elt1, Elt2> & signal){

	os << "Signal sample: "<<endl;
		for (int i=0; i < signal.sample_num_; i++) {
		os << signal.sample_[i]<< ",";
	}
	os<<endl;

	os << "Time sample: "<<endl;
		for (int i=0; i < signal.sample_num_; i++) {
		os << signal.time_[i]<< ",";
	}
	os<<endl;
	return os;
}

/** method for write date to file */
template < class Elt1, class Elt2 >
void Signal<Elt1, Elt2>::write_date(ofstream file) {
	//załatwic to w pętli
	if(!file) { } //rzucic wyjatkiem
}

/** method for read date from file */
template < class Elt1, class Elt2 >
void Signal<Elt1, Elt2>::read_date(ifstream file) {
	//załatwić to w pętli
	if(!file) { } //rzucic wyjatkiem
}
