
/** Graphics library header file */

#ifndef PLOT_H_
#define PLOT_H_

#include "Simple_window.h"
#include "Graph.h"

using namespace Graph_lib;

class Holter_window {
protected:
	double length_;
	double width_;
	Point start_window_;
public:
	Holter_window (){
		length_ = 600;
		width_ = 400;
		start_window_(100,100);
		Simple_window win(start_window_, length_, width_, "Holter sygnal");
	}

	Holter_window (double length, double width, Point start_window){
		length_ = length;
		width_ = width;
		start_window_ = start_window;
		Simple_window win(start_window_, length_, width_, "Holter sygnal");
	}

};






#endif /* PLOT_H_ */
