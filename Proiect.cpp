#include <iostream>
#include <regex>
#include <string>
#include <fstream>
#include <algorithm>
#include <stdio.h>
#include "SQLite3.h"


using namespace std;

char symbols[7] = { ',', '.', '!', '?', ':', ';', '-' };

void eliminateSymbol(std::string& s) {
	for (int i = 0; i <= 6; ++i)
		if (symbols[i] == s.back())
			s = s.substr(0, s.size() - 1);
}

bool is_number(const std::string& s)
{
	std::string::const_iterator it = s.begin();
	while (it != s.end() && std::isdigit(*it)) ++it;
	return !s.empty() && it == s.end();
}

bool BothAreSpaces(char lhs, char rhs) { return (lhs == rhs) && (lhs == ' '); }


std::string ExtractString(std::string source, std::string start, std::string end)
{
	std::size_t startIndex = source.find(start);

	if (startIndex == std::string::npos) return "";

	startIndex += start.length();

	std::string::size_type endIndex = source.find(end, startIndex);

	if (endIndex == std::string::npos) return "";

	string temp =  source.substr(startIndex, endIndex - startIndex);

	std::string::iterator new_end = std::unique(temp.begin(), temp.end(), BothAreSpaces);

	if (temp[0] == ' ') temp.erase(0, 1);

	temp.erase(new_end, temp.end()); //sterge spatiile multiple
	//temp.erase(std::replace(temp.begin(), temp.end(), '\n', ' '), temp.end()); //sterge liniile multiple
	std::replace(temp.begin(), temp.end(), '\n', ' ');
	return temp;
}

string getTextReg(string s, std::regex reg) {
	std::smatch m;
	string copy = s;
	while (regex_search(copy, m, reg)) {
		for (auto x : m) return x;
	}
	return "";
}

std::regex numberReg("\\b([0-9]+)");
std::regex numberReg2("\\b([0-9]+(,)[0-9+])");

/*string getNumber(string s) {
	string temp;
	if (getTextReg(s, numberReg) != "") return getTextReg(s, numberReg);
	if (getTextReg(s, numberReg2) != "") {
		temp = getTextReg(s, numberReg2);
		std::replace(temp.begin(), temp.end(), '\n', ' ');
	}
}*/

void cm(string command) {
	const char* command2 = command.c_str();
	system(command2);
}

