
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

bool IsDouble (const string &str);
double ConvertToDouble (const string &str);

#endif /* APP_SERVICE_H_ */
