
/** Main source file to test classes */

#include <iostream>
#include <string>

#include "holter.h"
#include "app_service.h"
#include "ecg_signal.h"

using namespace std;


int main () try
{

	//string str = "Artur,Tynecki,Tynio";
	//string result;
	//result = find_word(str, 3);
	//cout<<result;

	//Patient patient_1(46, 182, 102, "Jan", "Kowalski", "74023086385");
	//patient_1.set_id_number();
	//Patient patient_2;

	//Date date_1(2014,11,14);
	//Date date_0;
	//Date date_2(2014,9,1);
	//bool small_check = false;
	//small_check = date_2 < date_1;

	Signal<int, int> signal;

	//int sample_1[] = {0,2,4,6,8};
	//int time_1[] = {1,3,5,7,9};

	//vector<int> sample1 (sample_1, sample_1 + sizeof(sample_1) / sizeof(int));
	//vector<int> time1(time_1, time_1 + sizeof(time_1) / sizeof(int));
	//vector<int> sample1 (5, 4);
	//vector<int> time1 (5, 2);

	//Signal <int, int> signal1(sample1, time1);

	//signal1.show_date();
	//cout<<endl;

	vector<int> sample_2 = {1,3,5,7,9,11,13};
	vector<int> time_2 = {2,4,6,8,10,12,14};
	Signal<int, int> signal2(sample_2, time_2);

	signal2.show_date();
	cout<<endl;

	vector <int> sample_3 = {1,4,7,9,14,17,11,9};
	vector <int> time_3 = {1,2,3,4,5,6,7,8};
	Signal<int, int> signal3(sample_3, time_3);

	signal3.show_date();
	cout<<endl;

	pair<int, int> result;
	result = find_max (signal2);
	display_pair(result);

	//Signal<int, int> signal4(signal1);
	//signal = signal1;
	//signal.show_date();
	//cout<<endl;

	//ofstream plikWyj ( "test.txt" );
	//if (!plikWyj)
		//return 1;
	//ifstream plikWej ( "test.txt" );
	//if (!plikWej)
		//return 1;

	//signal1.write_date(plikWyj);
	//date_1.write_date(plikWyj);
	//signal.read_date(plikWej);

	//plikWyj.close();
	//plikWej.close();

	//cout<<date_0;
	//signal.show_date();
	return 0;
}

catch (...){
	cerr<< "Unexpected exception\n";
}

