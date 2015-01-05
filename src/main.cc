
/** Main source file to test classes */

#include <iostream>
#include <string>

#include "holter.h"
#include "plot.h"

using namespace std;


int main () try
{
	ofstream plikWyj ( "plikWyj.txt" ) ;
	RecorderEKG test_recorder(3, 33245, 512, "ASPEL", "ASPEKT");
	test_recorder.write_date(plikWyj);
	plikWyj.close();
	return 0;
}

catch (...){
	cerr<< "Unexpected exception\n";
}

