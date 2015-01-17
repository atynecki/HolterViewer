
#include "gui_interface.h"

HolterEKG holter_ekg_global;
HolterABPM holter_abpm_global;

char welcom_window_display(void)
{
	char ch;

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

	return ch;
}

int main_window_display(char option)
{
	int i;

	if(option == 'E'){
		Main_window mw_ekg("EKG");
		mw_ekg.display_win();
	}
	else if( option == 'A'){
		Main_window mw_abpm("ABPM");
		mw_abpm.display_win();
	}

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

	return i;
}

bool example_window_display(char option)
{
	char ch;
	string str;
	bool exit = false;

	Patient patient(46, 182, 102, "Jan", "Kowalski", "74023086385");
	patient.set_id_number();
	Date date(2014,1,16);

	if(option == 'E'){
		RecorderEKG recorder(3, 6969,1024, "ASPEL", "ASPEKT");
		vector <EKG_SIGNAL_TYPE> sample = {1,4,7,9,14,17,11,9,2,3,6,11,15,5,1};
		vector <TIME_TYPE> time = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
		Signal<EKG_SIGNAL_TYPE, TIME_TYPE> signal_ekg(sample, time);
		HolterEKG holter_ekg_example(date, patient, &signal_ekg, recorder, 1);
		holter_ekg_global = holter_ekg_example;
		holter_ekg_example.show_date();
		cout<<endl;
		Plot_window <EKG_SIGNAL_TYPE, TIME_TYPE> plot_example("Holter EKG example plot", sample, "V", time, "s");
		plot_example.display_win();
		display_min_max(signal_ekg);
	}
	else if(option == 'A'){
		RecorderABPM recorder("mmHg", 1003, 25, "Medi_tech", "ABPM-05");
		vector <ABPM_SIGNAL_TYPE> sample = {0.12,0.14,0.2,0.4,0.7,0.17,0.11,0.2,0.4,0.85,0.1,0.7,0.3,0.1,0.5};
		vector <TIME_TYPE> time = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
		Signal<ABPM_SIGNAL_TYPE, TIME_TYPE> signal_abpm(sample, time);
		HolterABPM holter_abpm_example(date, patient, signal_abpm, recorder, "normal");
		holter_abpm_global = holter_abpm_example;
		holter_abpm_example.show_date();
		cout<<endl;
		Plot_window <ABPM_SIGNAL_TYPE, TIME_TYPE> plot_example("Holter ABPM example plot", sample, "V", time, "s");
		plot_example.display_win();
		display_min_max(signal_abpm);
	}

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
		if(option == 'E')
			holter_ekg_global.write_date(str);

		else if(option == 'A')
			holter_abpm_global.write_date(str);
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

	return exit;
}

