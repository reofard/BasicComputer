//
//  basicComputer.h
//  BasicComputer
//
//  Created by sunggwang_park on 2021/11/09.
//

#ifndef basicComputer_h
#define basicComputer_h


#include <iostream>
#include <string>
#include <bitset>
#include <vector>
#include <iomanip>
#include "firstpass.h"
//#include <map
#include "CPU_M.h"
//#include "hexTranslator.cpp"



using namespace std;

map<word,string> reverseSymbolTable;

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
string mHexToString(byte2 hex)
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
    byte2 type = (byte2)(IR >> 12);
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
        

//         주소모드를 나타내는 4비트를 밀어버리고 12비트의 Address만 남김
        if (I == 1)
        {
            AR = IR & 0x0fff;
            AR = MEMORY[AR];
        }
        else
            AR = IR & 0x0fff;
        
        cout << " 04. Address = " <<setw(3)<< std::hex << AR << "H" << endl;
        

        return mHexToString(type);
    }
}

// Memory Reference Instruction
void AND()
{
    DR = MEMORY[AR];
    AC = AC & DR;
    
    cout << "DR" << DR << endl;
    cout << "AC" << AC << endl;
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
    
    cout << " 변경된 레지스터 값" << endl;
    cout << " DR : " <<setw(4)<< DR << endl;
    cout << " AC : " <<setw(4)<< AC << endl;
    cout << " E  : " << E << endl;
}
void LDA()
{
    DR = MEMORY[AR];
//    cout << "AR !+ " << AR << endl;
    AC = DR;
    
    cout << std::hex;
    cout << " 변경된 레지스터 값" << endl;
    cout << " DR : " <<setw(4)<< DR << endl;
    cout << " AC : " <<setw(4)<< AC << endl;
    
}
void STA()
{
    MEMORY[AR] = AC;
    
    if(reverseSymbolTable.find(AR) != reverseSymbolTable.end()) {

            cout << " 변경된 라벨 값" << endl;
            cout << " " << reverseSymbolTable[AR] <<" : " <<setw(4)<< MEMORY[AR] << endl;

            return;

    }
    
    cout << " 변경된 메모리 값" << endl;
    cout << " MEMORY[" <<setw(4)<< AR << "] : ";
    cout << setw(4)<< MEMORY[AR] << endl;
    
    

    
    
   

    
}
void BUN()
{
    PC = AR;
    cout << " 변경된 레지스터 값" << endl;
    cout << " PC : " <<setw(4)<< PC << endl;
}
void BSA()
{
    MEMORY[AR] = PC;
    AR = AR + 1;
    PC = AR;
    
    if(reverseSymbolTable.find(AR) != reverseSymbolTable.end()) {

            cout << " 변경된 라벨 값" << endl;
            cout << " " << reverseSymbolTable[AR] <<" : " <<setw(4)<< MEMORY[AR] << endl;

    } else {
        cout << " 변경된 메모리 값" << endl;
        cout << " MEMORY[" <<setw(4)<< AR << "] : ";
        cout << setw(4)<< MEMORY[AR] << endl;
    }
    

    cout << " 변경된 레지스터 값" << endl;
    cout << " AR : " <<setw(4)<< AR << endl;
    cout << " PC : " <<setw(4)<< PC << endl;
    
    
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
    
    if(reverseSymbolTable.find(AR) != reverseSymbolTable.end()) {

            cout << " 변경된 라벨 값" << endl;
            cout << " " << reverseSymbolTable[AR] <<" : " <<setw(4)<< MEMORY[AR] << endl;

    } else {
        cout << " 변경된 메모리 값" << endl;
        cout << " MEMORY[" <<setw(4)<< AR << "] : ";
        cout << setw(4)<< MEMORY[AR] << endl;
    }
    
    cout << " 변경된 레지스터 값" << endl;
    cout << " DR : " <<setw(4)<< DR << endl;
    cout << " PC : " <<setw(4)<< AR << endl;
    
}

