
/** Main source file to test classes */

#include "std_lib_facilities.h"

#include "holter.h"
#include "app_service.h"
#include "ecg_signal.h"
#include "Point.h"
#include "Line.h"
#include "Frame.h"
#include "Plot.h"
#include "GUI.h"

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
	unsigned counter;

	cout<<"Program start"<<endl;
	Welcome_window win1("HolterViewer", "Artur Tynecki");
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
					vector <int> sample = {1,4,7,9,14,17,11,9};
					vector <int> time = {1,2,3,4,5,6,7,8};
					Signal<int, int> signal(sample, time);
					HolterEKG holter_ekg_example(date, patient, &signal, recorder, 1);
					holter_ekg_global = holter_ekg_example;
					holter_ekg_example.show_date();
					cout<<endl;
					Plot_window <int, int> plot_example("Holter EKG example plot", sample, "V", time, "s");
					plot_example.display_win();
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
						holter_ekg_example.write_date(str);
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

				}
					break;
				case read_date:{
					HolterEKG holter_ekg_read;
					cout<<"Write the file name:"<<endl;
					cout<<"Enter here >";
					cin>>str;
					holter_ekg_read.read_date(str);
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
						vector<int> sample;
						vector<int> time;
						for(counter =0; counter<holter_ekg_read.get_signal_num(); ++counter){
							sample = get_value_signal(holter_ekg_read.signal_[counter].signal_);
							time = get_time_signal(holter_ekg_read.signal_[counter].signal_);
							Plot_window <int, int> plot_example("Holter EKG read plot", sample, "V", time, "s");
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
				cout<<"Wrong date! Try again"<<endl;
				cout<<"Enter here:";
				cin>>i;
			}

			switch (i) {
				case example:{
					RecorderABPM recorder("mmHg", 1003, 0.1, "Medi_tech", "ABPM-05");
					Patient patient(46, 182, 102, "Jan", "Kowalski", "74023086385");
					patient.set_id_number();
					Date date(2014,1,16);
					vector <int> sample = {12,14,20,4,7,17,11,2};
					vector <int> time = {1,2,3,4,5,6,7,8};
					Signal<int, int> signal(sample, time);
					HolterABPM holter_abpm_example(date, patient, signal, recorder, "normal");
					holter_abpm_global = holter_abpm_example;
					holter_abpm_example.show_date();
					cout<<endl;
					Plot_window <int, int> plot_example("Holter ABPM example plot", sample, "V", time, "s");
					plot_example.display_win();
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
						holter_abpm_example.write_date(str);
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
			case enter_date:
				break;
			case read_date:{
				HolterABPM holter_abpm_read;
				cout<<"Write the file name:"<<endl;
				cout<<"Enter here >";
				cin>>str;
				holter_abpm_read.read_date(str);
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
					vector<int> sample;
					vector<int> time;
					sample = get_value_signal(holter_abpm_read.signal_[0].signal_);
					time = get_time_signal(holter_abpm_read.signal_[0].signal_);
					Plot_window <int, int> plot_example("Holter ABPM read plot", sample, holter_abpm_read.new_recorder_.get_unit(), time, "s");
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

	cout<<"Program stop"<<endl;
	return 0;
}

catch (...){
	cerr<< "Unexpected exception\n";
}

