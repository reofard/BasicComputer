#include <iostream>
#include <string>
#include <bitset>
#include "CPU_M.h"

using namespace std;

word MEMORY[4096];

//레지스터
word DR;
word AR;
word AC;
word IR;
word PC;
word TR;
word INPR;
word OUTR;

bool S;
bool E;

//메모리에 데이터를 집어넣는 함수
//매개변수 (배열의 위치, 값)
void inputData(int position, word data) {}

//명령어 분리 (opcode 와 address)
string decodeInstruction(word instruction)
{
	// Instruction Register에 명령어 저장
	IR = instruction;

	// 명령어 타입 추출
	// T2
	byte type = (byte)(IR >> 12);
	bool I = type | 8;

	// DECODE
	//  구분해낸 명령어 문자열을 통해 명령어 형식별로 결과를 출력함
	switch (type)
	{

	// Opcode = 111, I = 0
	case 0x7:
		cout << " 02. 명령어 형식 = 'Register' reference operation" << endl;
		cout << " 03. Symbol = " << HexToString(IR) << endl;
		return HexToString(IR);

	// Opcode = 111, I = 1
	case 0xf:
		cout << " 02. 명령어 형식 = 'I/O' operation" << endl;
		cout << " 03. Symbol = " << HexToString(IR) << endl;
		return HexToString(IR);

	// Opcode = 000~110, I = 0, 1
	default:
		cout << " 02. 명령어 형식 = 'Memory' reference operation" << endl;
		cout << " 03. Symbol = " << mHexToString(type) << endl;

		// 주소모드를 나타내는 4비트를 밀어버리고 12비트의 Address만 남김
		if (I == 1)
		{
			AR = IR & 0x0FFF;;
			AR = MEMORY[AR];
		}
		else
			AR = IR & 0x0FFF;;
		cout << " 04. Address = " << std::hex << AR << "H" << endl;

		return mHexToString(type);
	}
}

// CMA명령어 처리 함수
void CMA()
{
	AC = ~AC;
}
// SPA명령어 처리 함수
void SPA()
{
	if ((AC >> 15) == 0)
		PC = PC + 1;
}
// HLT명령어 처리 함수
void HLT()
{
	S = false;
}

// BSA명령어 처리 함수
void BSA()
{
	MEMORY[AR] = PC;
	PC = AR + 1;

}
// ISZ명령어 처리 함수
void ISZ()
{
	MEMORY[AR] = MEMORY[AR] + 1;
	if (MEMORY[AR] == 0)
	{
		PC = PC + 1;
	}
}
// CIL명령어 처리 함수
void CIL()
{
	E = AC & 0x8000;
	AC = AC << 1;
	AC = AC | (word)E;
}

void executeInstruction(string symbol)
{
	if ("AND" == symbol)
		;
	else if ("ADD" == symbol)
		;
	else if ("LDA" == symbol)
		;
	else if ("STA" == symbol)
		;
	else if ("BUN" == symbol)
		;
	else if ("BSA" == symbol)
		BSA();
	else if ("ISZ" == symbol)
		ISZ();
	else if ("CLA" == symbol)
		;
	else if ("CLE" == symbol)
		;
	else if ("CMA" == symbol)
		CMA();
	else if ("CME" == symbol)
		;
	else if ("CIR" == symbol)
		;
	else if ("CIL" == symbol)
		CIL();
	else if ("INC" == symbol)
		;
	else if ("SPA" == symbol)
		SPA();
	else if ("SNA" == symbol)
		;
	else if ("SZA" == symbol)
		;
	else if ("SZE" == symbol)
		;
	else if ("HLT" == symbol)
		HLT();
	else
		cout << "I/O 명령어" << endl;

	//메모리 및 레지스터 상태 출력
}

void init()
{
	DR = 0;
	AR = 0;
	TR = 0;
	S = true;
}

int main()
{

	// basicComputer 클래스를 생성한다.
	init();

	AC = 0b1000101010101000;
	PC = 0;
	MEMORY[0x456] = 0xFFFF;

	//메모리에 임의 명령어를 입력한다.
	
	MEMORY[0] = (word)0x5123;
	MEMORY[0x124] = (word)0x7040;
	MEMORY[0x125] = (word)0x6456;
	MEMORY[0x126] = (word)0x5130;
	MEMORY[0x127] = (word)0x7001;
	MEMORY[0x130] = (word)0x7040;
	MEMORY[0x131] = (word)0x7001;

	while (S)
	{
		// FETCH
		// T0
		AR = PC;

		word testInstruction = MEMORY[AR];
		PC++;

		cout << " 01. 입력 = 0x" << std::hex << testInstruction << endl;

		string symbol = decodeInstruction(testInstruction);

		// EXECUTION
		executeInstruction(symbol);
	}
	return 0;
}