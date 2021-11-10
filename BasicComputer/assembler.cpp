//
//  main.cpp
//  BasicComputer
//
//  Created by sunggwang_park on 2021/11/09.
//

#include <iostream>
#include "basicComputer.h"
#include "firstpass.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>





using namespace std;

bool cmp(const pair<string, word>& a, const pair<string, word>& b) {
    if (a.second < b.second)
        return true;
    return false;
}

void printSymbolTable() {
    
    cout << "---------First Pass----------" << endl;
    cout << "[ Symbol Table ]" << endl;
    
    vector<pair<string,word>> vec( symbolTable.begin(), symbolTable.end() );
    
    sort(vec.begin(), vec.end(), cmp);
    
    

    
    cout << "Label" << "    " << "location" << endl;
    
    cout << hex; //효과 지속
    cout << setfill('0');
    for (auto num : vec) {
        cout << num.first  << "      "  <<setw(3)<< num.second << endl;
    }
    
//    cout << "------------------------------" << endl;
    
    return;
}


void printProgram() {
    cout << "[ Program ]" << endl;
    cout << "Location" << "     " << "Instruction" << endl;
    
    cout << hex; //효과 지속
    cout << setfill('0');
    
    word address = 0; //하드 코딩
    cout << MEMORY[address] << endl;
    
    while (MEMORY[address] != 0) {
        cout << setw(3) << address << "          "  << setw(4)<< MEMORY[address] << endl;
        address++;
    }
    
//    for (; startAddress ; i++) {
//        cout << setw(3) << i << "          "  << setw(4)<< MEMORY[i] << endl;
//    }
}


void secondPass(string filename) {
    cout << "---------Second Pass----------" << endl;
    
    string line;
    word LC = 0;
    ifstream input_file(filename);

    if (!input_file.is_open())
    {
        cerr << "Could not open the file - '" << filename << "'" << endl;
        return;
    }
    
//    getline(input_file, line);
    

//    while (getline(input_file, line))
//    {
//        LC++;
//        cout << line << endl;
//        vector<string> tokens = getTokens(line + ' ');
//
//        //수도 코드 처리
//        if (/*수도 코드인가? 박하민*/)
//        {
//            if (/*ORG인가?*/)
//            {
//                //신호수
//            }
//            if (/*END인가?*/)
//            {
//                //신호수
//            }
//            if (/*DEX인가?*/)
//            {
//                //서정이
//            }
//            if (/*HEX인가?*/)
//            {
//                //서완석
//            }
//            continue;
//        }
//        //메모리 레퍼런스 명령어 처리
//        if (/*MRI명령어인가?*/)
//        {
//            //서완석
//            continue;
//        }
//        if (/*MRI명령어가 아닌가?*/)
//        {
//            //박하민
//            continue;
//        }
//        cout << "Error in line of code" << endl;
//    }
    input_file.close();
    
    printProgram();
    
    
}




int main(int argc, const char * argv[]) {
    
    
    
    string filename("test.txt");
    
    firstPass(filename);
    printSymbolTable();
    
    
    //임시 코드
    MEMORY[0] = (word)0x2004;
    MEMORY[1] = (word)0x1005;
    MEMORY[2] = (word)0x3006;
    MEMORY[3] = (word)0x7001;
    MEMORY[4] = (word)0x0053;
    MEMORY[5] = (word)0xffe9;
    MEMORY[6] = (word)0x0000;
    
    secondPass(filename);
    
    start();
    
//    printProgram();
    
    
    

    //바이트 코드 basic_computer에 전달
    return 0;
}
