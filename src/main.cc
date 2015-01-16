
/** Main source file to test classes */

#include "app_service.h"

#include "holter.h"

#include "graph_lib_file.h"

main_options options;
HolterEKG holter_ekg_global;
HolterABPM holter_abpm_global;

using namespace std;
using namespace Graph_lib;

int main () try
{
	char ch;
	int i;
	string str;
	bool exit = false;
	bool form_exit = false;
	unsigned counter;

	cout<<"Program start"<<endl;
	Welcome_window win1("HolterViewer v1.0", "Artur Tynecki");
	win1.display_win();
	cout<<endl;
	cout<<"Enter here >";
	cin>>ch;
	ch = toupper(ch);
	while ((ch != 'E') & (ch != 'A')){
		cout<<"Wrong date! Try again"<<endl;
		cout<<"Enter here >";
		cin>>ch;
		ch = toupper(ch);
	}

	/** HOLTER EKG */
	if(ch == 'E'){
		do {
			Main_window mw_ekg("EKG");
			mw_ekg.display_win();
			cout<<endl;
			cout<<"Enter here >";
			cin>>i;

			while ((i != 1) & (i != 2) & (i != 3) & (i != 4)){
				cin.clear();
				cin.ignore(numeric_limits<int>::max(), '\n');
				cout<<"Wrong date! Try again"<<endl;
				cout<<"Enter here >";
				cin>>i;
			}

			switch (i) {
				case example: {
					RecorderEKG recorder(3, 6969,1024, "ASPEL", "ASPEKT");
					Patient patient(46, 182, 102, "Jan", "Kowalski", "74023086385");
					patient.set_id_number();
					Date date(2014,1,16);
					vector <EKG_SIGNAL_TYPE> sample = {1,4,7,9,14,17,11,9,2,3,6,11,15,5,1};
					vector <TIME_TYPE> time = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
					Signal<EKG_SIGNAL_TYPE, TIME_TYPE> signal(sample, time);
					HolterEKG holter_ekg_example(date, patient, &signal, recorder, 1);
					holter_ekg_global = holter_ekg_example;
					holter_ekg_example.show_date();
					cout<<endl;
					Plot_window <EKG_SIGNAL_TYPE, TIME_TYPE> plot_example("Holter EKG example plot", sample, "V", time, "s");
					plot_example.display_win();
					display_min_max(signal);
					cout<<"Write date to file? [T/N] >";
					cin>>ch;
					ch = toupper(ch);
					while ((ch != 'T') & (ch != 'N')){
						cout<<"Wrong answer! Try again"<<endl;
						cout<<"Enter here >";
						cin>>ch;
						ch = toupper(ch);
					}

					if (ch == 'T'){
						cout<<"Write the file name:"<<endl;
						cout<<"Enter here >";
						cin>>str;
						try { holter_ekg_example.write_date(str); }
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
						cout<<endl;
						cout<<"Date write complete"<<endl;
					}

					cout<<"Finish program? [T/N] >";
					cin>>ch;
					ch = toupper(ch);
					if (ch == 'T')
						exit = true;
					else
						exit = false;
				}
				break;

				case enter_date:{
					HolterEKG holter_ekg_form;
					Form_window form("EKG");
					do {
						form.display_win();
						cout<<endl;
						cout<<"Enter here >";
						cin>>i;
						while ((i != 1) & (i != 2) & (i != 3) & (i != 4) & (i != 5) & (i != 6)& (i != 7)){
							cin.clear();
							cin.ignore(numeric_limits<int>::max(), '\n');
							cout<<"Wrong date! Try again"<<endl;
							cout<<"Enter here:";
							cin>>i;
						}
						switch (i) {
							case date: {
								Date_form_window form;
								form.display_win();
								form.enter_data();
								Date date(form.day_,form.month_,form.year_);
								holter_ekg_form.test_date_ = date;
								PressCToContinue();
							}
							break;
							case patient: {
								Patient_form_window form;
								form.display_win();
								form.enter_data();
								Patient patient(form.age_, form.growth_, form.weight_, form.name_, form.last_name_, form.pesel_);
								patient.set_id_number();
								holter_ekg_form.patients_ = patient;
								PressCToContinue();
							}
							break;
							case recorder: {
								Recorder_form_window form("EKG");
								form.display_win();
								form.enter_data();
								RecorderEKG recorder(form.channel_number_,form.serial_number_,form.sampling_,form.producer_,form.model_);
								holter_ekg_form.new_recorder_ = recorder;
								PressCToContinue();
							}
							break;
							case signal: {
								Signal_form_window  <EKG_SIGNAL_TYPE> form;
								form.display_win();
								form.enter_data();
								Signal<EKG_SIGNAL_TYPE,TIME_TYPE> signal(form.sample_, form.time_);
								holter_ekg_form.signal_.push_back(signal);
								holter_ekg_form.set_signal_num(1);
								PressCToContinue();
							}
							break;
							case display: {
								holter_ekg_form.show_date();
								PressCToContinue();
							}
							break;
							case save: {
								cout<<"Write the file name:"<<endl;
								cout<<"Enter here >";
								cin>>str;
								try{holter_ekg_form.write_date(str);}
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
								cout<<endl;
								cout<<"Date write complete"<<endl;
								PressCToContinue();
							}
							break;
							case exit_form: {
								cout<<"Finish enter date? [T/N] >";
								cin>>ch;
								ch = toupper(ch);
								if (ch == 'T')
									form_exit = true;
								else
									form_exit = false;
							}
							break;
						}
					}
					while(!form_exit);

				}
					break;
				case read_date: {
					HolterEKG holter_ekg_read;
					cout<<"Write the file name:"<<endl;
					cout<<"Enter here >";
					cin>>str;
					try {holter_ekg_read.read_date(str);}
					catch (const OpenFileError &of_error){
						Error_window win_err(of_error.get_error());
						win_err.display_win();
						break;
					}
					catch (const ReadFileError &r_error){
						Error_window win_err(r_error.get_error());
						win_err.display_win();
						break;
					}
					cout<<endl;
					cout<<"Date read complete"<<endl;
					holter_ekg_global = holter_ekg_read;


					cout<<"Display date? [T/N] >";
					cin>>ch;
					ch = toupper(ch);
					while ((ch != 'T') & (ch != 'N')){
						cout<<"Wrong answer! Try again"<<endl;
						cout<<"Enter here >";
						cin>>ch;
						ch = toupper(ch);
					}

					if (ch == 'T'){
						holter_ekg_read.show_date();
						cout<<endl;
						vector<EKG_SIGNAL_TYPE> sample;
						vector<TIME_TYPE> time;
						for(counter =0; counter<holter_ekg_read.get_signal_num(); ++counter){
							sample = get_value_signal(holter_ekg_read.signal_[counter].signal_);
							time = get_time_signal(holter_ekg_read.signal_[counter].signal_);
							Plot_window <EKG_SIGNAL_TYPE, TIME_TYPE> plot_example("Holter EKG read plot", sample, "V", time, "s");
							plot_example.display_win();
						}
					}

					cout<<"Finish program? [T/N] >";
					cin>>ch;
					ch = toupper(ch);
					if (ch == 'T')
						exit = true;
					else
						exit = false;
				}
					break;
				case exit_program:
					cout<<"Finish program? [T/N] >";
					cin>>ch;
					ch = toupper(ch);
					if (ch == 'T')
						exit = true;
					else
						exit = false;
					break;
			}
		}
		while(!exit);

	}

	/** HOLTER ABPM */
	else if (ch == 'A'){
		do {
			Main_window mw_abpm("ABPM");
			mw_abpm.display_win();
			cout<<endl;
			cout<<"Enter here:";
			cin>>i;
			while ((i != 1) & (i != 2) & (i != 3) & (i != 4)){
				cin.clear();
				cin.ignore(numeric_limits<int>::max(), '\n');
				cout<<"Wrong date! Try again"<<endl;
				cout<<"Enter here: >";
				cin>>i;
			}

			switch (i) {
				case example:{
					RecorderABPM recorder("mmHg", 1003, 25, "Medi_tech", "ABPM-05");
					Patient patient(46, 182, 102, "Jan", "Kowalski", "74023086385");
					patient.set_id_number();
					Date date(2014,1,16);
					vector <ABPM_SIGNAL_TYPE> sample = {0.12,0.14,0.2,0.4,0.7,0.17,0.11,0.2,0.4,0.85,0.1,0.7,0.3,0.1,0.5};
					vector <TIME_TYPE> time = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
					Signal<ABPM_SIGNAL_TYPE, TIME_TYPE> signal(sample, time);
					HolterABPM holter_abpm_example(date, patient, signal, recorder, "normal");
					holter_abpm_global = holter_abpm_example;
					holter_abpm_example.show_date();
					cout<<endl;
					Plot_window <ABPM_SIGNAL_TYPE, TIME_TYPE> plot_example("Holter ABPM example plot", sample, "V", time, "s");
					plot_example.display_win();
					display_min_max(signal);
					cout<<"Write date to file? [T/N] >";
					cin>>ch;
					ch = toupper(ch);
					while ((ch != 'T') & (ch != 'N')){
						cout<<"Wrong answer! Try again"<<endl;
						cout<<"Enter here >";
						cin>>ch;
						ch = toupper(ch);
					}

					if (ch == 'T'){
						cout<<"Write the file name:"<<endl;
						cout<<"Enter here >";
						cin>>str;

						try{holter_abpm_example.write_date(str);}
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

						cout<<endl;
						cout<<"Date write complete"<<endl;
					}

					cout<<"Finish program? [T/N] >";
					cin>>ch;
					ch = toupper(ch);
					if (ch == 'T')
						exit = true;
					else
						exit = false;
				}
				break;
			case enter_date: {
				HolterABPM holter_abpm_form;
				Form_window form("ABPM");
			do {
				form.display_win();
				cout<<endl;
				cout<<"Enter here >";
				cin>>i;
				while ((i != 1) & (i != 2) & (i != 3) & (i != 4) & (i != 5) & (i != 6) & (i != 7)){
					cin.clear();
					cin.ignore(numeric_limits<int>::max(), '\n');
					cout<<"Wrong date! Try again"<<endl;
					cout<<"Enter here >";
					cin>>i;
				}
				switch (i) {
					case date: {
						Date_form_window form;
						form.display_win();
						form.enter_data();
						Date date(form.day_,form.month_,form.year_);
						holter_abpm_form.test_date_ = date;
						PressCToContinue();
					}
					break;
					case patient: {
						Patient_form_window form;
						form.display_win();
						form.enter_data();
						Patient patient(form.age_, form.growth_, form.weight_, form.name_, form.last_name_, form.pesel_);
						patient.set_id_number();
						holter_abpm_form.patients_ = patient;
						PressCToContinue();
					}
					break;
					case recorder: {
						Recorder_form_window form("ABPM");
						form.display_win();
						form.enter_data();
						RecorderABPM recorder(form.unit_,form.serial_number_,form.sampling_,form.producer_,form.model_);
						holter_abpm_form.new_recorder_ = recorder;
						PressCToContinue();
					}
					break;
					case signal: {
						Signal_form_window <ABPM_SIGNAL_TYPE> form;
						form.display_win();
						form.enter_data();
						Signal<ABPM_SIGNAL_TYPE,TIME_TYPE> signal(form.sample_, form.time_);
						holter_abpm_form.signal_.push_back(signal);
						PressCToContinue();
					}
					break;
					case display: {
						holter_abpm_form.show_date();
						PressCToContinue();
					}
					break;
					case save: {
						cout<<"Write the file name:"<<endl;
						cout<<"Enter here >";
						cin>>str;

						try{holter_abpm_form.write_date(str);}
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

						cout<<endl;
						cout<<"Date write complete"<<endl;
						PressCToContinue();
					}
					break;
					case exit_form: {
						cout<<"Finish enter date? [T/N] >";
						cin>>ch;
						ch = toupper(ch);
						if (ch == 'T')
							form_exit = true;
						else
							form_exit = false;
					}
					break;
				}
				}
				while(!form_exit);
			}
				break;
			case read_date:{
				HolterABPM holter_abpm_read;
				cout<<"Write the file name:"<<endl;
				cout<<"Enter here >";
				cin>>str;
				try {holter_abpm_read.read_date(str);}
				catch (const OpenFileError &of_error){
					Error_window win_err(of_error.get_error());
					win_err.display_win();
					break;
				}
				catch (const ReadFileError &r_error){
					Error_window win_err(r_error.get_error());
					win_err.display_win();
					break;
				}
				cout<<endl;
				cout<<"Date read complete"<<endl;
				holter_abpm_global = holter_abpm_read;

				cout<<"Display date? [T/N] >";
				cin>>ch;
				ch = toupper(ch);
				while ((ch != 'T') & (ch != 'N')){
					cout<<"Wrong answer! Try again"<<endl;
					cout<<"Enter here >";
					cin>>ch;
					ch = toupper(ch);
				}

				if (ch == 'T'){
					holter_abpm_read.show_date();
					cout<<endl;
					vector<ABPM_SIGNAL_TYPE> sample;
					vector<TIME_TYPE> time;
					sample = get_value_signal(holter_abpm_read.signal_[0].signal_);
					time = get_time_signal(holter_abpm_read.signal_[0].signal_);
					Plot_window <ABPM_SIGNAL_TYPE, TIME_TYPE> plot_example("Holter ABPM read plot", sample, holter_abpm_read.new_recorder_.get_unit(), time, "s");
					plot_example.display_win();
				}

				cout<<"Finish program? [T/N] >";
				cin>>ch;
				ch = toupper(ch);
				if (ch == 'T')
					exit = true;
				else
					exit = false;
			}

				break;
			case exit_program:{
				cout<<"Finish program? [T/N] >";
				cin>>ch;
				ch = toupper(ch);
				if (ch == 'T')
					exit = true;
				else
				exit = false;
			}
				break;
			}
		}while(!exit);
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
	cerr<< "Unexpected exception\n";
}

