/*
 * Line.h
 *
 *  Created on: 9 sty 2015
 *      Author: tynio
 */

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

		if((lenght_%2 == 0 & text.size()%2 == 0) | (lenght_%2 == 1 & text.size()%2 == 1)){
			for(unsigned i = 0; i<line_middle - text_middle-1; ++i)
				line_.push_back(Point(0,0,' '));
			for(unsigned i = 0; i<text.size(); ++i)
				line_.push_back(Point(0,0,text.at(i)));
			for(unsigned i = 0; i<line_middle - text_middle-1; ++i)
				line_.push_back(Point(0,0,' '));
		}

		else if(lenght_%2 == 1 & text.size()%2 == 0){
			for(unsigned i = 0; i<line_middle - text_middle-1; ++i)
				line_.push_back(Point(0,0,' '));
			for(unsigned i = 0; i<text.size(); ++i)
				line_.push_back(Point(0,0,text.at(i)));
			for(unsigned i = 0; i<line_middle - text_middle-2; ++i)
				line_.push_back(Point(0,0,' '));
		}

		else if(lenght_%2 == 0 & text.size()%2 == 1){
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

}

#endif /* LINE_H_ */
