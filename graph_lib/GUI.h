
/** GUI class header file */

#ifndef GUI_H_
#define GUI_H_

#include "std_lib_facilities.h"
#include "app_service.h"

#include "Frame.h"
#include "Plot.h"

namespace Graph_lib {

class Window {
public:
	vector<Frame> frames_;
	Point start_point_;

	Window(): start_point_(Point(0,0,' ')) { }
	Window(Point start_point, vector<Frame> frames): start_point_(start_point) {
		frames_ = frames;
	}

	Window(const Window& win){
		start_point_ = win.start_point_;
		frames_ = win.frames_;
	}

	Window & operator=( const Window& win){
		if(this !=&win){
			start_point_ = win.start_point_;
			frames_ = win.frames_;
		}
		return *this;
	}

	virtual ~Window() { }
	virtual void display_win() = 0;
};

class Welcome_window: public Window {

protected:
	string program_name_;
	string author_;

	Welcome_window(): Window() { }
	Welcome_window(const Welcome_window& w_win) { }
	Welcome_window & operator=( const Welcome_window& win){ }
public:
	Welcome_window(string program, string author) {
		start_point_ = Point (20,0, ' ');
		vector<string> text_message;

		text_message.push_back("Welcome to:");
		text_message.push_back(program);
		text_message.push_back("Author:");
		text_message.push_back(author);
		Text_box welcome_frame(50, start_point_, 'x', text_message);
		frames_.push_back(welcome_frame);

		text_message.clear();
		text_message.push_back("Select Holter type: ");
		text_message.push_back("Holter EKG - E ");
		text_message.push_back("Holter ABPM - A ");
		text_message.push_back("Press enter");
		Text_box holter_type(50, start_point_, '_', text_message);
		frames_.push_back(holter_type);
	}

	virtual ~Welcome_window() { }
	virtual void display_win(){
		frames_[0].display();
		cout<<endl;
		frames_[1].display();
	}
};

class Close_window: public Window {
protected:
	Close_window(const Close_window& c_win) { }
	Close_window & operator=( const Close_window& c_win){ }
public:
	Close_window() {
		start_point_ = Point (20,0, ' ');
		vector<string> text_message;

		text_message.push_back("Program HolterViewer v1.0 will be closed!");
		text_message.push_back("Thank you and welcome again");
		Text_box close_frame(50, start_point_, 'x', text_message);
		frames_.push_back(close_frame);
	}

	virtual ~Close_window() { }
	virtual void display_win(){
		frames_[0].display();
		cout<<endl;
	}
};

class Main_window: public Window {
protected:
	string holter_type_;

	Main_window(): Window() { }
	Main_window(const Main_window& m_win) { }
	Main_window & operator=( const Main_window& m_win){ }
public:
	Main_window(string type) {
		start_point_ = Point (20,0, ' ');
		vector<string> text_message;

		holter_type_ = type;

		if(holter_type_ == "EKG")
			text_message.push_back("Select function for Holter EKG:");
		else if(holter_type_ == "ABPM")
			text_message.push_back("Select function for Holter APBM:");

		text_message.push_back("Show example - 1");
		text_message.push_back("Enter date - 2");
		text_message.push_back("Read date from file - 3");
		text_message.push_back("Exit - 4");
		text_message.push_back("and press enter");
		Text_box main_frame(50, start_point_, '_', text_message);
		frames_.push_back(main_frame);
	}

	virtual ~Main_window() { }
	virtual void display_win(){
		frames_[0].display();
		cout<<endl;
	}

};

template <typename Elt1, typename Elt2>
class Plot_window: public Window {
protected:
	Title plot_title_;
	Plot<Elt1, Elt2> plot_;
	Plot_window(): Window() { }
	Plot_window(const Plot_window& p_win) { }
	Plot_window & operator=( const Plot_window& p_win){ }
public:
	Plot_window(string title, vector<Elt1> signal, string y_unit, vector<Elt2> time, string x_unit){
		plot_title_ = Title(title);
		plot_ = Plot<Elt1, Elt2> (signal, Label("Sample", y_unit), time, Label("Time", x_unit), 'x');
	}

