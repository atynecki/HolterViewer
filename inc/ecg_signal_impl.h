/** Subobject Signal implementation file */

#include "ecg_signal.h"
//#include <algorithm>

using namespace std;

/** arguments (all) constructor */
template<typename Elt1, typename Elt2>
Signal<Elt1, Elt2>::Signal(vector<Elt1> sample, vector<Elt2> time) {
	if (sample.size() != time.size())
		//throw WrongSizeError ("DIFFERENT SIZE OF ARGUMENT");
	for (unsigned i = 0; i <sample.size(); ++i) {
		signal_[i].first = sample[i];
		signal_[i].second = time[i];
	}
}

/** Auxiliary function 1 */
template<typename Elt1, typename Elt2>
void Signal<Elt1, Elt2>::fun_1(pair<Elt1, Elt2> el) {
	signal_.push_back(el);
}

/** copy constructor */
template<typename Elt1, typename Elt2>
Signal<Elt1, Elt2>::Signal(const Signal &sig) {

	//for_each(sig.signal_.begin(), sig.signal_.end(), fun_1);
	for(size_t i = 0; i <sig.signal_.size(); ++i)
		fun_1(sig.signal_[i]);
}

/** operator "=" */
template<typename Elt1, typename Elt2>
Signal<Elt1, Elt2> & Signal<Elt1, Elt2>::operator=(const Signal &sig) {

	if (this != &sig) {
		//for_each(sig.signal_.begin(), sig.signal_.end(), fun_1);
		for(size_t i = 0; i <sig.signal_.size(); ++i)
			fun_1(sig.signal_[i]);
	}
	return *this;
}

/** operator "+" */
template<typename Elt1, typename Elt2>
Signal<Elt1, Elt2> Signal<Elt1, Elt2>::operator+(const Signal& sig) const {

	Signal tmp;
	tmp = *this;

	for(size_t i = 0; i <sig.signal_.size(); ++i) {
		tmp.signal_.push_back(sig.signal_[i]);
	}

	return tmp;
}

/** operator "( )" */
template<typename Elt1, typename Elt2>
Signal<Elt1, Elt2> Signal<Elt1, Elt2>::operator()(Elt1 sample,
		Elt2 time) const {

	pair<Elt1, Elt2> sample_signal;
	sample_signal.first = sample;
	sample_signal.second = time;

	Signal tmp;
	tmp = *this;

	tmp.signal_ = push_back(sample_signal);

	return tmp;
}

/** Auxiliary function 2 */
template<typename Elt1, typename Elt2>
void fun_2(pair<Elt1, Elt2> el) {
	cout << el.first << "," << el.second << endl;
}

/** method for show date */
template<typename Elt1, typename Elt2>
void Signal<Elt1,Elt2>::show_date(){
	cout << "Signal sample: " << endl;
	for (size_t i = 0; i <signal_.size(); ++i) {
		fun_2(signal_[i]);
	}
}

/** method for write date to file */
template<typename Elt1, typename Elt2>
void Signal<Elt1, Elt2>::write_date(ofstream& file) {
	for (vector<int>::const_iterator i = signal_.begin(); i != signal_.end();
			++i) {
		file << signal_[i].first << "," << signal_[i].second << endl;
		if (!file)
			throw WriteFileError("WRITE ERROR");
	}
}

/** method for read date from file */
template<typename Elt1, typename Elt2>
void Signal<Elt1, Elt2>::read_date(ifstream& file) {
	string read_temp;
	pair<Elt1, Elt2> sample_signal;

	while (file.eof() != 1) {
		getline(file, read_temp);
		if (!file)
			throw ReadFileError("READ ERROR");
		sample_signal.first = atoi(find_word(read_temp, 1).c_str());
		sample_signal.second = atoi(find_word(read_temp, 2).c_str());
		signal_.push_back(sample_signal);
	}
}
