
/** Point Lines header file */

#ifndef LINE_H_
#define LINE_H_

#include "std_lib_facilities.h"
#include "Point.h"

//dopisać operatory kopiujacy i =


namespace Graph_lib {

class Line {
public:
	vector<Point> line_;
	Point start_point_;
	unsigned lenght_;
	Line(): lenght_(0) { start_point_ = Point(); }
	Line(Point start_point, int lenght): start_point_(start_point), lenght_(lenght) { }

	void draw(){
		for(unsigned i = 0; i<lenght_; ++i)
		line_[i].draw();
	}
};

class Sign_line: public Line {
public:
	char sign_;
	Sign_line(): Line(), sign_(0) { }
	Sign_line(Point start_point, int lenght, char sign): Line(start_point, lenght), sign_(sign){
		start_point.sign_ = sign_;
		line_.push_back(start_point_);
		for(unsigned i = 0; i<lenght_; ++i)
			line_.push_back(Point(0,0,sign_));
	}
};

class Middle_line: public Sign_line {
public:
	Middle_line(): Sign_line() { }
	Middle_line(Point start_point, int lenght){
		start_point_ = start_point;
		lenght_ = lenght;
		sign_ = start_point.sign_;
		line_.push_back(start_point_);
		for(unsigned i = 0; i<lenght_-2; ++i)
			line_.push_back(Point(0,0,' '));
		line_.push_back(Point(0,0,sign_));
	}

};

class Simple_text_line: public Line {
public:
	Simple_text_line(): Line() { }
	Simple_text_line(int lenght, string text) {
		if(text.size() > lenght -2)
			return;
			//throw WrongSizeError ("TEXT LONGER THEN LINE");
		lenght_ = lenght;
	for(unsigned i = 0; i<text.size(); ++i)
		line_.push_back(Point(0,0,text.at(i)));
	for(unsigned i = 0; i<(lenght_ - text.size()); ++i)
			line_.push_back(Point(0,0,' '));
	}
};

class Text_line: public Sign_line {
public:
	string text_;
	Text_line(): Sign_line() { }
	Text_line(Point start_point, int lenght, string text){
		if(text.size() > lenght -2)
			return;
			//throw WrongSizeError ("TEXT LONGER THEN LINE");
		start_point_ = start_point;
		lenght_ = lenght;
		sign_ = start_point.sign_;
		line_.push_back(start_point_);
		unsigned line_middle;
		unsigned text_middle;
		if(lenght_%2)
			line_middle = (lenght_+1)/2;
		else
			line_middle = lenght_/2;

		if(text.size()%2)
			text_middle = (text.size()+1)/2;
		else
			text_middle = text.size()/2;

		if(((lenght_%2 == 0) && (text.size()%2 == 0)) | ((lenght_%2 == 1) && (text.size()%2 == 1))){
			for(unsigned i = 0; i<line_middle - text_middle-1; ++i)
				line_.push_back(Point(0,0,' '));
			for(unsigned i = 0; i<text.size(); ++i)
				line_.push_back(Point(0,0,text.at(i)));
			for(unsigned i = 0; i<line_middle - text_middle-1; ++i)
				line_.push_back(Point(0,0,' '));
		}

		else if((lenght_%2 == 1) && (text.size()%2 == 0)){
			for(unsigned i = 0; i<line_middle - text_middle-1; ++i)
				line_.push_back(Point(0,0,' '));
			for(unsigned i = 0; i<text.size(); ++i)
				line_.push_back(Point(0,0,text.at(i)));
			for(unsigned i = 0; i<line_middle - text_middle-2; ++i)
				line_.push_back(Point(0,0,' '));
		}

		else if((lenght_%2 == 0) && (text.size()%2 == 1)){
			for(unsigned i = 0; i<line_middle - text_middle; ++i)
					line_.push_back(Point(0,0,' '));
			for(unsigned i = 0; i<text.size(); ++i)
				line_.push_back(Point(0,0,text.at(i)));
			for(unsigned i = 0; i<line_middle - text_middle-1; ++i)
				line_.push_back(Point(0,0,' '));
			}

		line_.push_back(Point(0,0,sign_));
	}
};

template <typename Elt1>
class Axis_line: public Line {
public:
	Axis_line(): Line() { }
	Axis_line(vector<Elt1> axis_value){
		string value;
		lenght_ = axis_value.size()*3+1;
		start_point_ = Point(3,0,' ');
		line_.push_back(start_point_);
		for(unsigned i = 0; i<axis_value.size(); ++i){
			value = std::to_string(axis_value[i]);
			if(value.size()==1){
				line_.push_back(Point(0,0,' '));
				line_.push_back(Point(0,0,value.at(0)));
				line_.push_back(Point(0,0,' '));
			}
			else if(value.size()==2){
				line_.push_back(Point(0,0,' '));
				line_.push_back(Point(0,0,value.at(0)));
				line_.push_back(Point(0,0,value.at(1)));
			}
			else if(value.size()==3){
				line_.push_back(Point(0,0,value.at(0)));
				line_.push_back(Point(0,0,value.at(1)));
				line_.push_back(Point(0,0,value.at(2)));
			}
		}

	}
};

class Label_line: public Text_line {
public:
	Label_line(): Text_line() { }
	Label_line(int lenght, string text){
		lenght_ = lenght;
		for(unsigned i = 0; i<lenght - text.size(); ++i)
			line_.push_back(Point(0,0,' '));
		for(unsigned i = 0; i<text.size(); ++i)
			line_.push_back(Point(0,0,text.at(i)));
	}
};

class Plot_line: public Line {
public:
	Plot_line(): Line() { }
	Plot_line(int lenght, string value, char axis_marker, vector<int> position, char point_marker){
		lenght_ = lenght;

		unsigned i;
		unsigned j;

		if(value.size() ==1){
			line_.push_back(Point(0,0,' '));
			line_.push_back(Point(0,0,' '));
		}
		else if(value.size() ==2)
			line_.push_back(Point(0,0,' '));

		for(i = 0; i<value.size(); ++i)
			line_.push_back(Point(0,0,value.at(i)));
		line_.push_back(Point(0,0,axis_marker));

		int tail_pos =0;
		for (i = 0; i<position.size(); ++i){
			for(j = 3; j<position[i]*3 - tail_pos; ++j)
				line_.push_back(Point(0,0,' '));
			line_.push_back(Point(0,0,' '));
			line_.push_back(Point(0,0,point_marker));
			line_.push_back(Point(0,0,' '));
			tail_pos = position[i]*3;
		}

		for(i = 0; i<lenght- tail_pos; ++i)
			line_.push_back(Point(0,0,' '));
	}
};
}

#endif /* LINE_H_ */
