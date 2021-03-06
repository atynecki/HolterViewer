
/** Subobject Signal header file */
#ifndef SIGNAL_H_
#define SIGNAL_H_

#include "std_lib_facilities.h"
#include "app_service.h"

using namespace std;

template <typename Elt1, typename Elt2>
class Signal {
public:
	vector<pair<Elt1, Elt2>> signal_;
	Signal(){};
	Signal (vector<pair<Elt1,Elt2>> sig);
	Signal(vector<Elt1> sample, vector<Elt2> time);
	Signal(const Signal &sig);

	Signal & operator=(const Signal &sig);
	Signal operator+(const Signal& sig) const;
	Signal operator()(Elt1 sample, Elt2 time) const;

	void show_date();
	void write_date(ofstream& file);
	void read_date(ifstream& file);
};

template <typename Elt1, typename Elt2>
void display_pair(pair<Elt1, Elt2> el);

template <typename Elt1, typename Elt2>
vector<Elt1> get_value_signal(const Signal<Elt1,Elt2>& sig);

template <typename Elt1, typename Elt2>
vector<Elt2> get_time_signal(const Signal<Elt1,Elt2>& sig);

template <typename Elt1, typename Elt2>
pair<Elt1, Elt2> find_max(const Signal<Elt1,Elt2>& sig);

template <typename Elt1, typename Elt2>
pair<Elt1, Elt2> find_min(const Signal<Elt1,Elt2>& sig);

template <typename Elt1, typename Elt2>
float calculate_frequance(const Signal<Elt1,Elt2>& sig, int sampling);

template <typename Elt1, typename Elt2>
void display_min_max (const Signal<Elt1,Elt2>& sig);

#include "ecg_signal_impl.h"

#endif /* SIGNAL_H_ */
