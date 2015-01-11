
/** Point class header file */

#ifndef POINT_H
#define POINT_H

#include "std_lib_facilities.h"

namespace Graph_lib {

class Point {
public:
	int x,y;
	char sign_;
	Point(int xx, int yy, char sign) : x(xx), y(yy), sign_(sign) { }
	Point() :x(0), y(0), sign_(0) { }


	Point(const Point& pon){
		x = pon.x;
		y = pon.y;
		sign_ = pon.sign_;
	}

	Point & operator=( const Point& pon){
		if(this !=&pon){
			x = pon.x;
			y = pon.y;
			sign_ = pon.sign_;
		}
		return *this;
	}

	void draw() {
		for (int i =0; i<y; ++i)
			cout<<endl;
		for (int j = 0;j<x; ++j)
			cout<<" ";
		cout<<sign_;
	}

	//Point& operator+=(Point d) { x+=d.x; y+=d.y; return *this; }
};

//inline bool operator==(Point a, Point b) { return a.x==b.x && a.y==b.y; }

//inline bool operator!=(Point a, Point b) { return !(a==b); }

}
#endif
