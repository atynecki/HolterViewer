
/** Main source file to test classes */

#include "gui_interface.h"
#include "graph_lib_file.h"

main_options options;

using namespace Graph_lib;

int main () try
{
	char ch_replay;
	int i_replay;
	string str;
	bool exit = false;

	ch_replay = welcom_window_display();

	/** HOLTER EKG */
	if(ch_replay == 'E'){
		do {
			i_replay =  main_window_display(ch_replay);

			switch (i_replay) {
				case example:
					try {exit =  example_window_display(ch_replay);}
					catch (const OpenFileError &of_error){
						Error_window win_err(of_error.get_error());
						win_err.display_win();
						break;
					}
					catch (const WriteFileError &w_error){
						Error_window win_err(w_error.get_error());
						win_err.display_win();
						break;
					}
				break;

				case enter_date:
					enter_data_window_display(ch_replay);
				break;

				case read_date:
					try {exit = read_data_window_display(ch_replay);}
					catch (const OpenFileError &of_error){
						Error_window win_err(of_error.get_error());
						win_err.display_win();
						break;
					}
					catch (const WriteFileError &w_error){
						Error_window win_err(w_error.get_error());
						win_err.display_win();
						break;
					}
				break;

				case exit_program:
					exit = exit_window_display();
					break;
			}
		}
		while(!exit);

	}

	/** HOLTER ABPM */
	else if (ch_replay == 'A'){
		do {
			i_replay =  main_window_display(ch_replay);

			switch (i_replay) {
				case example:
					try {exit =  example_window_display(ch_replay);}
					catch (const OpenFileError &of_error){
						Error_window win_err(of_error.get_error());
						win_err.display_win();
						break;
					}
					catch (const WriteFileError &w_error){
						Error_window win_err(w_error.get_error());
						win_err.display_win();
						break;
					}
				break;

				case enter_date:
					enter_data_window_display(ch_replay);
				break;

				case read_date:
					try {exit = read_data_window_display(ch_replay);}
					catch (const OpenFileError &of_error){
						Error_window win_err(of_error.get_error());
						win_err.display_win();
						break;
					}
					catch (const WriteFileError &w_error){
						Error_window win_err(w_error.get_error());
						win_err.display_win();
						break;
					}
				break;

				case exit_program:
					exit = exit_window_display();
					break;
			}
		}
		while(!exit);
	}

	Close_window close;
	close.display_win();

	return 0;
}

catch (const WrongSizeError &wz_error){
	Error_window win_err(wz_error.get_error());
	win_err.display_win();
}

catch (const CalculationError &c_error){
	Error_window win_err(c_error.get_error());
	win_err.display_win();
}

catch (...){
	Error_window win_err("Unexpected exception\n");
	win_err.display_win();
}
