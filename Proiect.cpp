#include <iostream>
#include <regex>
#include <string>
#include <fstream>
#include <Python.h>
#include <algorithm>

using namespace std;

char symbols[7] = { ',', '.', '!', '?', ':', ';', '-' };

void eliminateSymbol(std::string& s) {
	for (int i = 0; i <= 6; ++i)
		if (symbols[i] == s.back())
			s = s.substr(0, s.size() - 1);
}

bool BothAreSpaces(char lhs, char rhs) { return (lhs == rhs) && (lhs == ' '); }

string getText(string s, string first, string last) {

	unsigned start = s.find(first);
	unsigned end = s.find(last);
	string temp = s.substr(start, end - start);
	temp = temp.substr(temp.find_first_of(first) + first.length());

	std::string::iterator new_end = std::unique(temp.begin(), temp.end(), BothAreSpaces);

	if (temp[0] == ' ') temp.erase(0,1);

	temp.erase(new_end, temp.end()); //sterge spatiile multiple
	temp.erase(std::remove(temp.begin(), temp.end(), '\n'), temp.end()); //sterge liniile multiple

	return temp;
}

string getTextReg(string s, std::regex reg) {
	std::smatch m;
	string copy = s;
	regex_search(copy, m, reg);
	return m.str();
}

void cm(string command) {
	const char* command2 = command.c_str();
	system(command2);
}

void WordNet(string word) {
	cm("C:");
	cm("E:");
	cm("cd TILN");
	cm("cd Proiect");
	cm("cd Proiect");
	cm("cd Proiect");
	cm("python WordNet.py " + word);
}

struct article {
	std::string title;
	std::string code;
	std::string	contact;
	std::string	dataType;
	std::string	createdBy;
	std::string	createdAt;
};

struct sample {
	std::string gender;
	float sd;
	std::string nationality;
	std::string name;
	std::string createdBy;
	std::string	createdAt;
	int	size;
	article article;
	std::string	type;
	std::string	education;
	float avg;
};

struct variable {
	std::string type;
	float min;
	float max;
	float sd;
	std::string details;
	int o;
	std::string name;
	std::string createdBy;
	std::string createdAt;
	std::string sample;
	float mean;
	article article;
};

int main()
{
	std::regex articleYear1("\\b(')([A-Z][a-z]*(')([1]+[9]+[0-9]+[0-9]))");
	std::regex articleYear2("\\b(')([A-Z][a-z]*(')([2]+[0-2]+[0-9]+[0-9]))");
	std::regex year1("\\b([1]+[9]+[0-9]+[0-9])");
	std::regex year2("\\b([2]+[0-2]+[0-9]+[0-9])");
	std::regex title("\\b(')([A-Z][^] *)(')");
	std::regex name("\\b([A-Z][a-z]*)");
	std::regex e("\\b((n = )([^ ]*)())");
	std::regex e1("\\b((N = )([^ ]*)");

	string path = "poppler-0.67.0\\bin";
	string file_name = "exemplu_corelatii_3";
	string str;
	str = "cd " + path + " && pdftotext -layout -nopgbrk ..\\..\\" + file_name + ".pdf ..\\..\\" + file_name + ".txt";
	const char* command = str.c_str();
	system(command);

	fstream f(file_name + ".txt", fstream::in);
	string s;
	getline(f, s, '\0');

	f.close();



	return 0;
}
