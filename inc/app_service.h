
/** Application service functions header file */

#ifndef APP_SERVICE_H_
#define APP_SERVICE_H_

#include <string>

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
	exit_form
} form_options;

string find_word(string line, int word_number);

#endif /* APP_SERVICE_H_ */
