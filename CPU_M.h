typedef unsigned char byte;
typedef unsigned short word;

using namespace std;

//메모리
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

bool FGI;
bool FGO;
bool IEN;

//메모리에 데이터를 집어넣는 함수
//매개변수 (배열의 위치, 값)
void inputData(int position, word data);

//명령어 분리 (opcode 와 address)
string decodeInstruction(word instruction);

//명령어 호출
void executeInstruction(string symbol);

void init();