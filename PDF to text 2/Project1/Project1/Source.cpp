#include <iostream>
using namespace std;

int main()
{	
	string path = "poppler-0.67.0\\bin";
	string file_name = "exemplu_raportare_corelatii2";
	string str;
	str = "cd " + path + " && pdftotext -layout -nopgbrk ..\\..\\" + file_name + ".pdf ..\\..\\" + file_name + ".txt";
	const char * command = str.c_str();
	system(command);
	return 0;
}