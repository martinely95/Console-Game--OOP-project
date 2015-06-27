// tova za splita :
#include <string>
#include <sstream>
#include <vector>

using namespace std;

#ifndef SPLIT_STRINGTOINT_H
#define SPLIT_STRINGTOINT_H

//split begin
std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		elems.push_back(item);
	}
	return elems;
}

std::vector<std::string> split(const std::string &s, char delim) {
	std::vector<std::string> elems;
	split(s, delim, elems);
	return elems;
}
//split end

int StringToInt(string string)
{
	int i;
	std::istringstream ss(string);
	ss >> i;
	return i;
}

string CharToString(char a){
	std::string s;
	std::stringstream ss;
	ss << a;
	ss >> s;
	return s;
}

#endif
