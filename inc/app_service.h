
/** Application service functions header file */

#ifndef APP_SERVICE_H_
#define APP_SERVICE_H_

#include "std_lib_facilities.h"

using namespace std;

typedef enum{
	example =1,
	enter_date,
	read_date,
	exit_program
} main_options;

typedef enum{
	date =1,
	patient,
	recorder,
	signal,
	display,
	save,
	exit_form
} form_options;

string find_word(string line, int word_number);

void PressCToContinue();

template<class T>
string to_string(const T& t);

#endif /* APP_SERVICE_H_ */
