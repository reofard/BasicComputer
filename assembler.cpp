#include "BasicComputer.cpp"
#include "firstpass.cpp"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
using namespace std;

vector<string> lines;

vector<string> secondToken(string line)
{
	vector<string> token;
	size_t pos = 0;
	while ((pos = line.find(' ')) != string::npos)
	{
		string temp = line.substr(0, pos);
		if (temp.length() > 0 && temp.find(',') == string::npos)
			token.push_back(line.substr(0, pos));
		line.erase(0, pos + 1);
	}
	return token;
}
int main()
{
	string filename("test2.txt");
	string line;
	word LC = -1;

	firstPass(filename);
	createTable();

	ifstream input_file(filename);

	if (!input_file.is_open())
	{
		cerr << "Could not open the file - '" << filename << "'" << endl;
		return 0;
	}

	// SecondPass
	while (getline(input_file, line))
	{
		LC++;
		vector<string> tokens = secondToken(line + ' ');
		if (tokens.size() == 0)
			continue;
		//수도 코드 처리
		if (tokens[0] == "ORG")
		{
			LC = stoi(tokens[1], nullptr, 16) - 1;
			continue;
		}
		if (tokens[0] == "END")
		{
			break;
		}
		if (tokens[0] == "DEC")
		{
			MEMORY[LC] = stoi(tokens[1], nullptr, 10);
			continue;
		}
		if (tokens[0] == "HEX")
		{
			MEMORY[LC] = stoi(tokens[1], nullptr, 16);
			continue;
		}
		// 메모리 레퍼런스 명령어 처리
		if (mriTable.find(tokens[0]) != mriTable.end())
		{
			word temp = mriTable[tokens[0]] << 12;
			word addr = symbolTable[tokens[1]] & 4095;
			temp |= addr;
			if (tokens.size() == 3)
			{
				if (tokens[2] == "I")
				{
					temp |= (1 << 15);
				}
			}
			MEMORY[LC] = temp;
			continue;
		}
		if (non_mriTable.find(tokens[0]) != non_mriTable.end())
		{
			word temp = non_mriTable[tokens[0]];
			MEMORY[LC] = temp;
			continue;
		}
		cout << "Error in line of code" << endl;
	}
	input_file.close();

	// BasicComputer 실행
	start(0x100);
	return 0;
}