void WordNet(string word) {
	cm("C:");
	cm("D:");
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

void Init(article Article, sample Sample, variable Variable) {
	Variable.article = Article;
	Sample.article = Article;
	Article.title = "";
	Article.code = "";
	Article.contact = "";
	Article.dataType = "";
	Article.createdBy = "";
	Article.createdAt = "";
	Sample.gender = "";
	Sample.sd = 0;
	Sample.nationality = "";
	Sample.name = "";
	Sample.createdBy = "";
	Sample.createdAt = "";
	Sample.size = 0;
	Sample.article = Article;
	Sample.type = "";
	Sample.education = "";
	Sample.avg = 0;
	Variable.type="";
	Variable.min=0;
	Variable.max=0;
	Variable.sd=0;
	Variable.details="";
	Variable.o=0;
	Variable.name="";
	Variable.createdBy="";
	Variable.createdAt="";
	Variable.sample="";
	Variable.mean=0;
	Variable.article = Article;
}

int Snumber = 0;
int age1 = 0;
int age2 = 0;


void Subjects(string subjects) {

	std::regex r1("\\b([0-9]+( participants))");
	std::regex r2("\\b([0-9]+( men and women))");
	std::regex r3("\\b([0-9]+( individuals))");
	std::regex r4("\\b([0-9]+( students))");
	std::regex r5("\\b([0-9]+( were women))");
	std::regex r6("\\b([0-9]+( were men))");
	std::regex r7("\\b([0-9]+( responses were returned))");
	std::regex r8("\\b((age from )[0-9]+( to )[0-9]+)");
	std::regex r9("\\b((from )[0-9]+)");
	std::regex r10("\\b((to )[0-9]+)");
	std::regex r11("\\b((from )[0-9]+( years old to )[0-9]+)");
	std::regex r12("\\b((from )[0-9]+( to )[0-9]+( years))");
	std::regex r13("\\b([0-9]+( )([A-Z][a-z])*( students))");
	std::regex r14("\\b((ages )[0-9]+( to )[0-9]+)");
	std::regex r15("\\b((ages )[0-9]+)");
	std::regex r16("\\b((between )[0-9]+( and )[0-9]+( years))");
	std::regex r17("\\b((between )[0-9]+)");
	std::regex r18("\\b(( and )[0-9]+( years))");
	std::regex r19("\\b([0-9]+( finished))");
	std::regex r20("\\b([0-9]+( returned))");
	/*std::regex r21("\\b([0-9]+( men and))");
	std::regex r22("\\b([0-9]+( women and )[0-9]+( men))");
	std::regex r23("\\b([0-9]+( men))");
	std::regex r24("\\b([0-9]+( women))");*/
	std::regex r25("\\b((sample of )[0-9]+( target))");


	int Snumber1 = 0, Snumber2 = 0;
	string age;
	string tempString;
	string tempString2;
	string tempString3;
	string tempString4;
	int ageMin = 999;
	int ageMax = 0;


	if (is_number(ExtractString(subjects, "(N = ", ")")))
	{
		Snumber = stoi(ExtractString(subjects, "(N = ", ")"));
	}

	if (is_number(ExtractString(subjects, "(N = ", " )")))
	{
		Snumber = stoi(ExtractString(subjects, "(N = ", " )"));
	}

	if (is_number(ExtractString(subjects, "(N=", ")")))
	{
		Snumber = stoi(ExtractString(subjects, "(N = ", ")"));
	}


	if (is_number(ExtractString(subjects, "(N= ", ")")))
	{
		Snumber = stoi(ExtractString(subjects, "(N= ", ")"));
	}

	if (is_number(ExtractString(subjects, "(n = ", ")")))
	{
		Snumber = stoi(ExtractString(subjects, "(n = ", ")"));
	}

	if (is_number(ExtractString(subjects, "(n = ", " )")))
	{
		Snumber = stoi(ExtractString(subjects, "(n = ", " )"));
	}

	if (is_number(ExtractString(subjects, "(n=", ")")))
	{
		Snumber = stoi(ExtractString(subjects, "(n=", ")"));
	}

	if (is_number(ExtractString(subjects, "(n= ", ")")))
	{
		Snumber = stoi(ExtractString(subjects, "(n= ", ")"));
	}

	tempString = getTextReg(subjects, r1);
	if (tempString != "") Snumber = stoi(getTextReg(tempString, numberReg));

	tempString = getTextReg(subjects, r2);
	if (tempString != "") Snumber = stoi(getTextReg(tempString, numberReg));

	tempString = getTextReg(subjects, r3);
	if (tempString != "") Snumber = stoi(getTextReg(tempString, numberReg));

	tempString = getTextReg(subjects, r4);
	if (tempString != "") Snumber = stoi(getTextReg(tempString, numberReg));

	tempString = getTextReg(subjects, r25);
	if (tempString != "") Snumber = stoi(getTextReg(tempString, numberReg));

	tempString = getTextReg(subjects, r5);
	if (tempString != "") {
		Snumber1 = stoi(getTextReg(tempString, numberReg));
		tempString2 = getTextReg(subjects, r6);
		if (tempString2 != "")
			Snumber2 = stoi(getTextReg(tempString2, numberReg));
		Snumber = Snumber1 + Snumber2;
	}

	tempString = getTextReg(subjects, r7);
	if (tempString != "") Snumber = stoi(getTextReg(tempString, numberReg));

	if (is_number(ExtractString(subjects, "number of ", " participants")))
		Snumber = stoi(ExtractString(subjects, "number of ", " participants"));

	if (is_number(ExtractString(subjects, "number of ", " individuals")))
		Snumber = stoi(ExtractString(subjects, "number of ", " individuals"));

	if (is_number(ExtractString(subjects, "a sample of ", " participants")))
		Snumber = stoi(ExtractString(subjects, "a sample of ", " participants"));

	if (is_number(ExtractString(subjects, "a pool of ", " items")))
		Snumber = stoi(ExtractString(subjects, "a pool of ", " items"));

	if (is_number(ExtractString(subjects, "a sample of ", " target participants")))
		Snumber = stoi(ExtractString(subjects, "a sample of ", " target participants"));


	if (ExtractString(subjects, "ges ranged ", " years") != "") {
		age = ExtractString(subjects, "ges ranged ", " years");
		age1 = stoi(ExtractString(age, "between ", " and"));
		tempString = "and ";
		age2 = stoi(age.substr(age.find(tempString) + tempString.length()));
		if (age1 < ageMin) ageMin = age1;
		if (age2 > ageMax) ageMax = age2;
	}

	if (getTextReg(subjects, r8) != "") {
		age = getTextReg(subjects, r8);
		tempString = getTextReg(age, r9);
		tempString2 = getTextReg(age, r10);
		if (tempString != "") tempString3 = getTextReg(tempString, numberReg);
		if (tempString2 != "") tempString4 = getTextReg(tempString2, numberReg);
		if (tempString3 != "") age1 = stoi(tempString3);
		if (tempString4 != "") age2 = stoi(tempString4);
		if (age1 < ageMin) ageMin = age1;
		if (age2 > ageMax) ageMax = age2;
	}

	if (getTextReg(subjects, r11) != "") {
		age = getTextReg(subjects, r11);
		tempString = getTextReg(age, r9);
		tempString2 = getTextReg(age, r10);
		if (tempString != "") tempString3 = getTextReg(tempString, numberReg);
		if (tempString2 != "") tempString4 = getTextReg(tempString2, numberReg);
		if (tempString3 != "") age1 = stoi(tempString3);
		if (tempString4 != "") age2 = stoi(tempString4);
		if (age1 < ageMin) ageMin = age1;
		if (age2 > ageMax) ageMax = age2;
	}

	if (getTextReg(subjects, r12) != "") {
		age = getTextReg(subjects, r12);
		tempString = getTextReg(age, r9);
		tempString2 = getTextReg(age, r10);
		if (tempString != "") tempString3 = getTextReg(tempString, numberReg);
		if (tempString2 != "") tempString4 = getTextReg(tempString2, numberReg);
		if (tempString3 != "") age1 = stoi(tempString3);
		if (tempString4 != "") age2 = stoi(tempString4);
		if (age1 < ageMin) ageMin = age1;
		if (age2 > ageMax) ageMax = age2;
	}
	/*if (getTextReg(subjects, r13) != "") {
		tempString = getTextReg(subjects, r13);
		Snumber = stoi(getTextReg(tempString, numberReg));
	}
	if (getTextReg(subjects, r14) != "") {
		age = getTextReg(subjects, r14);
		tempString = getTextReg(age, r15);
		tempString2 = getTextReg(age, r10);
		if (tempString != "") tempString3 = getTextReg(tempString, numberReg);
		if (tempString2 != "") tempString4 = getTextReg(tempString2, numberReg);
		if (tempString3 != "") age1 = stoi(tempString3);
		if (tempString4 != "") age2 = stoi(tempString4);
		if (age1 < ageMin) ageMin = age1;
		if (age2 > ageMax) ageMax = age2;
	}

	if (getTextReg(subjects, r16) != "") {
		age = getTextReg(subjects, r16);
		tempString = getTextReg(age, r17);
		tempString2 = getTextReg(age, r18);
		if (tempString != "") tempString3 = getTextReg(tempString, numberReg);
		if (tempString2 != "") tempString4 = getTextReg(tempString2, numberReg);
		if (tempString3 != "") age1 = stoi(tempString3);
		if (tempString4 != "") age2 = stoi(tempString4);
		if (age1 < ageMin) ageMin = age1;
		if (age2 > ageMax) ageMax = age2;
	}*/

	if (getTextReg(subjects, r19) != "") Snumber = stoi(getTextReg(getTextReg(subjects, r19), numberReg));
	if (getTextReg(subjects, r20) != "") Snumber = stoi(getTextReg(getTextReg(subjects, r20), numberReg));

	age1 = ageMin;
	if (age1 == 999) age1 = 0;
	age2 = ageMax;
}

string title(string s) {

	string temp = "";
	if (ExtractString(s, "Article", "Abstract") != "") return ExtractString(s, "Article", "Abstract");
	if (ExtractString(s, "Research Report", "ABSTRACT") != "") return ExtractString(s, "Research Report", "ABSTRACT");
	if (ExtractString(s, "paid", "a r t i c l e") != "") return ExtractString(s, "paid", "a r t i c l e");
	if (ExtractString(s, "jocrd", "A B S T R A C T") != "") return ExtractString(s, "jocrd", "A B S T R A C T");
	if (ExtractString(s, "Brief report", "Abstract") != "") return ExtractString(s, "Brief report", "Abstract");
	if (ExtractString(s, "jrp", "a r t i c l e") != "") return ExtractString(s, "jrp", "a r t i c l e");
	if (ExtractString(s, "paid", "A R T I C LE I N FO") != "") return ExtractString(s, "paid", "A R T I C LE I N FO");
	if (ExtractString(s, "plc", "(") != "") return ExtractString(s, "plc", "(");

	std::regex r1("\\b([0-9]+[\character]+( ABSTRACT))");
	std::regex r2("\\b([\character]+( ABSTRACT))");

	if (getTextReg(s, r1) != "") {
		temp = getTextReg(s, r1);
		return temp;
	
	}
	return s.substr(0, 500);
}

string getNationalities(string s1) {
	string final = "";
	string Nationalities[] = { " Afghanistan ", " Afghan ",
		" Albania ", " Albanian ",
		" Algeria ", 	" Algerian ",
		" Argentina ", 	" Argentine ",
		" Australia ", 	" Australian ",
		" Austria ", 	" Austrian ",
		" Bangladesh ", 	" Bangladeshi ",
		" Belgium ", 	" Belgian ",
		" Bolivia ", 	" Bolivian ",
		" Botswana ", 	" Batswana ",
		" Brazil ", 	" Brazilian ",
		" Bulgaria ", 	" Bulgarian ",
		" Cambodia ", 	" Cambodian ",
		" Cameroon ", 	" Cameroonian ",
		" Canada ", 	" Canadian ",
		" Chile ", 	" Chilean ",
		" China ", 	" Chinese ",
		" Colombia ", " Colombian ",
		" Costa Rica ", 	" Costa Rican ",
		" Croatia ", 	" Croatian ",
		" Cuba ", 	" Cuban ",
		" Czech Republic ", 	" Czech ",
		" Denmark ", 	" Danish ",
		" Dominican Republic ", 	" Dominican ",
		" Ecuador ", 	" Ecuadorian ",
		" Egypt ", 	" Egyptian ",
		" El Salvador ", 	" Salvadorian ",
		" England ", 	" English ",
		" Estonia ",	" Estonian ",
		" Ethiopia ", 	" Ethiopian ",
		" Fiji ", 	" Fijian ",
		" Finland ", 	" Finnish ",
		" France ",	" French ",
		" Germany ",	" German ",
		" Ghana ", 	" Ghanaian ",
		" Greece ", 	" Greek ",
		" Guatemala ", 	" Guatemalan ",
		" Haiti ", 	" Haitian ",
		" Honduras ", 	" Honduran ",
		" Hungary ",	" Hungarian ",
		" Iceland ", 	" Icelandic ",
		" India ", 	" Indian ",
		" Indonesia ", 	" Indonesian ",
		" Iran ", 	" Iranian ",
		" Iraq ", 	" Iraqi ",
		" Ireland ", 	" Irish ",
		" Israel ", 	" Israeli ",
		" Italy ", 	" Italian ",
		" Jamaica ", 	" Jamaican ",
		" Japan ", 	" Japanese ",
		" Jordan ", 	" Jordanian ",
		" Kenya ", 	" Kenyan ",
		" Kuwait ", 	" Kuwaiti ",
		" Laos ", 	" Lao ",
		" Latvia ", 	" Latvian ",
		" Lebanon ", 	" Lebanese ",
		" Libya ", 	" Libyan ",
		" Lithuania ", 	" Lithuanian ",
		" Madagascar ", 	" Malagasy ",
		" Malaysia ", 	" Malaysian ",
		" Mali ", 	" Malian ",
		" Malta ", 	" Maltese ",
		" Mexico ", 	" Mexican ",
		" Mongolia ", 	" Mongolian ",
		" Morocco ", 	" Moroccan ",
		" Mozambique ", 	" Mozambican ",
		" Namibia ", 	" Namibian ",
		" Nepal ", 	" Nepalese ",
		" Netherlands ", 	" Dutch ",
		" New Zealand ", 	" New Zealand ",
		" Nicaragua ", 	" Nicaraguan ",
		" Nigeria ", 	" Nigerian ",
		" Norway ", 	" Norwegian ",
		" Pakistan ", 	" Pakistani ",
		" Panama ",	" Panamanian ",
		" Paraguay ", 	" Paraguayan ",
		" Peru ", 	" Peruvian ",
		" Philippines ", 	" Philippine ",
		" Poland ", 	" Polish ",
		" Portugal ", 	" Portuguese ",
		" Romania ", 	" Romanian ",
		" Russia ", 	" Russian ",
		" Saudi Arabia ", 	" Saudi ",
		" Scotland ", 	" Scottish ",
		" Senegal ",	" Senegalese ",
		" Serbia ", 	" Serbian ",
		" Singapore ",	" Singaporean ",
		" Slovakia ", 	" Slovak ",
		" South Africa ", 	" South African ",
		" South Korea ", 	" Korean ",
		" Spain ",	" Spanish ",
		" Sri Lanka ", 	" Sri Lankan ",
		" Sudan ", 	" Sudanese ",
		" Sweden ", 	" Swedish ",
		" Switzerland ", 	" Swiss ",
		" Syria ", 	" Syrian ",
		" Taiwan ",	" Taiwanese ",
		" Tajikistan ", 	" Tajikistani ",
		" Thailand ", 	" Thai ",
		" Tonga ", 	" Tongan ",
		" Tunisia ", 	" Tunisian ",
		" Turkey ", " Turkish ",
		" Ukraine ", 	" Ukrainian ",
		" United Arab Emirates ", 	" Emirati ",
		" United Kingdom ", 	" British ",
		" United States ", 	" American ",
		" Uruguay ", 	" Uruguayan ",
		" Venezuela ", 	" Venezuelan ",
		" Vietnam ", 	" Vietnamese ",
		" Wales ", 	" Welsh ",
		" Zambia ", 	" Zambian ",
		" Zimbabwe ", " Zimbabwean "
		" Africa ", " African ",
		" Black African ", " Black African ",
		" Asian American ", " Asian American ",
		" Asia ", " Asian ", 
		" Europe ", " European ", };

	/*std::regex r1("\\b((participants were Black African))");
	std::regex r2("\\b((participants were Asian American))");
	std::regex r3("\\b((participants were )[A-Z][a-z]+)");
	std::regex r4("\\b((Black African students))");
	std::regex r5("\\b((Asian American students))");
	std::regex r6("\\b([A-Z][a-z]+( students))");
	std::regex r7("\\b((substantial proportions of )(Asian American))");
	std::regex r8("\\b((substantial proportions of )(Black African))");
	std::regex r9("\\b((substantial proportions of )[A-Z][a-z]+)");
    std::regex r13("\\b((respondents were )(Asian American))");
	std::regex r14("\\b((respondents were )(Black African))");
	std::regex r15("\\b((respondents were )[A-Z][a-z]+)");
	std::regex r10("\\b((Black African))");
	std::regex r11("\\b((Asian American))");
	std::regex r12("\\b([A-Z][a-z]+)");

	if (getTextReg(s1, r1) != "") return getTextReg(getTextReg(s1, r1), r10); //return; }
	if (getTextReg(s1, r2) != "") return getTextReg(getTextReg(s1, r2), r11); //return; }
	if (getTextReg(s1, r4) != "") return getTextReg(getTextReg(s1, r4), r10); //return; }
	if (getTextReg(s1, r5) != "") return getTextReg(getTextReg(s1, r5), r11);// return; }
	if (getTextReg(s1, r7) != "") return getTextReg(getTextReg(s1, r7), r10); //return; }
	if (getTextReg(s1, r8) != "") return getTextReg(getTextReg(s1, r8), r10); //return; }
	if (getTextReg(s1, r3) != "") return getTextReg(getTextReg(s1, r3), r12);// return; }
	if (getTextReg(s1, r6) != "") return getTextReg(getTextReg(s1, r6), r12); //return; }
	if (getTextReg(s1, r9) != "") return getTextReg(getTextReg(s1, r9), r12);// return; }
	if (getTextReg(s1, r13) != "") return getTextReg(getTextReg(s1, r13), r11);// return; }
	if (getTextReg(s1, r14) != "") return getTextReg(getTextReg(s1, r14), r10); //return; }
	if (getTextReg(s1, r15) != "") return getTextReg(getTextReg(s1, r15), r12);// return; }
	return "";*/

	for (int i = 0; i <= 231; i = i + 2) {
		if (s1.find(Nationalities[i]) != std::string::npos or s1.find(Nationalities[i + 1]) != std::string::npos)
			if (i % 2 == 0) final = final + " " + Nationalities[i + 1];
			else final = final + Nationalities[i];
	}
	return final;
}

string Nationalities(string s) {


	string participants = ExtractString(s, "Abstract", "Keywords");

	if (participants == "") {

		participants = ExtractString(s, "ubjects", "Study 2");
	}

	if (participants == "") {

		participants = ExtractString(s, "2.1.2. Participants", "2.2. Results");
	}

	if (participants == "") {

		participants = ExtractString(s, "Participants", "Targets and informants");
	}

	if (participants == "") {

		participants = ExtractString(s, "Participants", "Measures");
	}

	if (participants == "") {

		participants = ExtractString(s, "ABSTRACT", "INTRODUCTION");
	}

		return getNationalities(participants);
}

string Variables(string s) {
	std::regex r1("\\b((correlations between )[A-Za-z]+( )[A-Za-z]+( and )[A-Za-z]+( )[A-Za-z]+)");
	std::regex r2("\\b((association between )[A-Za-z]+( )[A-Za-z]+( and )[A-Za-z]+)( )[A-Za-z]+");
	std::regex r3("\\b([a-z]+( )[A-Za-z]+ ( and ) [A-Za-z]+( )[A-Za-z]+ ( were correlated))");
	std::regex r4("\\b([a-z]+( )[A-Za-z]+ ( robuslty correlated with ) [A-Za-z]+( )[A-Za-z]+)");
	std::regex r5("\\b([a-z]+( )[A-Za-z]+ ( correlated strongly with ) [A-Za-z]+( )[A-Za-z]+)");
	std::regex r6("\\b((relationship among ) [A-Za-z]+( )[A-Za-z]+ ( and ) [A-Za-z]+( )[A-Za-z]+)");
	std::regex r7("\\b((relationship between ) [A-Za-z]+( )[A-Za-z]+ ( and ) [A-Za-z]+( )[A-Za-z]+)");
	std::regex r8("\\b([a-z]+( )[A-Za-z]+ ( correlated strongly with ) [A-Za-z]+( )[A-Za-z]+)");
	std::regex r9("\\b([a-z]+ ((, ) [A-Za-z]+)* ( were all ) ([A-Za-z]+( ))* (associated with) [A-Za-z]+)");
	std::regex r10("\\b([a-z]+ (( )[A-Za-z]+)* ( associated with ) [A-Za-z]+)");
	std::regex r11("\\b((relationship between ) [A-Za-z]+( )[A-Za-z]+ ( and )[A-Za-z]+( )[A-Za-z]+)");
	std::regex r12("\\b([A-Za-z]+( )[A-Za-z]+ (was correlated with )[A-Za-z]+( )[A-Za-z]+)");
	std::regex r13("\\b([A-Za-z]+( )[A-Za-z]+ (were correlated with )[A-Za-z]+( )[A-Za-z]+)");
	std::regex r14("\\b((relations between) [A-Za-z]+( )[A-Za-z]+ ( and ) [A-Za-z]+( )[A-Za-z]+)");

	std::regex r15("\\b((correlations between )[A-Za-z]+( and )[A-Za-z]+( )[A-Za-z]+)");
	std::regex r16("\\b((association between )[A-Za-z]+( and )[A-Za-z]+( )[A-Za-z]+)");
	std::regex r17("\\b([a-z]+ ( and ) [A-Za-z]+( )[A-Za-z]+ ( were correlated))");
	std::regex r18("\\b([a-z]+ ( robuslty correlated with ) [A-Za-z]+( )[A-Za-z]+)");
	std::regex r19("\\b([a-z]+ ( correlated strongly with ) [A-Za-z]+( )[A-Za-z]+)");
	std::regex r20("\\b((relationship among ) [A-Za-z]+ ( and ) [A-Za-z]+)( )[A-Za-z]+");
	std::regex r21("\\b((relationship between ) [A-Za-z]+ ( and ) [A-Za-z]+)( )[A-Za-z]+");
	std::regex r22("\\b([a-z]+( )[A-Za-z]+ ( correlated strongly with ) [A-Za-z]+)( )[A-Za-z]+");
	std::regex r23("\\b([a-z]+ ((, ) [A-Za-z]+)* ( were all ) ([A-Za-z]+( ))* (associated with) [A-Za-z]+)");
	std::regex r24("\\b([a-z]+ (( )[A-Za-z]+)* ( associated with ) [A-Za-z]+)");
	std::regex r25("\\b((relationship between ) [A-Za-z]+ ( and )[A-Za-z]+( )[A-Za-z]+)");
	std::regex r26("\\b([A-Za-z]+ (was correlated with )[A-Za-z]+( )[A-Za-z]+)");
	std::regex r27("\\b([A-Za-z]+ (were correlated with )[A-Za-z]+( )[A-Za-z]+)");
	std::regex r28("\\b((relations between) [A-Za-z]+ ( and ) [A-Za-z]+( )[A-Za-z]+)");

	std::regex r29("\\b((correlations between )[A-Za-z]+( )[A-Za-z]+( and )[A-Za-z]+)");
	std::regex r30("\\b((association between )[A-Za-z]+( )[A-Za-z]+( and )[A-Za-z]+)");
	std::regex r31("\\b([a-z]+ ( and ) [A-Za-z]+( )[A-Za-z]+ ( were correlated))");
	std::regex r32("\\b([a-z]+( )[A-Za-z]+ ( robuslty correlated with ) [A-Za-z]+)");
	std::regex r33("\\b([a-z]+( )[A-Za-z]+ ( correlated strongly with ) [A-Za-z]+)");
	std::regex r34("\\b((relationship among ) [A-Za-z]+( )[A-Za-z]+ ( and ) [A-Za-z]+)");
	std::regex r35("\\b((relationship between ) [A-Za-z]+( )[A-Za-z]+ ( and ) [A-Za-z]+)");
	std::regex r36("\\b([a-z]+( )[A-Za-z]+ ( correlated strongly with ) [A-Za-z]+)");
	std::regex r37("\\b([a-z]+ ((, ) [A-Za-z]+)* ( were all ) ([A-Za-z]+( ))* (associated with) [A-Za-z]+)");
	std::regex r38("\\b([a-z]+ (( )[A-Za-z]+)* ( associated with ) [A-Za-z]+)");
	std::regex r39("\\b((relationship between ) [A-Za-z]+( )[A-Za-z]+ ( and )[A-Za-z]+)");
	std::regex r40("\\b([A-Za-z]+( )[A-Za-z]+ (was correlated with )[A-Za-z]+)");
	std::regex r41("\\b([A-Za-z]+( )[A-Za-z]+ (were correlated with )[A-Za-z]+)");
	std::regex r42("\\b((relations between) [A-Za-z]+( )[A-Za-z]+ ( and ) [A-Za-z]+)");

	std::regex r43("\\b((correlations between )[A-Za-z]+( and )[A-Za-z]+)");
	std::regex r44("\\b((association between )[A-Za-z]+( and )[A-Za-z]+)");
	std::regex r45("\\b([a-z]+ ( and ) [A-Za-z]+ ( were correlated))");
	std::regex r46("\\b([a-z]+ ( robuslty correlated with ) [A-Za-z]+)");
	std::regex r47("\\b([a-z]+ ( correlated strongly with ) [A-Za-z]+)");
	std::regex r48("\\b((relationship among ) [A-Za-z]+ ( and ) [A-Za-z]+)");
	std::regex r49("\\b((relationship between ) [A-Za-z]+ ( and ) [A-Za-z]+)");
	std::regex r50("\\b([a-z]+ ( correlated strongly with ) [A-Za-z]+)");
	std::regex r51("\\b([a-z]+ ((, ) [A-Za-z]+)* ( were all ) ([A-Za-z]+( ))* (associated with) [A-Za-z]+)");
	std::regex r52("\\b([a-z]+ (( )[A-Za-z]+)* ( associated with ) [A-Za-z]+)");
	std::regex r53("\\b((relationship between ) [A-Za-z]+ ( and )[A-Za-z]+)");
	std::regex r54("\\b([A-Za-z]+ (was correlated with )[A-Za-z]+)");
	std::regex r55("\\b([A-Za-z]+ (were correlated with )[A-Za-z]+)");
	std::regex r56("\\b((relations between) [A-Za-z]+ ( and ) [A-Za-z]+)");
	
	string variables = "";
	variables = getTextReg(s, r1);
	if (variables == "") variables = getTextReg(s, r2);
	if (variables == "") variables = getTextReg(s, r3);
	if (variables == "") variables = getTextReg(s, r4);
	if (variables == "") variables = getTextReg(s, r5);
	if (variables == "") variables = getTextReg(s, r6);
	if (variables == "") variables = getTextReg(s, r7);
	if (variables == "") variables = getTextReg(s, r8);
	if (variables == "") variables = getTextReg(s, r9);
	if (variables == "") variables = getTextReg(s, r10);
	if (variables == "") variables = getTextReg(s, r11);
	if (variables == "") variables = getTextReg(s, r12);
	if (variables == "") variables = getTextReg(s, r13);
	if (variables == "") variables = getTextReg(s, r14);

	if (variables == "") variables = getTextReg(s, r15);
	if (variables == "") variables = getTextReg(s, r16);
	if (variables == "") variables = getTextReg(s, r17);
	if (variables == "") variables = getTextReg(s, r18);
	if (variables == "") variables = getTextReg(s, r19);
	if (variables == "") variables = getTextReg(s, r20);
	if (variables == "") variables = getTextReg(s, r21);
	if (variables == "") variables = getTextReg(s, r22);
	if (variables == "") variables = getTextReg(s, r23);
	if (variables == "") variables = getTextReg(s, r24);
	if (variables == "") variables = getTextReg(s, r25);
	if (variables == "") variables = getTextReg(s, r26);
	if (variables == "") variables = getTextReg(s, r27);

	if (variables == "") variables = getTextReg(s, r28);
	if (variables == "") variables = getTextReg(s, r29);
	if (variables == "") variables = getTextReg(s, r30);
	if (variables == "") variables = getTextReg(s, r31);
	if (variables == "") variables = getTextReg(s, r32);
	if (variables == "") variables = getTextReg(s, r33);
	if (variables == "") variables = getTextReg(s, r34);
	if (variables == "") variables = getTextReg(s, r35);
	if (variables == "") variables = getTextReg(s, r36);
	if (variables == "") variables = getTextReg(s, r37);
	if (variables == "") variables = getTextReg(s, r38);
	if (variables == "") variables = getTextReg(s, r39);
	if (variables == "") variables = getTextReg(s, r40);

	if (variables == "") variables = getTextReg(s, r41);
	if (variables == "") variables = getTextReg(s, r42);
	if (variables == "") variables = getTextReg(s, r43);
	if (variables == "") variables = getTextReg(s, r44);
	if (variables == "") variables = getTextReg(s, r45);
	if (variables == "") variables = getTextReg(s, r46);
	if (variables == "") variables = getTextReg(s, r47);
	if (variables == "") variables = getTextReg(s, r48);
	if (variables == "") variables = getTextReg(s, r49);
	if (variables == "") variables = getTextReg(s, r50);
	if (variables == "") variables = getTextReg(s, r51);
	if (variables == "") variables = getTextReg(s, r52);
	if (variables == "") variables = getTextReg(s, r53);

	if (ExtractString(s, "The study aims to examining ", ".") != "") variables = ExtractString(s, "The study aims to examining ", ".");
	if (ExtractString(s, "The relationship between ", " was") != "") variables = ExtractString(s, "The relationship between ", " was");
	if (ExtractString(s, "The relationship between ", ".") != "") variables = ExtractString(s, "The relationship between ", ".");
	
	if (s.find(" Big Five ") != std::string::npos and variables == "") variables = "Something about Big Five";
	return variables;

	/*   
ABSTACT -next section is- Introduction

    relationship among x and y
    correlation between x and y
    a,b,c were all significantly associated with x
    correlations between x and y 

Introduction -next section is- Method
    x associated with y
    relationship between x and y
    x has been associated with y
    x significantly associated with y
Introduction -next section is- Theoretical background and hypotheses
    relationship between x and y

Results -next sesion is- Descriptive statistics
    correlations between x and y

Correlations -next section is- Regression
    correlations between x and y
Correlational analysis -next section is- Structural equation modelling
    the two extraversion sub-factors were inter-correlated
    x were modestly but significantly associated with y
    x was significantly and positively associated with y

SUMMARY next section is CONCEPTUALIZING FACETS OF AGREEABLENESS AND CONSCIENTIOUSNESS
    correlations of the x with y

First pilot study: A and C facet scales -next section is- Second pilot study: revisions of N, E, and O facets 
    correlations of the x with y
    correlations between x and y
Result and discussion -next section is- Method
    correlations between x and y

*/

}

float SD(string s) {
	std::regex r1("\\b([0-9]+(.)[0-9]+)");
	std::regex r2("\\b((SD = )[0-9]+(.)[0-9]+)");
	std::regex r3("\\b((SD=)[0-9]+(.)[0-9]+)");
	std::regex r4("\\b((sd = )[0-9]+(.)[0-9]+)");
	std::regex r5("\\b((sd=)[0-9]+(.)[0-9]+)");

	if (getTextReg(s, r2) !="") return stof(getTextReg(getTextReg(s, r2), r1));
	if (getTextReg(s, r3) != "") return stof(getTextReg(getTextReg(s, r3), r1));
	if (getTextReg(s, r4) != "") return stof(getTextReg(getTextReg(s, r4), r1));
	if (getTextReg(s, r5) != "") return stof(getTextReg(getTextReg(s, r5), r1));
	return 0;
}

string getGender(string s) {
	bool male = false;
	bool female = false;
	std::regex r1("\\b((male))");
	std::regex r2("\\b((males))");
	std::regex r3("\\b((boys))");
	std::regex r4("\\b((men))");
	std::regex r5("\\b((female))");
	std::regex r6("\\b((females))");
	std::regex r7("\\b((girls))");
	std::regex r8("\\b((women))");

	std::regex r9("\\b((Male))");
	std::regex r10("\\b((Males))");
	std::regex r11("\\b((Boys))");
	std::regex r12("\\b((Men))");
	std::regex r13("\\b((Female))");
	std::regex r14("\\b((Females))");
	std::regex r15("\\b((Girls))");
	std::regex r16("\\b((Women))");

	if (getTextReg(s, r1) != "" || getTextReg(s, r2) != "" || getTextReg(s, r3) != "" || getTextReg(s, r4) != "" ||
		getTextReg(s, r9) != "" || getTextReg(s, r10) != "" || getTextReg(s, r11) != "" || getTextReg(s, r12) != "") male = true;
	if (getTextReg(s, r5) != "" || getTextReg(s, r6) != "" || getTextReg(s, r7) != "" || getTextReg(s, r8) != "" ||
		getTextReg(s, r13) != "" || getTextReg(s, r14) != "" || getTextReg(s, r15) != "" || getTextReg(s, r16) != "") female = true;

	if (male and !female) return "m";
	if (!male and female) return "f";
	if (male and female) return "mf";
	return "";
}

string Gender(string s) {
	string temp = "";
	string participants = ExtractString(s, "Abstract", "Keywords");

	temp = getGender(participants);

	if (participants == "") {

		participants = ExtractString(s, "ubjects", "Study 2");

		temp = getGender(participants);
	}

	if (participants == "") {

		participants = ExtractString(s, "2.1.2. Participants", "2.2. Results");

		temp = getGender(participants);
	}

	if (participants == "") {

		participants = ExtractString(s, "Participants", "Targets and informants");

		temp = getGender(participants);
	}

	if (participants == "") {

		participants = ExtractString(s, "Participants", "Measures");

		temp = getGender(participants);
	} return temp;
}

string Type(string s) {

	string temp = "";
	std::regex a1("\\b((self-report))");
	std::regex a2("\\b((individual))");
	std::regex a3("\\b((dyadic))");
	std::regex a4("\\b((objective))");
	std::regex a5("\\b((heteroevaluation))");
	std::regex a6("\\b((teams))");

	if (ExtractString(s, "Materials and procedure", "Table 1") != "") {
		temp = ExtractString(s, "Materials and procedure", "Table 1");
		if (getTextReg(temp, a1) != "")
			return getTextReg(temp, a1);
		if (getTextReg(temp, a2) != "")
			return getTextReg(temp, a2);
		if (getTextReg(temp, a3) != "")
			return getTextReg(temp, a3);
		if (getTextReg(temp, a4) != "")
			return getTextReg(temp, a4);
		if (getTextReg(temp, a5) != "")
			return getTextReg(temp, a5);
		if (getTextReg(temp, a6) != "")
			return getTextReg(temp, a6);
	}

	if (ExtractString(s, "Personality", "Academic performance") != "") {
		temp = ExtractString(s, "Personality", "Academic performance");
		if (getTextReg(temp, a1) != "")
			return getTextReg(temp, a1);
		if (getTextReg(temp, a2) != "")
			return getTextReg(temp, a2);
		if (getTextReg(temp, a3) != "")
			return getTextReg(temp, a3);
		if (getTextReg(temp, a4) != "")
			return getTextReg(temp, a4);
		if (getTextReg(temp, a5) != "")
			return getTextReg(temp, a5);
		if (getTextReg(temp, a6) != "")
			return getTextReg(temp, a6);
	}

	if (ExtractString(s, "Keywords", "Abstract") != "") {
		temp = ExtractString(s, "Keywords", "Abstract");
		if (getTextReg(temp, a1) != "")
			return getTextReg(temp, a1);
		if (getTextReg(temp, a2) != "")
			return getTextReg(temp, a2);
		if (getTextReg(temp, a3) != "")
			return getTextReg(temp, a3);
		if (getTextReg(temp, a4) != "")
			return getTextReg(temp, a4);
		if (getTextReg(temp, a5) != "")
			return getTextReg(temp, a5);
		if (getTextReg(temp, a6) != "")
			return getTextReg(temp, a6);
	}

	if (ExtractString(s, "Measures", "Results") != "") {
		temp = ExtractString(s, "Measures", "Results");
		if (getTextReg(temp, a1) != "")
			return getTextReg(temp, a1);
		if (getTextReg(temp, a2) != "")
			return getTextReg(temp, a2);
		if (getTextReg(temp, a3) != "")
			return getTextReg(temp, a3);
		if (getTextReg(temp, a4) != "")
			return getTextReg(temp, a4);
		if (getTextReg(temp, a5) != "")
			return getTextReg(temp, a5);
		if (getTextReg(temp, a6) != "")
			return getTextReg(temp, a6);
	}
	return "";
}

static int callback(void* NotUsed, int argc, char** argv, char** azColName) {
	int i;
	for (i = 0; i < argc; i++) {
		      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	printf("\n");
	return 0;
	}

int main()
{
	article Article;
	sample Sample;
	variable Variable;

	Init(Article, Sample, Variable);

	string path = "poppler-0.67.0\\bin";
	string file_name = "IJIKMv12p139-157Waheed2882";
	string str;
	str = "cd " + path + " && pdftotext -layout -nopgbrk ..\\..\\" + file_name + ".pdf ..\\..\\" + file_name + ".txt";
	const char* command = str.c_str();
	system(command);

	fstream f(file_name + ".txt", fstream::in);
	string s;
	getline(f, s, '\0');

	f.close();

	/*sqlite3* db;
	char** zErrMsg = 0;
	string sql = "INSERT INTO nume_tabela ('id', 'name', 'locatie') VALUES ('1','name', 'locatie');";
	sqlite3_stmt* stmt;

	int rc = sqlite3_open("DB.db", &db);

	if (rc) {
	      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		  sqlite3_close(db);
		  return(1);
	}
	
	const char** pzTail = 0;
	
	rc = sqlite3_exec(db, sql, callback, 0, zErrMsg);

	if (rc != SQLITE_OK) {
		      fprintf(stderr, "SQL error: %s\n", zErrMsg);
		      sqlite3_free(zErrMsg);
		
	}
	sqlite3_prepare(db, sql.c_str(), sql.size(), &stmt, NULL);
	sqlite3_step(stmt);
	sqlite3_finalize(stmt);
	sqlite3_close(db);*/

	//cout << s << endl;
	
	std::replace(s.begin(), s.end(), '\n', ' ');

	Subjects(s);
	Article.title = title(s);
	Variable.sd = Sample.sd = SD(s);
	Sample.gender = getGender(s);
	Sample.nationality = Nationalities(s);
	Sample.type = Type(s);

	
	cout << "Title: " << Article.title<<endl;
	cout << "Variables: " << Variables(s)<<endl;
	cout << "Participants number: " << Snumber<<endl;
	cout << "Min age: " << age1<<endl;
	cout << "Max age: " << age2<<endl;
	cout << "Nationality: " << Sample.nationality<<endl;
	cout << "Genders: " << Sample.gender<<endl;
	cout << "SD: " << Variable.sd<<endl;
	cout << "Type: "<< Sample.type<<endl;
	
	return 0;
}
