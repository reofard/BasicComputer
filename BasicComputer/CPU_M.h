//
//  CPU_M.h
//  BasicComputer
//
//  Created by sunggwang_park on 2021/11/09.
//

#ifndef CPU_M_h
#define CPU_M_h


#endif /* CPU_M_h */


#include <iostream>

typedef unsigned char byte2;
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
