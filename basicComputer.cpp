
#include <bitset>
#include "CPU_M.h"
#include "hexTranslator.cpp"

using namespace std;

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
	bool I = type >> 3;

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
			AR = IR & 0x0fff;
			AR = MEMORY[AR];
		}
		else
			AR = IR & 0x0fff;
		cout << " 04. Address = " << std::hex << AR << "H" << endl;

		return mHexToString(type);
	}
}

// Memory Reference Instruction
void AND()
{
	DR = MEMORY[AR];
	AC = AC & DR;
}
void ADD()
{
	DR = MEMORY[AR];

	bool carry = false;

	for (int i = 0; i < 16; i++)
	{
		bool A = AC & (1 << i);
		bool B = DR & (1 << i);
		carry = (A & B) | ((A ^ B) & carry);
	}

	E = carry;
	AC = AC + DR;
}
void LDA()
{
	DR = MEMORY[AR];
	AC = DR;
}
void STA()
{
	MEMORY[AR] = AC;
}
void BUN()
{
	PC = AR;
}
void BSA()
{
	MEMORY[AR] = PC;
	AR = AR + 1;
	PC = AR;
}
void ISZ()
{
	DR = MEMORY[AR];
	DR = DR + 1;
	MEMORY[AR] = DR;
	if (DR == 0)
	{
		PC = PC + 1;
	}
}

// Register Reference Instruction
void CLA()
{
	AC = 0;
}
void CLE()
{
	E = false;
}
void CMA()
{
	AC = ~AC;
}
void CME()
{
	E = ~E;
}
void CIR()
{
	bool min_bit = AC & 1;
	AC = AC >> 1;
	AC = AC | (E << 15);
	E = min_bit;
}
void CIL()
{
	bool max_bit = AC & 0x8000;
	AC = AC << 1;
	AC = AC | E;
	E = max_bit;
}
void INC()
{
	AC = AC + 1;
}
void SPA()
{
	if ((AC >> 15) == 0)
		PC = PC + 1;
}
void SNA()
{
	if ((AC >> 15) == 1)
		PC = PC + 1;
}
void SZA()
{
	if (AC == 0x0000)
		PC = PC + 1;
}
void SZE()
{
	if (E == 0)
		PC = PC + 1;
}
void HLT()
{
	S = false;
}

// INC명령어 처리 함수
void INC()
{
	AC = AC + 1;
}

// SZA명령어 처리 함수
void SZA()
{
	if (AC == 0x0000)
		PC = PC + 1;
}


void executeInstruction(string symbol)
{
	if ("AND" == symbol)
		AND();
	else if ("ADD" == symbol)
		ADD();
	else if ("LDA" == symbol)
		LDA();
	else if ("STA" == symbol)
		STA();
	else if ("BUN" == symbol)
		BUN();
	else if ("BSA" == symbol)
		BSA();
	else if ("ISZ" == symbol)
		ISZ();
	else if ("CLA" == symbol)
		CLA();
	else if ("CLE" == symbol)
		CLE();
	else if ("CMA" == symbol)
		CMA();
	else if ("CME" == symbol)
		CME();
	else if ("CIR" == symbol)
		CIR();
	else if ("CIL" == symbol)
		CIL();
	else if ("INC" == symbol)
		INC();
	else if ("SPA" == symbol)
		SPA();
	else if ("SNA" == symbol)
		SNA();
	else if ("SZA" == symbol)
		SZA();
	else if ("SZE" == symbol)
		SZE();
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

// void setMemory(word[] M) {}

int start()
{

	// basicComputer 클래스를 생성한다.
	init();

	//표 6-2,3, 바이트 코드
	MEMORY[0] = (word)0x2004;
	MEMORY[1] = (word)0x1005;
	MEMORY[2] = (word)0x3006;
	MEMORY[3] = (word)0x7001;
	MEMORY[4] = (word)0x0053;
	MEMORY[5] = (word)0xffe9;
	MEMORY[6] = (word)0x0000;

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