// Register Reference Instruction
void CLA()
{
    AC = 0;
    cout << " 변경된 레지스터 값" << endl;
    cout << " AC : " <<setw(4)<< AC << endl;
    
}
void CLE()
{
    E = false;
    cout << " 변경된 레지스터 값" << endl;
    cout << " E : " << E << endl;
    
}
void CMA()
{
    AC = ~AC;
    cout << " 변경된 레지스터 값" << endl;
    cout << " AC : " <<setw(4)<< AC << endl;
    
}
void CME()
{
    E = ~E;
    cout << " 변경된 레지스터 값" << endl;
    cout << " E : " <<setw(4)<< E << endl;
    
}
void CIR()
{
    bool min_bit = AC & 1;
    AC = AC >> 1;
    AC = AC | (E << 15);
    E = min_bit;
    cout << " 변경된 레지스터 값" << endl;
    cout << " AC : " <<setw(4)<< AC << endl;
    cout << " E : " << E << endl;
}
void CIL()
{
    bool max_bit = AC & 0x8000;
    AC = AC << 1;
    AC = AC | E;
    E = max_bit;
    cout << " 변경된 레지스터 값" << endl;
    cout << " AC : " <<setw(4)<< AC << endl;
    cout << " E : " << AR << endl;
}
void INC()
{
    AC = AC + 1;
    cout << " 변경된 레지스터 값" << endl;
    cout << " AC : " <<setw(4)<< AC << endl;
    
}
void SPA()
{
    if ((AC >> 15) == 0)
        PC = PC + 1;
    cout << " 변경된 레지스터 값" << endl;
    cout << " PC : " <<setw(4)<< AR << endl;
}
void SNA()
{
    if ((AC >> 15) == 1)
        PC = PC + 1;
    cout << " 변경된 레지스터 값" << endl;
    cout << " PC : " <<setw(4)<< AR << endl;
}
void SZA()
{
    if (AC == 0x0000)
        PC = PC + 1;
    cout << " 변경된 레지스터 값" << endl;
    cout << " PC : " <<setw(4)<< AR << endl;
}
void SZE()
{
    if (E == 0)
        PC = PC + 1;
    cout << " 변경된 레지스터 값" << endl;
    cout << " PC : " <<setw(4)<< AR << endl;
}
void HLT()
{
    S = false;
    cout << " 변경된 레지스터 값" << endl;
    cout << " S : " << S << endl;
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

void makeReverseSymbolTable() {
    for (map<string, word>::iterator itr = symbolTable.begin(); itr != symbolTable.end(); itr++)
        {
            // itr -> first : key   itr -> second : value
            
            reverseSymbolTable.insert(pair<word, string>(itr->second, itr->first));

//            cout << "Label: " << itr->first << " location: " << std::hex << itr->second << endl;
        }
}

int start()
{
    makeReverseSymbolTable();

    
    cout << "---------Machine Code Execution----------" << endl;

    // basicComputer 클래스를 생성한다.
    init();

    //표 6-8, 바이트 코드
    MEMORY[0] = (word)0x2004;
    MEMORY[1] = (word)0x1005;
    MEMORY[2] = (word)0x3006;
    MEMORY[3] = (word)0x7001;
    MEMORY[4] = (word)0x0053;
    MEMORY[5] = (word)0xffe9;
    MEMORY[6] = (word)0x0000;

    
    cout << setfill('0');
    cout << hex; //효과 지속
    
    
    while (S)
    {
        
        cout << endl;
        // FETCH
        // T0
        
        
        AR = PC;
        
        
        cout << "Location" << "     " << "Instruction" << endl;
        
        cout << setw(3) << AR << "          "  << setw(4)<< MEMORY[AR] << endl;
        
        
        

        word testInstruction = MEMORY[AR];
        PC++;

        
        cout << " 01. 입력 = 0x" << std::hex << testInstruction << endl;

        string symbol = decodeInstruction(testInstruction);

        // EXECUTION
        executeInstruction(symbol);
    }
    return 0;
}



#endif /* basicComputer_h */
