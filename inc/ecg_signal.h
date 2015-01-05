
/** Subobject Signal header file */
#ifndef SIGNAL_H_
#define SIGNAL_H_

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

template < class Elt1, class Elt2 >
class Signal {
	//dane przechowywać w kontenerze?? (para albo vector)
	Elt1 *sample_;
	Elt2 *time_;
	int sample_num_;
public:
	Signal();
	Signal(int sample_number);
	Signal(int sample_number, Elt1 *sample, Elt2 *time);
	Signal(const Signal &signal);

	~Signal();

	Signal & operator=(const Signal &signal);
	Signal operator+(const Signal& sig) const;
	Signal operator()(Elt1 sample, Elt2 time) const;

	friend ostream & operator<<(std::ostream & os, const Signal<Elt1, Elt2> & signal);

	void write_date(ofstream file);
	void read_date(ifstream file);

};

#endif /* SIGNAL_H_ */
