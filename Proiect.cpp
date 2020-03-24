#include <iostream>
#include <regex>
#include <string>

char symbols[7] = { ',', '.', '!', '?', ':', ';', '-' };

void eliminateSymbol(std::string &s) {
	for (int i = 0; i <= 6; ++i)
		if (symbols[i] == s.back())
			s = s.substr(0, s.size() - 1);
}

int main()
{
	std::string s("Since research has shown that age (Vinchur et al., 1998), gender (Bowen, Swim & Jacobs, 2000), and organizational tenure (Ng & Feldman, 2010) can be related to performance, we included these as control variables. To control for its possible quadratic effects as found by Grant(2013), we assessed positive affectivity (Watson et al., 1988), as it is closely related to the other facets of extroversion, such as warmth, gregariousness, and positive emotions (Nemanick & Munz, 1997). Cronbach`s Alpha for positive affectivity waas alpha = .81.");
	std::smatch m;
	std::string sCopy;
	std::regex e("\\b(such as )([^ ]*)");
	std::regex e1("\\b(has shown that )([^ ]*)");

	sCopy = s;
	std::string s1;

	std::cout << "The following variables were found: " << std::endl;

	while (std::regex_search(sCopy, m, e)) {
		for (std::string x : m)
		{
			int pos = x.find("such as ");
			s1 = x.substr(pos + 1);
		}
		eliminateSymbol(s1);
		std::cout << s1<<'\n';
		std::cout << std::endl;
		sCopy = m.suffix().str();
	}

	sCopy = s;

	while (std::regex_search(sCopy, m, e1)) {
		for (std::string x : m) //std::cout << x << " ";
		{
			int pos = x.find("has shown that ");
			s1 = x.substr(pos + 1);
		}
		std::cout << s1 << '\n';
		std::cout << std::endl;
		sCopy = m.suffix().str();
	}

	return 0;
}
