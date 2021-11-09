/* 책의 흐름도를 참고하여 코드를 수정하였습니다.
   또한, 올려주신 분들의 코드와 비슷하도록 코드를 구성해보았습니다. 
*/
#include "BasicComputer.cpp"
#include "assembler_firstpass.cpp"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
using namespace std;

word MEMORY[4096];
vector<string> lines;

map<string, word> symbolTable;
map<string, word> mriTable;
map<string, word> non_mriTable;

#define checkBit(n,p) (bool)(n&(1<<p))

void init()
{
	// mri테이블 구성
	mriTable.insert({ "AND", 0 });
	mriTable.insert({ "ADD", 1 });
	mriTable.insert({ "LDA", 2 });
	mriTable.insert({ "STA", 3 });
	mriTable.insert({ "BUN", 4 });
	mriTable.insert({ "ISZ", 5 });

	// non mri테이블 구성
	non_mriTable.insert({ "CLA", 0x7800 });
	non_mriTable.insert({ "CLE", 0x7400 });
	non_mriTable.insert({ "CMA", 0x7200 });
	non_mriTable.insert({ "CME", 0x7100 });
	non_mriTable.insert({ "CIR", 0x7080 });
	non_mriTable.insert({ "CIL", 0x7040 });
	non_mriTable.insert({ "INC", 0x7020 });
	non_mriTable.insert({ "SPA", 0x7010 });
	non_mriTable.insert({ "SNA", 0x7008 });
	non_mriTable.insert({ "SZA", 0x7004 });
	non_mriTable.insert({ "SZE", 0x7002 });
	non_mriTable.insert({ "HLT", 0x7001 });

	// mritable 받아오기
	symbolTable.insert({ "MIN", 83 });
	symbolTable.insert({ "SUB", -23 });
	symbolTable.insert({ "DIF", 0 });
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
	if(token[0]=="ORG" || token[0]=="END" || token[0] == "DEC" || token[0] == "HEX")
	{
		return true;
	}
	return false;

}

bool MRICheck(vector<string> token) {
	if (token[0] == "AND" ||
		token[0] == "ADD" ||
		token[0] == "LDA" ||
		token[0] == "STA" ||
		token[0] == "BUN" ||
		token[0] == "BSA" ||
		token[0] == "ISZ"
		)
		return true;
	return false;
}

bool ORGCheck(vector<string> token) {
	if (token[0] == "ORG")
		return true;
	return false;
}

bool DECCheck(vector<string> token)
{
	if (token[0] == "DEC")
		return true;
	return false;
}

bool HEXCheck(vector<string> token)
{
	if (token[0] == "DEC")
		return true;
	return false;
}

bool ENDCheck(vector<string> token) {
	if (token[0] == "END")
		return true;
	return false;
}

string decToBin(int n, int length)
{
	int i;
	string s = "";
	for (i = length - 1; i >= 0; i--)
	{
		if (checkBit(n, i))
		{
			s += "1";
		}
		else
		{
			s += "0";
		}
		if (i == 4 || i == 8 || i == 12)
		{
			s += " ";
		}
	}
	return s;
}

int main()
{
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

		//수도 코드 처리
		if (psuedoCheck(tokens) /*수도 코드인가?*/)
		{
			if (ORGCheck(tokens)!= 0 /*ORG인가?*/)  // ORG 이면 LC를 다시 세팅 
			{
				LC = stoi(tokens[1], 0, 16); //
				continue;
			}
			
			if (ENDCheck(tokens) != 0) // END 이면 끝냄 
			{
				break;
			}
			 
			if ( DECCheck(tokens) != 0 /*DEC인가?*/) // DEC or HEX 이면 그 번지 수에 DEC, HEX 값을 넣어준다 
			{ 
				int tmp = stoi(tokens[2], nullptr, 10);
				string strtmp = decToBin(tmp, 16);
				int n = stoi(strtmp, nullptr, 2);
				// convert operand to binary and store int location given by LC 
				MEMORY[LC] = n;
			}

			if ( psuedoCheck(tokens, "HEX") != 0/*HEX인가?*/)
			{
				// convert operand to binary and store int location given by LC 
			}
		}
		//메모리 레퍼런스 명령어 처리
		else if (MRICheck(tokens)/*MRI명령인가*/)
		{
			 // opcode 3비트를 가져옴 
			 // 피연산자 주소 ( 하위 12비트 ) 를 가져옴 
			 // addressing 모드에 해당하는 I 값이 1인지 0인지 확인 
			continue;
		}
		/*else if (//MRI명령어가 아닌가?)
		{
			 // 레지스터 참조 명령어, 입출력 명령어 중 하나 
			 // 해당하는 명령을 정의된 명령 테이블에서 16비트 그대로 가져오면 됨 
			continue;
		}*/
		else 
			cout << "Error in line of code" << endl;
	}
	input_file.close();



	//바이트 코드 basic_computer에 전달
	return 0;
}
