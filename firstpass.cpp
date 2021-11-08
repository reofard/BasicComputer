
#include "BasicComputer.cpp"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
using namespace std;

bool labelCheck(vector<string> token) {
	
	for (int i = 0; i < token.size(); i++) {
		if (token[i].find(",") != string::npos)
			return true;

		return false;
	}

	
}

vector<string> getTokens(string line)
{
	vector<string> token;
	size_t pos = 0;
	line.append(" "); // line의 마지막에 공백이 없으면 마지막 토큰은 지워짐
	while ((pos = line.find(' ')) != string::npos)
	{
		if (line.substr(0, pos).length() > 0)
			token.push_back(line.substr(0, pos));
		line.erase(0, pos + 1);
	}
	return token;
}


bool ORGCheck(vector<string> token) {
	
	if (token[0] == "ORG")
		return true;

	return false;
}


int main(void) {
	
	init();
	word LC = 0;
	
	
	
	ifstream file("test.txt");

	vector<string> token = {};
	map<string, word> symbolTable;
	
	if (true == file.is_open()) {
		string line;
		
		while (file.good()) {
			getline(file, line);
			token = getTokens(line);
			cout << token.size() << endl;

			
			//ORG Check
			if (ORGCheck(token))
			{		
				string str_LC = token[1];

				LC = stoi(str_LC, 0, 16); // str hex 변환
				PC = LC;
				continue;
				
			}

			// labelCheck
			if (labelCheck(token)) {
				string label = token[0];
				label = label.substr(0, label.size() - 1); // , 제거
				symbolTable.insert(pair<string, word>(label, LC));
			}
			LC++;
		}
	}
	
	for (map<string, word>::iterator itr = symbolTable.begin(); itr != symbolTable.end(); itr++)
	{ 
		// itr -> first : key   itr -> second : value

		cout << "Label: " << itr->first << " location: " << std::hex << itr->second << endl;
	}
	
	}

