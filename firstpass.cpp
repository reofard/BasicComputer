#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
using namespace std;

typedef unsigned short word;

map<string, word> symbolTable;
map<string, word> mriTable;
map<string, word> non_mriTable;

void createTable()
{
    // mri테이블 구성
    mriTable.insert({"AND", 0});
    mriTable.insert({"ADD", 1});
    mriTable.insert({"LDA", 2});
    mriTable.insert({"STA", 3});
    mriTable.insert({"BUN", 4});
    mriTable.insert({"BSA", 5});
    mriTable.insert({"ISZ", 6});

    // non mri테이블 구성
    non_mriTable.insert({"CLA", 0x7800});
    non_mriTable.insert({"CLE", 0x7400});
    non_mriTable.insert({"CMA", 0x7200});
    non_mriTable.insert({"CME", 0x7100});
    non_mriTable.insert({"CIR", 0x7080});
    non_mriTable.insert({"CIL", 0x7040});
    non_mriTable.insert({"INC", 0x7020});
    non_mriTable.insert({"SPA", 0x7010});
    non_mriTable.insert({"SNA", 0x7008});
    non_mriTable.insert({"SZA", 0x7004});
    non_mriTable.insert({"SZE", 0x7002});
    non_mriTable.insert({"HLT", 0x7001});

    non_mriTable.insert({"INP", 0xf800});
    non_mriTable.insert({"OUT", 0xf400});
    non_mriTable.insert({"SKI", 0xf200});
    non_mriTable.insert({"SKO", 0xf100});
    non_mriTable.insert({"ION", 0xf080});
    non_mriTable.insert({"IOF", 0xf040});
}

vector<string> getTokens(string line)
{
    vector<string> token;
    size_t pos = 0;
    while ((pos = line.find(' ')) != string::npos)
    {
        if (line.substr(0, pos).length() > 0)
            if (line[pos - 1] == ',')
                token.push_back(line.substr(0, pos - 1));
            else
                token.push_back(line.substr(0, pos));
        line.erase(0, pos + 1);
    }
    return token;
}

bool labelCheck(string line)
{
    if (line.find(',') >= 0 && line.find(',') <= line.length() - 1)
        return true;
    else
        return false;
}

bool psuedoCheck(vector<string> tokens, string psuedo)
{
    if (tokens[0] == psuedo)
        return true;
    else
        return false;
}

void getSymbolTable(map<string, word> &symbolTable, vector<string> tokens, word LC)
{
    symbolTable.insert(pair<string, word>(tokens[0], LC));
}

int firstPass()
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
        vector<string> tokens = getTokens(line + ' ');

        if (labelCheck(line) != 0)
        {
            getSymbolTable(symbolTable, tokens, LC);
            LC++;
            continue;
        }
        else
        {
            if (psuedoCheck(tokens, "ORG") != 0)
            {
                LC = stoi(tokens[1], 0, 16);
                continue;
            }
            else
            {
                if (psuedoCheck(tokens, "END") != 0)
                    break;
                else
                {
                    LC++;
                    continue;
                }
            }
        }
    }
    input_file.close();

    return 0;
}