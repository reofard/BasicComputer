#include "BasicComputer.cpp"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
using namespace std;

//word MEMORY[4096];
vector<string> lines;

map<string, word> symbolTable;
map<string, word> mriTable;
map<string, word> non_mriTable;

void init2()
{
	// mri테이블 구성
	mriTable.insert({"AND", 0});
	mriTable.insert({"ADD", 1});
	mriTable.insert({"LDA", 2});
	mriTable.insert({"STA", 3});
	mriTable.insert({"BUN", 4});
	mriTable.insert({"BSA", 5});
	mriTable.insert({"ISZ", 6});

	// non mri테이블 구성
	non_mriTable.insert({"CLA", 0x7800});
	non_mriTable.insert({"CLE", 0x7400});
	non_mriTable.insert({"CMA", 0x7200});
	non_mriTable.insert({"CME", 0x7100});
	non_mriTable.insert({"CIR", 0x7080});
	non_mriTable.insert({"CIL", 0x7040});
	non_mriTable.insert({"INC", 0x7020});
	non_mriTable.insert({"SPA", 0x7010});
	non_mriTable.insert({"SNA", 0x7008});
	non_mriTable.insert({"SZA", 0x7004});
	non_mriTable.insert({"SZE", 0x7002});
	non_mriTable.insert({"HLT", 0x7001});

	// mritable 받아오기
	symbolTable.insert({"MIN", 83});
	symbolTable.insert({"SUB", -23});
	symbolTable.insert({"DIF", 0});
}

vector<string> getTokens(string line)
{
	vector<string> token;
	size_t pos = 0;
	while ((pos = line.find(' ')) != string::npos)
	{
		if (line.substr(0, pos).length() > 0)
			token.push_back(line.substr(0, pos));
		line.erase(0, pos + 1);
	}
	return token;
}




bool pseudoCheck(vector<string> token)
{
	if (token[0] == "ORG" ||
		token[0] == "END" ||
		token[0] == "DEC" ||
		token[0] == "HEX"	
	)
		return true;
	return false;
}

bool MRICheck (vector<string> token)
{
	if (mriTable.find(token[0]) != mriTable.end()) 
	{ 
		return true; 
	} 
	else 
	{
		return false; 
	}
}

bool nonMRICheck (vector<string> token)
{
	if (non_mriTable.find(token[0]) != non_mriTable.end()) 
	{ 
		return true; 
	}
	else 
	{ 
		return false; 
	}
}

bool ORGCheck(vector<string> token)
{

	if (token[0] == "ORG")
		return true;

	return false;
}

bool ENDCheck(vector<string> token)
{
	if (token[0] == "END")
		return true;

	return false;
}


void storeNonMRI (vector<string> token, int LC)
{
	MEMORY[LC] = (word)non_mriTable[token[0]];
}

void storeMRI (vector<string> token, int LC)
{

}




int main()
{
	init2();

	string filename("test.txt");
	string line;
	word LC = 0;
	ifstream input_file(filename);

	if (!input_file.is_open())
	{
		cerr << "Could not open the file - '" << filename << "'" << endl;
		return 0;
	}

	while (getline(input_file, line))
	{
		LC++;
		cout << line << endl;
		vector<string> tokens = getTokens(line + ' ');

		
		if (pseudoCheck(tokens))//수도 코드 처리
		{
			if (ORGCheck(tokens) != 0)
			{
				LC = stoi(tokens[1], 0, 16);
				continue;
			}
			if (ENDCheck(tokens) != 0)
			{
				break;
			}
			//if (/*DEX인가?*/)
			{
				//서정이
			}
			//if (/*HEX인가?*/)
			{
				//서완석
			}
			continue;
		}
		//메모리 레퍼런스 명령어 처리
		if (MRICheck(tokens))
		{
			continue;
		}
		if (nonMRICheck(tokens))
		{	
			storeNonMRI(tokens, LC);
			continue;
		}
		cout << "Error in line of code" << endl;
	}
	input_file.close();

	//바이트 코드 basic_computer에 전달
	return 0;
}
