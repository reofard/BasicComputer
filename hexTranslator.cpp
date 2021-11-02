#include <string>

typedef unsigned char byte;
typedef unsigned short word;

using namespace std;

// decodeInstruction 함수에서 레지스터 참조, 입출력연산의 경우 헥사코드 변환을 위해 호출
string HexToString(word hex)
{
	switch (hex)
	{
	// 레지스터 참조 명령어
	case 0x7800:

		return "CLA";
	case 0x7400:
		return "CLE";
	case 0x7200:
		return "CMA";
	case 0x7100:
		return "CME";
	case 0x7080:
		return "CIR";
	case 0x7040:
		return "CIL";
	case 0x7020:
		return "INC";
	case 0x7010:
		return "SPA";
	case 0x7008:
		return "SNA";
	case 0x7004:
		return "SZA";
	case 0x7002:
		return "SZE";
	case 0x7001:
		return "HLT";

	// I/O 명령어
	case 0xf800:
		return "INP";
	case 0xf400:
		return "OUT";
	case 0xf200:
		return "SKI";
	case 0xf100:
		return "SKO";
	case 0xf080:
		return "ION";
	case 0xf040:
		return "IOF";
	}
	return "Unknown";
}

// 메모리 참조명령
string mHexToString(byte hex)
{
	string str = 8 & hex ? "[ Indirect ]" : "[ Direct ]";
	word opcode = 7 & hex;

	switch (opcode)
	{
	case 0x0:
		return "AND";
	case 0x1:
		return "ADD";
	case 0x2:
		return "LDA";
	case 0x3:
		return "STA";
	case 0x4:
		return "BUN";
	case 0x5:
		return "BSA";
	case 0x6:
		return "ISZ";
	}
	return "Unknown";
}