	virtual ~Plot_window() { }

	virtual void display_win(){
		plot_title_.display_title();
		cout<<endl;
		plot_.display_plot();
	}
};

class Form_window: public Window {
protected:
	string holter_type_;

	Form_window(const Close_window& f_win) { }
	Form_window & operator=( const Close_window& f_win){ }
public:
	Form_window();
	Form_window(string type) {
		holter_type_ = type;

		start_point_ = Point (20,0, ' ');
		vector<string> text_message;

		if(holter_type_ == "EKG")
			text_message.push_back("Select object for Holter EKG:");
		else if(holter_type_ == "ABPM")
			text_message.push_back("Select object for Holter APBM:");

		text_message.push_back("Date - 1");
		text_message.push_back("Patient - 2");
		text_message.push_back("Holter device - 3");
		text_message.push_back("Signal - 4");
		text_message.push_back("Display data - 5");
		text_message.push_back("Save data - 6");
		text_message.push_back("Exit - 7");
		Text_box close_frame(50, start_point_, '_', text_message);
		frames_.push_back(close_frame);
	}

	virtual ~Form_window() { }
	virtual void display_win(){
		frames_[0].display();
		cout<<endl;
	}
};

class Date_form_window: public Window {
protected:
	Date_form_window(const Date_form_window& win) { }
	Date_form_window & operator=( const Date_form_window& win){ }
public:
	int day_ = 0;
	int month_ = 0;
	int year_ = 0;
	Date_form_window() {
		start_point_ = Point (20,0, ' ');
		vector<string> text_message;

		text_message.push_back("Enter the data in order: ");
		text_message.push_back("Day [number]");
		text_message.push_back("Month [number]");
		text_message.push_back("Year");
		Text_box close_frame(50, start_point_, '_', text_message);
		frames_.push_back(close_frame);
	}

	virtual ~Date_form_window() { }
	virtual void display_win(){
		frames_[0].display();
		cout<<endl;
	}

	void enter_data (){
		cout<<"Enter here >";
		cin>>day_;
		cout<<"Enter here >";
		cin>>month_;
		cout<<"Enter here >";
		cin>>year_;
		cout<<"Thank you"<<endl;
	}
};

class Patient_form_window: public Window {
protected:
	Patient_form_window(const Patient_form_window& win) { }
	Patient_form_window & operator=( const Patient_form_window& win){ }
public:
	string name_;
	string last_name_;
	string pesel_;
	int age_ = 0;
	int growth_ = 0;
	int weight_ = 0;

	Patient_form_window() {
		start_point_ = Point (20,0, ' ');
		vector<string> text_message;

		text_message.push_back("Enter the data in order: ");
		text_message.push_back("Name");
		text_message.push_back("Last name");
		text_message.push_back("Pesel");
		text_message.push_back("Age");
		text_message.push_back("Growth [cm]");
		text_message.push_back("Weight [kg]");
		Text_box close_frame(50, start_point_, '_', text_message);
		frames_.push_back(close_frame);
	}

	virtual ~Patient_form_window() { }
	virtual void display_win(){
		frames_[0].display();
		cout<<endl;
	}

	void enter_data (){
		cout<<"Enter here >";
		cin>>name_;
		cout<<"Enter here >";
		cin>>last_name_;
		cout<<"Enter here >";
		cin>>pesel_;
		cout<<"Enter here >";
		cin>>age_;
		cout<<"Enter here >";
		cin>>growth_;
		cout<<"Enter here >";
		cin>>weight_;
		cout<<"Thank you"<<endl;
	}
};

class Recorder_form_window: public Window {
protected:
	string holter_type_;

	Recorder_form_window(const  Recorder_form_window& win) { }
	Recorder_form_window & operator=( const  Recorder_form_window& win){ }
public:
	string producer_;
	string model_;
	int serial_number_ = 0;
	double sampling_ = 0;
	int channel_number_ = 0;
	string unit_;

