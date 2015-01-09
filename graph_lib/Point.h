
/** Point class header file */

#ifndef POINT_H
#define POINT_H

namespace Graph_lib {

class Point {
public:
	int x,y;
	Point(int xx, int yy) : x(xx), y(yy) { }
	Point() :x(0), y(0) { }

	Point& operator+=(Point d) { x+=d.x; y+=d.y; return *this; }
};

inline bool operator==(Point a, Point b) { return a.x==b.x && a.y==b.y; }

inline bool operator!=(Point a, Point b) { return !(a==b); }

}
#endif
