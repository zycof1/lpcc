#include <bits/stdc++.h>
using namespace std;

/* ================================
   MACHINE OPCODE TABLE (MOT)
================================ */
struct MOTEntry {
    string mnemonic;
    string mclass;
    string opcode;
};

vector<MOTEntry> MOT = {
    {"STOP","IS","00"}, {"ADD","IS","01"}, {"SUB","IS","02"},
    {"MULT","IS","03"}, {"MOVER","IS","04"}, {"MOVEM","IS","05"},
    {"COMP","IS","06"}, {"BC","IS","07"}, {"DIV","IS","08"},
    {"READ","IS","09"}, {"PRINT","IS","10"}, {"LOAD","IS","11"},
    {"START","AD","01"}, {"END","AD","02"}, {"ORIGIN","AD","03"},
    {"EQU","AD","04"}, {"LTORG","AD","05"},
    {"DS","DL","01"}, {"DC","DL","02"}
};

/* ================================
   SYMBOL TABLE
================================ */
struct Symbol {
    string name;
    int address;
    bool defined;
    bool used;
};

vector<Symbol> SYMTAB;

/* ================================
   LITERAL TABLE
================================ */
struct Literal {
    string literal;
    int address;
};

vector<Literal> LITTAB;

/* ================================
   POOL TABLE
================================ */
vector<int> POOLTAB;

/* ================================
   GLOBAL VARIABLES
================================ */
vector<string> errors;
int LC = 0;
int literalPoolStart = 0;

/* ================================
   Utility Functions
================================ */

int searchMOT(string token) {
    for(int i=0;i<MOT.size();i++)
        if(MOT[i].mnemonic == token)
            return i;
    return -1;
}

int searchSymbol(string token) {
    for(int i=0;i<SYMTAB.size();i++)
        if(SYMTAB[i].name == token)
            return i;
    return -1;
}

int searchLiteral(string token) {
    for(int i=0;i<LITTAB.size();i++)
        if(LITTAB[i].literal == token)
            return i;
    return -1;
}

bool isNumber(string s) {
    for(char c: s)
        if(!isdigit(c)) return false;
    return true;
}

/* ================================
   PASS 1
================================ */

void pass1() {

    ifstream fin("sample.asm");
    ofstream fout("sample_IC.txt");

    if(!fin) {
        cout<<"Error opening source file\n";
        return;
    }

    POOLTAB.push_back(0);

    string line;

    while(getline(fin, line)) {

        if(line.empty()) continue;

        stringstream ss(line);
        vector<string> tokens;
        string token;

        while(ss >> token)
            tokens.push_back(token);

        if(tokens.size()==0) continue;

        int index = 0;

        // Label Check
        if(searchMOT(tokens[0]) == -1) {
            if(tokens.size()>1 && searchMOT(tokens[1]) != -1) {

                int symIndex = searchSymbol(tokens[0]);

                if(symIndex != -1 && SYMTAB[symIndex].defined)
                    errors.push_back("Duplicate definition of symbol: " + tokens[0]);
                else {
                    if(symIndex == -1)
                        SYMTAB.push_back({tokens[0],LC,true,false});
                    else {
                        SYMTAB[symIndex].address = LC;
                        SYMTAB[symIndex].defined = true;
                    }
                }
                index++;
            }
            else {
                errors.push_back("Invalid mnemonic: " + tokens[0]);
                continue;
            }
        }

        if(index >= tokens.size()) continue;

        int motIndex = searchMOT(tokens[index]);
        if(motIndex == -1) {
            errors.push_back("Invalid mnemonic: " + tokens[index]);
            continue;
        }

        string mclass = MOT[motIndex].mclass;
        string opcode = MOT[motIndex].opcode;

        // START
        if(tokens[index] == "START") {
            LC = stoi(tokens[index+1]);
            fout<<"(AD,01) (C,"<<LC<<")\n";
        }

        // END
        else if(tokens[index] == "END") {
            fout<<"(AD,02)\n";
            for(int i=literalPoolStart;i<LITTAB.size();i++)
                LITTAB[i].address = LC++;
        }

        // LTORG
        else if(tokens[index] == "LTORG") {
            fout<<"(AD,05)\n";
            for(int i=literalPoolStart;i<LITTAB.size();i++)
                LITTAB[i].address = LC++;
            literalPoolStart = LITTAB.size();
            POOLTAB.push_back(literalPoolStart);
        }

        // DL
        else if(mclass == "DL") {
            fout<<"("<<mclass<<","<<opcode<<") (C,"<<tokens[index+1]<<")\n";
            if(tokens[index]=="DS")
                LC+=stoi(tokens[index+1]);
            else
                LC++;
        }

        // IS
        else if(mclass == "IS") {

            fout<<"(IS,"<<opcode<<") ";

            if(index+1 < tokens.size()) {

                string operand = tokens[index+1];

                if(operand[0]=='=') {
                    int lindex = searchLiteral(operand);
                    if(lindex==-1){
                        LITTAB.push_back({operand,-1});
                        lindex=LITTAB.size()-1;
                    }
                    fout<<"(L,"<<lindex+1<<")";
                }
                else {
                    int sindex = searchSymbol(operand);
                    if(sindex==-1){
                        SYMTAB.push_back({operand,-1,false,true});
                        sindex=SYMTAB.size()-1;
                    } else
                        SYMTAB[sindex].used=true;

                    fout<<"(S,"<<sindex+1<<")";
                }
            }
            fout<<"\n";
            LC++;
        }
    }

    fin.close();
    fout.close();
}

