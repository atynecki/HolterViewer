
/** Main source file to test classes */

#include <iostream>
#include <string>

#include "holter.h"
#include "app_service.h"
#include "ecg_signal.h"
#include "Point.h"
#include "Line.h"
#include "Frame.h"
#include "Plot.h"


//using namespace std;
using namespace Graph_lib;

int main () try
{
	//Label_line lline1(10, "Artur");
	//lline1.draw();
	vector<int> x = {10,20,30,40,50,60,70,80,90, 100};
	vector<int> y = {11,12,13,14,15,13,17,112,119};
	Label y_label("sample", "BPM");
	Label x_label("time", "s");
	Plot<int,int> plot1(y, y_label, x, x_label, "TEST", 'x');
	plot1.display_plot();
	//Axis_line  <int> axisx(x);
	//axisx.draw();

	//vector<int> position = {2,14,20};
	//Plot_line line4(30, "4", '|', position, 'x');
	//int size = line4.line_.size();
	//line4.draw();
	//cout<<endl;
	//Plot_line line5(30, "158", '|', position, 'x');
	//int size = line4.line_.size();
	//line5.draw();

	//Simple_text_line line3(30, "Tynio");
	//line3.draw();
	//vector<int> values = {1,2,3,4,5,6,7,8,9,10};
	///Axis_y<int> axisx(values, "time", "s");
	//axisx.display();
	//Point point1(2,2,'x');
	//Point point2(10,1,'x');
	//vector<string> text_massage;
	//text_massage.push_back("Artur");
	//text_massage.push_back("Tynecki");
	//text_massage.push_back("Tommorowland");

	//Frame frame1(20,8, point2, '|');
	//Text_box text1(40, point2, '-',text_massage);
	//Text_box text2("Artur");
	//text1.display();
	//text2.display();
	//text1 = text1<<"Hello";
	//text1.display();
	//Text_line line1(point1, 14, "Tynio");
	//line1.draw();
	//point1.draw();
	//point2.draw();

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

