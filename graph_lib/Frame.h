/*
 * Frame.h
 *
 *  Created on: 9 sty 2015
 *      Author: tynio
 */

#ifndef FRAME_H_
#define FRAME_H_

#include "std_lib_facilities.h"
#include "Point.h"
#include "Line.h"

namespace Graph_lib {

class Frame {
public:
	Point start_point_;
	vector<Line> lines_;
	unsigned width_;
	unsigned height_;
	char marker_;
	Frame(): width_(0),height_(0), marker_(0) { start_point_ = Point(); }
	Frame(int width, int height, Point start_point, char marker): width_(width), height_(height), start_point_(start_point), marker_(marker){
		start_point_.sign_ = marker_;
		lines_.push_back(Sign_line(start_point_,width_, marker_));
		for (unsigned i = 0; i<(height_-2); ++i)
			lines_.push_back(Middle_line(Point(start_point.x,1,marker_), width_));
		lines_.push_back(Sign_line(Point(start_point.x,1,marker_),width_, marker_));
	}

	Frame(const Frame& fra){
		start_point_ = fra.start_point_;
		lines_ = fra.lines_;
		width_ = fra.width_;
		height_= fra.height_;
		marker_ = fra.marker_;

	}

	Frame & operator=( const Frame& fra){
		if(this !=&fra){
			start_point_ = fra.start_point_;
			lines_ = fra.lines_;
			width_ = fra.width_;
			height_= fra.height_;
			marker_ = fra.marker_;
		}

		return *this;
	}

	void display(){
		for(unsigned i = 0; i<height_; ++i)
			lines_[i].draw();
	}

};

class Text_box: public Frame {
public:
	vector<string> text_massage_;
	unsigned text_lines_num_;
	Text_box(): Frame(), text_lines_num_(0) { }
	Text_box(string text): text_lines_num_(1){
		text_massage_.push_back(text);
		start_point_ = Point(1,1, 'x');
		width_ = text.size()+4;
		height_ = text_lines_num_+2;
		marker_ = 'x';

		lines_.push_back(Sign_line(start_point_,width_,marker_));
		for (unsigned i = 0; i<text_lines_num_; ++i)
			lines_.push_back(Text_line(Point(start_point_.x,1,marker_),width_,text_massage_.at(i)));
		lines_.push_back(Sign_line(Point(start_point_.x,1,marker_),width_,marker_));
	}

	Text_box(vector<string> text){
			text_lines_num_ = text.size();
			text_massage_ = text;

			start_point_ = Point(1,1, 'x');
			width_ = calculate_width(text)+4;
			height_ = text_lines_num_+2;
			marker_ = 'x';

			lines_.push_back(Sign_line(start_point_,width_,marker_));
			for (unsigned i = 0; i<text_lines_num_; ++i)
				lines_.push_back(Text_line(Point(start_point_.x,1,marker_),width_,text_massage_.at(i)));
			lines_.push_back(Sign_line(Point(start_point_.x,1,marker_),width_,marker_));
	}

	Text_box(int width, Point start_point, char marker, string text): text_lines_num_(1){
		if(text.size() > width -2)
			return;
			//throw WrongSizeError ("TEXT LONGER THEN LINE");

		text_massage_.push_back(text);
		start_point_ = start_point;
		start_point_.sign_ = marker;
		width_ = text.size()+4;
		height_ = text_lines_num_+2;
		marker_ = marker;

		lines_.push_back(Sign_line(start_point_,width_,marker_));
		for (unsigned i = 0; i<text_lines_num_; ++i)
			lines_.push_back(Text_line(Point(start_point_.x,1,marker_),width_,text_massage_.at(i)));
		lines_.push_back(Sign_line(Point(start_point_.x,1,marker_),width_,marker_));

	}

	Text_box(int width, Point start_point, char marker, vector<string> text){
			if(text.size() > width -2)
				return;
				//throw WrongSizeError ("TEXT LONGER THEN LINE");

			text_lines_num_ = text.size();
			text_massage_ = text;
			start_point_ = start_point;
			start_point_.sign_ = marker;
			width_ = calculate_width(text)+4;
			height_ = text_lines_num_+2;
			marker_ = marker;

			lines_.push_back(Sign_line(start_point_,width_,marker_));
			for (unsigned i = 0; i<text_lines_num_; ++i)
				lines_.push_back(Text_line(Point(start_point_.x,1,marker_),width_,text_massage_.at(i)));
			lines_.push_back(Sign_line(Point(start_point_.x,1,marker_),width_,marker_));

		}


	Text_box(const Text_box& box){
		text_massage_ = box.text_massage_;
		text_lines_num_ = box.text_lines_num_;

		start_point_ = box.start_point_;
		lines_ = box.lines_;
		width_ = box.width_;
		height_= box.height_;
		marker_ = box.marker_;

	}

	Text_box & operator=( const Text_box& box){
		if(this !=&box){
			start_point_ = box.start_point_;
			lines_ = box.lines_;
			width_ = box.width_;
			height_= box.height_;
			marker_ = box.marker_;
		}

		return *this;
	}

	int calculate_width (vector<string> text){
		vector<int> size_of_text;
		int result;
		for (unsigned i=0; i<text.size(); ++i){
			size_of_text.push_back(text[i].size());
		}
		result = (int) (*max_element(size_of_text.begin(),size_of_text.end()));

		return result;
	}

	Text_box operator<<(string text)const{
		vector<string> add_text(this->text_massage_);
		add_text.push_back(text);
		Text_box tmp(this->width_,this->start_point_, this->marker_, add_text);

		return tmp;
	}
};
}

#endif /* FRAME_H_ */
