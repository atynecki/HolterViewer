
/** Application service functions source file */

#include "app_service.h"

using namespace std;

string find_word(string line, int word_number)
{
	string temp;
	size_t pos_head = 0;
	size_t pos_tail = 0;
	size_t length = 0;
	for(int i = 0; i<word_number; ++i)
	{
		pos_tail = line.find(",", pos_head);
		length = pos_tail - pos_head;
		temp = line.substr(pos_head, length);
		pos_head = pos_tail+1;
	}

	return temp;
}

void PressCToContinue()
{
	char ch;
	cout << "Press 'C' to continue... " << endl;
	cin>>ch;
	ch = toupper(ch);
	while (ch != 'C'){
		cin.clear();
		cout << "Press 'C' to continue... " << endl;
		cin>>ch;
	}
 }

template<class T> string to_string(const T& t)
{
	ostringstream os;
	os << t;
	return os.str();
}
