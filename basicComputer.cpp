#include <iostream>
#include <string>
#include <bitset>
#include "CPU_M.h"
#include "hexTranslator.cpp"

using namespace std;

//메모리에 데이터를 집어넣는 함수
//매개변수 (배열의 위치, 값)
void inputData(int position, word data) { }

//명령어 분리 (opcode 와 address)
void decodeInstruction(word instruction)
{
	// Instruction Register에 명령어 저장
	IR = instruction;
	
	// 명령어 타입 추출
	byte type = (byte)(IR >> 12);

	// 구분해낸 명령어 문자열을 통해 명령어 형식별로 결과를 출력함
	switch (type)
	{

		//Opcode = 111, I = 0
		case 0x7:
			cout << " 02. 명령어 형식 = 'Register' reference operation" << endl;
			cout << " 03. Symbol = " << HexToString(IR) << endl;
			break;

		//Opcode = 111, I = 1
		case 0xf:
			cout << " 02. 명령어 형식 = 'I/O' operation" << endl;
			cout << " 03. Symbol = " << HexToString(IR) << endl;
			break;

		//Opcode = 000~110, I = 0, 1
		default:
			cout << " 02. 명령어 형식 = 'Memory' reference operation" << endl;
			cout << " 03. Symbol = " << mHexToString(type) << endl;

			// 주소모드를 나타내는 4비트를 밀어버리고 12비트의 Address만 남김			
			TR = (IR << 4);
			cout << " 04. Address = " << std::hex << (TR / 16) << "H" << endl;

			break;
	}
}

void init()
{
	DR = 0;
	AR = 0;
	TR = 0;
}

int main()
{

	// basicComputer 클래스를 생성한다.
	init();

	//메모리에 임의 명령어를 입력한다.
	MEMORY[0] = (word)0xf800;

	//메모리 0번에서 명령어 읽음.
	word testInstruction = MEMORY[0];

	cout << " 01. 입력 = 0x" << std::hex << testInstruction << endl;

	//명령어 해독 실행
	decodeInstruction(testInstruction);

	return 0;
}