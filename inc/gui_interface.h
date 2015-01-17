
/** GUI interface functions header file */

#ifndef GUI_INTERFACE_H_
#define GUI_INTERFACE_H_

#include "std_lib_facilities.h"
#include "graph_lib_file.h"
#include "holter.h"

using namespace std;
using namespace Graph_lib;

/** GUI functions */
char welcom_window_display();
int main_window_display(char option);
bool example_window_display(char option);
void enter_data_window_display(char option);
bool read_data_window_display(char option);
bool exit_window_display();

#endif /* GUI_INTERFACE_H_ */
