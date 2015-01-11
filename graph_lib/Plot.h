
/** Point class header file */

#ifndef PLOT_H_
#define PLOT_H_


#include "std_lib_facilities.h"
#include "Point.h"
#include "Line.h"

namespace Graph_lib {

class Space {
public:
	unsigned width_;
	unsigned height_;

	Space(): width_(0), height_(0) { }
	Space(unsigned width,unsigned height): width_(width), height_(height) { }
};

template <typename Elt1>
class Axis {
public:
	vector<Elt1> axis_;
	unsigned lenght_;

	Axis(): lenght_(0) { }
	Axis(vector<Elt1> values) {
		lenght_ = values.size();
		axis_ = values;
	}

	Axis(const Axis& axi){
		axis_ = axi.axis_;
		lenght_ = axi.lenght_;
	}

	Axis& operator=( const Axis& axi){
		if(this !=axi){
			axis_ = axi.axis_;
			lenght_ = axi.lenght_;
		}
		return *this;
	}

	virtual ~Axis() { }
	virtual void display() = 0;
};

template <typename Elt1>
class Axis_x: public Axis <Elt1>{
public:
	char marker_ = '-';

	Axis_x(): Axis<Elt1> () { }
	Axis_x(vector<Elt1> values): Axis<Elt1>(values) { }

	Axis_x(const Axis_x& axi){
		this->axis_ = axi.axis_;
		this->lenght_ = axi.lenght_;
		marker_ = axi.marker_;
	}

	Axis_x& operator=( const Axis_x& axi){

			this->axis_ = axi.axis_;
			this->lenght_ = axi.lenght_;
			marker_ = axi.marker_;

		return *this;
	}

	virtual ~Axis_x() { }

	virtual void display(){

		for(unsigned i = 0; i<(this->lenght_); ++i){
			cout<<marker_<<marker_;
		}
		cout<<endl;

		for(unsigned i = 0; i<(this->lenght_); ++i){
			cout<<this->axis_[i]<<" ";
		}
	}
};

template <typename Elt2>
class Axis_y: public Axis <Elt2>{
public:
	char marker_ = '|';

	Axis_y(): Axis<Elt2> () { }
	Axis_y(vector<Elt2> values): Axis<Elt2>(values) { }

	Axis_y(const Axis_y& axi){
		this->axis_ = axi.axis_;
		this->lenght_ = axi.lenght_;
		marker_ = axi.marker_;
	}

	Axis_y& operator=( const Axis_y& axi){
		this->axis_ = axi.axis_;
		this->lenght_ = axi.lenght_;
		marker_ = axi.marker_;

		return *this;
	}

	virtual ~Axis_y() { }

	virtual void display(){
		for(unsigned i = 0; i<(this->lenght_); ++i){
			cout<<this->axis_[i]<<" "<<marker_<<endl;
		}
	}
};


class Label {
public:
	pair<string, string> label_;
	Label () { }
	Label (string name, string unit){
		label_.first = name;
		label_.second = unit;
	}
};

class Title {
protected:
	string title_;
	Text_box title_box_;
public:
	Title () { }
	Title (string title){
		title_box_ = Text_box(50, Point(10,0, '_'), '-', title);
	}

	void display_title (){
		title_box_.display();
	}
};

template <typename Elt1, typename Elt2>
class Plot: public Space {
public:
	vector<Line> plot_lines_;
	Axis_y <Elt1> axis_y_;
	Axis_x <Elt2> axis_x_;
	Label x_label_;
	Label y_label_;
	vector<Elt1> y_values_;
	vector<Elt2> x_values_;
	char marker_;


	Plot(): axis_x_(), axis_y_(), marker_(0){ }
	Plot(vector<Elt1> y_values, Label y_label, vector<Elt2> x_values, Label x_label, char marker)
		: marker_(marker), y_values_(y_values), x_values_(x_values), x_label_(x_label), y_label_(y_label){
		this->width_ = (x_values.size()*+1)*3+4;
		Axis_x <Elt2> axisx(x_values);
		axis_x_ = axisx;
		Axis_y <Elt1> axisy(y_values);
		axis_y_ = axisy;

		plot_lines_.push_back(Simple_text_line(width_, create_label(y_label_)));
		vector<Elt1> tmp_y_values(y_values);
		stable_sort(tmp_y_values.begin(), tmp_y_values.end());
		reverse(tmp_y_values.begin(), tmp_y_values.end());

		unsigned i = 0;
		unsigned j = 0;
		Elt1 value;
		int counter;
		int position = 0;
		vector<int> position_tab;
		while(i<tmp_y_values.size()){
			value = tmp_y_values[i];
			counter = count(tmp_y_values.begin(), tmp_y_values.end(), value);
			i+=counter;
			if(counter ==1){
				position_tab.push_back((int) ((find(y_values.begin(), y_values.end(), value))- y_values.begin())+1);
			}
			else{
				int tail = 0;
				for(j =0; j<counter; ++j) {
					position =(int) ((find(y_values.begin()+tail, y_values.end(), value))-y_values.begin()) + 1;
					position_tab.push_back(position);
					tail = position;
				}

			}

			plot_lines_.push_back(Plot_line(width_, std::to_string(value), axis_y_.marker_, position_tab, marker_));
			position_tab.clear();
		}

		plot_lines_.push_back(Sign_line(Point(4,0,'-'),width_-4,'-'));
		plot_lines_.push_back(Axis_line <Elt2> (x_values_));
		plot_lines_.push_back(Label_line (width_, create_label(x_label_)));

		this->height_ = plot_lines_.size();
	}

	string create_label (const Label& lab){
		string result;

		result = lab.label_.first;
		result += " [";
		result +=lab.label_.second;
		result += "]";

		return result;
	}

	void display_plot(){
		for(unsigned i = 0; i<height_; ++i){
			plot_lines_[i].draw();
			cout<<endl;
		}
	}
};
}

#endif /* PLOT_H_ */
