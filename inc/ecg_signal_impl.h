/** Subobject Signal implementation file */

#include "ecg_signal.h"

using namespace std;

/** arguments (all) constructor 1*/
template<typename Elt1, typename Elt2>
Signal<Elt1, Elt2>::Signal(vector<pair<Elt1,Elt2>> sig) {
	signal_ = sig;
}


/** arguments (all) constructor 2*/
template<typename Elt1, typename Elt2>
Signal<Elt1, Elt2>::Signal(vector<Elt1> sample, vector<Elt2> time) {
	if (sample.size() != time.size())
		throw WrongSizeError ("DIFFERENT SIZE OF SIGNAL ARGUMENT");

	pair<Elt1, Elt2> tmp;

	for (unsigned i = 0; i <sample.size(); ++i) {
		tmp.first = sample[i];
		tmp.second = time[i];
		signal_.push_back(tmp);
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
	for(unsigned i = 0; i <sig.signal_.size(); ++i)
		fun_1(sig.signal_[i]);
}

/** operator "=" */
template<typename Elt1, typename Elt2>
Signal<Elt1, Elt2> & Signal<Elt1, Elt2>::operator=(const Signal &sig) {

	if (this != &sig) {
		//for_each(sig.signal_.begin(), sig.signal_.end(), fun_1);
		for(unsigned i = 0; i <sig.signal_.size(); ++i)
			fun_1(sig.signal_[i]);
	}
	return *this;
}

/** operator "+" */
template<typename Elt1, typename Elt2>
Signal<Elt1, Elt2> Signal<Elt1, Elt2>::operator+(const Signal& sig) const {

	Signal tmp;
	tmp = *this;

	for(unsigned i = 0; i <sig.signal_.size(); ++i) {
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
void display_pair(pair<Elt1, Elt2> el) {
	cout << el.first << "," << el.second << endl;
}

/** method for show date */
template<typename Elt1, typename Elt2>
void Signal<Elt1,Elt2>::show_date(){
	cout << "Signal sample: " << endl;
	for (unsigned i = 0; i <signal_.size(); ++i) {
		display_pair(signal_[i]);
	}
}

/** method for write date to file */
template<typename Elt1, typename Elt2>
void Signal<Elt1, Elt2>::write_date(ofstream& file) {
	for (unsigned i = 0; i <signal_.size(); ++i) {
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

	signal_.pop_back();
}

/** method for get value signal form hole signal*/
template <typename Elt1, typename Elt2>
vector<Elt1> get_value_signal(const vector<pair<Elt1, Elt2>> sig){
	vector<Elt1> result;
	for (unsigned i = 0; i <sig.size(); ++i)
		result.push_back(get<0>(sig[i]));

	return result;
}

/** method for get time signal form hole signal*/
template <typename Elt1, typename Elt2>
vector<Elt2> get_time_signal(const vector<pair<Elt1, Elt2>> sig){
	vector<Elt2> result;
	for (unsigned i = 0; i <sig.size(); ++i)
		result.push_back(get<1>(sig[i]));

	return result;
}

/** method for find max value in signal*/
template<typename Elt1, typename Elt2>
pair<Elt1, Elt2> find_max(const Signal<Elt1,Elt2>& sig){
	vector<Elt1> signal_samples;
	pair<Elt1, Elt2> result;
	int position;

	signal_samples = parse_signal(sig.signal_);

	position = (int)(max_element(signal_samples.begin(), signal_samples.end()) - signal_samples.begin());

	result = sig.signal_[position];

	return result;
}
/** method for find min value in signal*/
template<typename Elt1, typename Elt2>
pair<Elt1, Elt2> find_min(const Signal<Elt1,Elt2>& sig){
	vector<Elt1> signal_samples;
	pair<Elt1, Elt2> result;
	int position;

	signal_samples = parse_signal(sig.signal_);

	position = (int)(min_element(signal_samples.begin(), signal_samples.end()) - signal_samples.begin());

	result = sig.signal_[position];

	return result;
}
/** method for calculate frequance in signal*/
template<typename Elt1, typename Elt2>
float calculate_frequance(const Signal<Elt1,Elt2>& sig, int sampling){
	vector<Elt1> signal_samples;
	float result;
	int length;
	Elt2 begin;

	signal_samples = parse_signal(sig.signal_);

	if (signal_samples.size < 2*sampling)
		throw WrongSizeError ("TOO SHORT SIGNAL TO CALCULATE FREQ");

	begin = max_element (signal_samples.begin(),signal_samples.begin()+sampling);
	length = (int)(find(++signal_samples.begin(), signal_samples.end(), begin) - signal_samples.begin());

	if(length ==0)
		throw CalculationError("SIGNAL IS NOT PERIODIC");
	result = (float)(1)/(float)length;

	return result;
}