void enter_data_window_display(char option)
{
	int i;
	char ch;
	string str;
	bool form_exit = false;
	Form_window form_global;
	HolterEKG holter_ekg;
	HolterABPM holter_abpm;

	if(option == 'E'){
		Form_window form("EKG");
		form_global = form;
	}

	else if(option == 'A'){
		Form_window form("ABPM");
		form_global = form;
	}

	do {
		form_global.display_win();
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
				if(option == 'E')
					holter_ekg_global.test_date_ = date;
				else if(option =='A')
					holter_abpm_global.test_date_ = date;
				PressCToContinue();
			}
			break;
			case patient: {
				Patient_form_window form;
				form.display_win();
				form.enter_data();
				Patient patient(form.age_, form.growth_, form.weight_, form.name_, form.last_name_, form.pesel_);
				patient.set_id_number();
				if(option == 'E')
					holter_ekg.patients_ = patient;
				else if(option == 'A')
					holter_abpm.patients_ = patient;
				PressCToContinue();
			}
			break;
			case recorder: {
				if(option == 'E'){
					Recorder_form_window form("EKG");
					form.display_win();
					form.enter_data();
					RecorderEKG recorder(form.channel_number_,form.serial_number_,form.sampling_,form.producer_,form.model_);
					holter_ekg.new_recorder_ = recorder;
				}
				else if(option == 'A'){
					Recorder_form_window form("ABPM");
					form.display_win();
					form.enter_data();
					RecorderABPM recorder(form.unit_,form.serial_number_,form.sampling_,form.producer_,form.model_);
					holter_abpm.new_recorder_ = recorder;
				}
				PressCToContinue();
			}
			break;
			case signal: {
				if(option == 'E'){
					Signal_form_window  <EKG_SIGNAL_TYPE, TIME_TYPE> form;
					form.display_win();
					form.enter_data();
					Signal<EKG_SIGNAL_TYPE,TIME_TYPE> signal(form.sample_, form.time_);
					holter_ekg.signal_.push_back(signal);
					holter_ekg.set_signal_num(1);
				}
				else if(option == 'A'){
					Signal_form_window <ABPM_SIGNAL_TYPE, TIME_TYPE> form;
					form.display_win();
					form.enter_data();
					Signal<ABPM_SIGNAL_TYPE,TIME_TYPE> signal(form.sample_, form.time_);
					holter_abpm.signal_.push_back(signal);
				}
				PressCToContinue();
			}
			break;
			case display: {
				if(option == 'E')
					holter_ekg.show_date();
				else if(option == 'A')
					holter_abpm.show_date();
				PressCToContinue();
			}
			break;
			case save: {
				cout<<"Write the file name:"<<endl;
				cout<<"Enter here >";
				cin>>str;
				if(option == 'E'){
					try { holter_ekg.write_date(str); }
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
				}
				else if(option == 'A'){
					try { holter_abpm.write_date(str); }
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
				if (ch == 'T'){
					form_exit = true;
					holter_ekg_global = holter_ekg;
					holter_abpm_global = holter_abpm;
				}

				else
					form_exit = false;
			}
			break;
		}

	}

	while(!form_exit);
}

bool read_data_window_display(char option)
{
	char ch;
	string str;
	unsigned counter;
	bool exit = false;

	cout<<"Write the file name:"<<endl;
	cout<<"Enter here >";
	cin>>str;
	if(option == 'E')
		holter_ekg_global.read_date(str);
	else if(option == 'A')
		holter_abpm_global.read_date(str);

	cout<<endl;
	cout<<"Date read complete"<<endl;

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
		if(option == 'E'){
			holter_ekg_global.show_date();
			cout<<endl;
			vector<EKG_SIGNAL_TYPE> sample;
			vector<TIME_TYPE> time;
			for(counter =0; counter<holter_ekg_global.get_signal_num(); ++counter){
				sample = get_value_signal(holter_ekg_global.signal_[counter].signal_);
				time = get_time_signal(holter_ekg_global.signal_[counter].signal_);
				Plot_window <EKG_SIGNAL_TYPE, TIME_TYPE> plot_example("Holter EKG read plot", sample, "V", time, "s");
				plot_example.display_win();
			}
		}
		else if(option == 'A'){
			holter_abpm_global.show_date();
			cout<<endl;
			vector<ABPM_SIGNAL_TYPE> sample;
			vector<TIME_TYPE> time;
			sample = get_value_signal(holter_abpm_global.signal_[0].signal_);
			time = get_time_signal(holter_abpm_global.signal_[0].signal_);
			Plot_window <ABPM_SIGNAL_TYPE, TIME_TYPE> plot_example("Holter ABPM read plot", sample, holter_abpm_global.new_recorder_.get_unit(), time, "s");
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

	return exit;
}

bool exit_window_display()
{
	char ch;
	bool exit = false;

	cout<<"Finish program? [T/N] >";
	cin>>ch;
	ch = toupper(ch);
	if (ch == 'T')
		exit = true;
	else
		exit = false;

	return exit;
}