/* ================================
   PASS 2
================================ */

void pass2()
{
    ifstream fin("sample_IC.txt");

    if (!fin)
    {
        cout << "Error opening IC file\n";
        return;
    }

    cout << "\nFINAL MACHINE CODE\n";

    string line;
    int LC2 = 0;

    while (getline(fin, line))
    {
        if (line.find("(IS") != string::npos)
        {
            int pos = line.find(",") + 1;
            string opcode = line.substr(pos, 2);

            cout << LC2 << "  " << opcode << "  ";

            // Default register = 0
            cout << "0  ";

            if (line.find("(S,") != string::npos)
            {
                int sStart = line.find("(S,") + 3;
                int sEnd = line.find(")", sStart);
                int sIndex = stoi(line.substr(sStart, sEnd - sStart)) - 1;

                cout << SYMTAB[sIndex].address;
            }
            else if (line.find("(L,") != string::npos)
            {
                int lStart = line.find("(L,") + 3;
                int lEnd = line.find(")", lStart);
                int lIndex = stoi(line.substr(lStart, lEnd - lStart)) - 1;

                cout << LITTAB[lIndex].address;
            }
            else
            {
                cout << "000";
            }

            cout << endl;
            LC2++;
        }
    }

    fin.close();
}

/* ================================
   ERROR CHECK
================================ */

void errorCheck(){
    for(auto &s:SYMTAB){
        if(!s.defined && s.used)
            errors.push_back("Symbol not declared: "+s.name);
        if(s.defined && !s.used)
            errors.push_back("Warning: Symbol declared but not used: "+s.name);
    }
}

/* ================================
   DISPLAY TABLES
================================ */

void displayTables(){

    cout<<"\nSYMBOL TABLE\n";
    for(int i=0;i<SYMTAB.size();i++)
        cout<<i+1<<" "<<SYMTAB[i].name<<" "<<SYMTAB[i].address<<endl;

    cout<<"\nLITERAL TABLE\n";
    for(int i=0;i<LITTAB.size();i++)
        cout<<i+1<<" "<<LITTAB[i].literal<<" "<<LITTAB[i].address<<endl;

    cout<<"\nPOOL TABLE\n";
    for(int i=0;i<POOLTAB.size();i++)
        cout<<i+1<<" "<<POOLTAB[i]<<endl;

    cout<<"\nERRORS\n";
    for(string e:errors)
        cout<<e<<endl;
}

/* ================================
   MAIN
================================ */

int main(){

    pass1();
    errorCheck();
    displayTables();
    
    pass2();

    return 0;
}