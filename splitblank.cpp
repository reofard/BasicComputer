#include <string>
#include<string.h>
#include <vector>
using namespace std;



string ltrim(string line)
{
	const char* delimeters = " \t\n\r\f\v";
	
	line.erase(0, line.find_first_not_of(delimeters));
	return line;
}

string rtrim(string line)
{
	const char* delimeters = " \t\n\r\f\v";
	line.erase(line.find_last_not_of(delimeters) + 1);
	return line;
}

string trim(string line)
{
	
	return ltrim(rtrim(line));
}

vector<string> splitBlank(string line)
{
	line = trim(line); // 앞 뒤 공백 제거
	int previous = 0;
	int current = 0;

	vector<string> token;
	token.clear();

	current = line.find(' ');

	while (current != string::npos) {
		string substring = line.substr(previous, current - previous);
		substring = trim(substring);
		token.push_back(substring);
		previous = current + 1; // 그다음 문자열 index
		current = line.find(' ', previous);
	}
	token.push_back(line.substr(previous, current - previous)); // 마지막 문자열 저장

	string zero_str = "";

	for (int i = 0; i < token.size(); i++)
	{
		if (token[i] == zero_str) {
			 token.erase(token.begin() + i);
			 i = 0;
		}
	}
	
	return token;
}


