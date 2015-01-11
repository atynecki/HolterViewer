
/** GUI class header file */

#ifndef GUI_H_
#define GUI_H_

#include "std_lib_facilities.h"
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

class Main_window: public Window {
protected:
	string holter_type_;

	Main_window(): Window() { }
	Main_window(const Main_window& w_win) { }
	Main_window & operator=( const Main_window& w_win){ }
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

}

#endif /* GUI_H_ */
