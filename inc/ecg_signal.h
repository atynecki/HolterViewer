
/** Subobject Signal header file */
#ifndef SIGNAL_H_
#define SIGNAL_H_

#include <iostream>
#include <string>
#include <fstream>
#include <utility>
#include <vector>
#include <algorithm>
#include "error.h"
#include "app_service.h"

using namespace std;

template <typename Elt1, typename Elt2>
class Signal {
	vector<pair<Elt1, Elt2>> signal_;
public:
	Signal(){};
	Signal(vector<Elt1> sample, vector<Elt2> time);
	Signal(const Signal &sig);

	Signal & operator=(const Signal &sig);
	Signal operator+(const Signal& sig) const;
	Signal operator()(Elt1 sample, Elt2 time) const;

	void fun_1(pair<Elt1, Elt2> el);

	void show_date();
	void write_date(ofstream& file);
	void read_date(ifstream& file);
};

template <typename Elt1, typename Elt2>
void display_pair(pair<Elt1, Elt2> el);

template <typename Elt1, typename Elt2>
vector<Elt1> parse_signal(const Signal<Elt1,Elt2>& sig);

template <typename Elt1, typename Elt2>
pair<Elt1, Elt2> find_max(const Signal<Elt1,Elt2>& sig);

template <typename Elt1, typename Elt2>
pair<Elt1, Elt2> find_min(const Signal<Elt1,Elt2>& sig);

template <typename Elt1, typename Elt2>
double calculate_frequance(const Signal<Elt1,Elt2>& sig);

#include "ecg_signal_impl.h"

#endif /* SIGNAL_H_ */