	Recorder_form_window();
	Recorder_form_window(string type) {
		holter_type_ = type;
		start_point_ = Point (20,0, ' ');
		vector<string> text_message;

		text_message.push_back("Enter the data in order: ");
		text_message.push_back("Producer");
		text_message.push_back("Model");
		text_message.push_back("Serial number");
		text_message.push_back("Sampling [Hz]");
		if(holter_type_ == "EKG")
			text_message.push_back("Channel number");
		else if(holter_type_ == "ABPM")
			text_message.push_back("Unit");
		Text_box close_frame(50, start_point_, '_', text_message);
		frames_.push_back(close_frame);
	}

	virtual ~Recorder_form_window() { }
	virtual void display_win(){
		frames_[0].display();
		cout<<endl;
	}

	void enter_data (){
		cout<<"Enter here >";
		cin>>producer_;
		cout<<"Enter here >";
		cin>>model_;
		cout<<"Enter here >";
		cin>>serial_number_;
		cout<<"Enter here >";
		cin>>sampling_;
		if(holter_type_ == "EKG"){
			cout<<"Enter here >";
			cin>>channel_number_;
		}
		else if(holter_type_ == "ABPM"){
			cout<<"Enter here >";
			cin>>unit_;
		}

		cout<<"Thank you"<<endl;
	}
};

template <typename T>
class Signal_form_window: public Window {
protected:
	string sample_str;
	string time_str;
	int samples_number = 1;
	Signal_form_window(const  Signal_form_window& win) { }
	Signal_form_window & operator=( const  Signal_form_window& win){ }
public:
	vector<T> sample_;
	vector<TIME_TYPE> time_;

	Signal_form_window() {
		start_point_ = Point (20,0, ' ');
		vector<string> text_message;

		text_message.push_back("Enter the data in order: ");
		text_message.push_back("Number of samples");
		text_message.push_back("Signal sample: in one line separated by commas");
		text_message.push_back("Time sample: in one line separated by commas");
		text_message.push_back("Example: 1,2,3,4,5 ...");
		Text_box close_frame(50, start_point_, '_', text_message);
		frames_.push_back(close_frame);
	}

	virtual ~Signal_form_window() { }
	virtual void display_win(){
		frames_[0].display();
		cout<<endl;
	}

	void enter_data (){

		while(sample_.size() !=samples_number){
			cout<<"Enter here >";
			cin>>samples_number;
			cout<<"Enter here >";
			cin>>sample_str;
			sample_str.push_back(',');
			cout<<"Enter here >";
			cin>>time_str;
			time_str.push_back(',');

			string sample_word;
			string time_word;
			for(unsigned i = 0; i<samples_number; ++i){
				sample_word = find_word(sample_str, i+1);
				time_word = find_word(time_str, i+1);
				if((sample_word != "NOT WORD") | (time_word != "NOT WORD")){
					if(IsDouble(sample_word)){
						//sample_.push_back(stod(sample_word));
						//time_.push_back(stod(time_word));
						sample_.push_back(ConvertToDouble(sample_word));
						time_.push_back(ConvertToDouble(time_word));
					}
					else {
						//sample_.push_back(stoi(sample_word));
						//time_.push_back(stoi(time_word));
						sample_.push_back(atoi(sample_word.c_str()));
						time_.push_back(atoi(time_word.c_str()));
					}
				}
				else {
					cout<<"Various sizes of samples vectors!"<<endl;
					cout<<"Vectors should vectors should contain "<<samples_number<<" samples. Try again"<<endl;
					break;
				}
			}
		}
		cout<<"Thank you"<<endl;
	}
};

class Error_window: public Window {
protected:
	Error_window();
	Error_window(const Error_window& e_win) { }
	Error_window & operator=( const Error_window& e_win){ }
public:
	Error_window(string error_massage) {
	start_point_ = Point (20,0, ' ');
	vector<string> text_message;

	text_message.push_back("Exception occurred!");
	text_message.push_back(error_massage);
	Text_box error_frame(100, start_point_, '!', text_message);
	frames_.push_back(error_frame);
	}

	virtual ~Error_window() { }
	virtual void display_win(){
		frames_[0].display();
		cout<<endl;
	}
};

}

#endif /* GUI_H_ */
