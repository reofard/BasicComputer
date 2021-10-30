#pragma once
#include <iostream>

typedef unsigned char byte;
typedef unsigned short word;

using namespace std;

//메모리
extern word MEMORY[4096];

//레지스터
extern word DR;
extern word AR;
extern word AC;
extern word IR;
extern word PC;
extern word TR;
extern word INPR;
extern word OUTR;

extern bool S;
extern bool E;

//메모리에 데이터를 집어넣는 함수
//매개변수 (배열의 위치, 값)
void inputData(int position, word data);

//명령어 분리 (opcode 와 address)
string decodeInstruction(word instruction);

//opcode 해독
void decodeOpcode();

//명령어 판별
void readInstruction();

//명령어 호출
void executeInstruction(string symbol);

void init();

string HexToString(word hex);
string mHexToString(byte hex);