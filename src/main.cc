
/** Main source file to test classes */

#include <iostream>
#include <string>

#include "holter.h"
#include "app_service.h"
#include "ecg_signal.h"

using namespace std;


int main () try
{


	/*RecorderEKG recorder_1(3, 6969,1024, "ASPEL", "ASPEKT");
	RecorderABPM recorder_2("mmHg", 1003, 3, "CARDIO_TASK", "CT-08");

	Patient patient_1(46, 182, 102, "Jan", "Kowalski", "74023086385");
	patient_1.set_id_number();

	Date date_1(2014,11,14);

	vector<int> sample_2 = {1,3,5,7,9,1,13};
	vector<int> time_2 = {2,4,6,8,10,12,14};
	Signal<int, int> signal2(sample_2, time_2);

	vector <int> sample_3 = {1,4,7,9,14,17,11,9};
	vector <int> time_3 = {1,2,3,4,5,6,7,8};
	Signal<int, int> signal3(sample_3, time_3);

	Signal<int, int> signal_tab[2] = {signal2, signal3};

	HolterEKG holter1(date_1, patient_1, signal_tab, recorder_1, 2);

	holter1.show_date();
	cout<<endl;

	holter1.write_date();

	HolterEKG holter2;
	holter2.read_date();
	holter2.show_date();*/

	//string str = "Artur,Tynecki,Tynio";
	//string result;
	//result = find_word(str, 3);
	//cout<<result;

	//Date date_1(2014,11,14);
	//Date date_2(2014,9,1);
	//bool small_check = false;
	//small_check = date_2 < date_1;

	//pair<int, int> result;
	//float freq;
	//freq = calculate_frequance(signal2);
	//result = find_min(signal2);
	//display_pair(result);

	return 0;
}

catch (...){
	cerr<< "Unexpected exception\n";
}

