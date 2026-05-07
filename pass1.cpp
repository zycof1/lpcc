#include <bits/stdc++.h>
using namespace std;

int main()
{
    ifstream input("input.txt");

    ofstream mnt("mnt.txt");
    ofstream mdt("mdt.txt");
    ofstream pntab("pntab.txt");
    ofstream intermediate("intermediate.txt");

    if(!input)
    {
        cout<<"Input file not found\n";
        return 0;
    }

    string line;
    bool macro = false;
    int mdtIndex = 1;

    while(getline(input,line))
    {
        if(line == "MACRO")
        {
            macro = true;

            getline(input,line);
            stringstream ss(line);

            string macroName,param;

            ss>>macroName;

            mnt<<macroName<<" "<<mdtIndex<<endl;

            int pos=1;

            while(ss>>param)
            {
                pntab<<macroName<<" "<<param<<" #"<<pos<<endl;
                pos++;
            }
        }

        else if(line == "MEND")
        {
            macro=false;
            mdt<<"MEND"<<endl;
            mdtIndex++;
        }

        else if(macro)
        {
            mdt<<line<<endl;
            mdtIndex++;
        }

        else
        {
            intermediate<<line<<endl;
        }
    }

    input.close();
    mnt.close();
    mdt.close();
    pntab.close();
    intermediate.close();

    cout<<"PASS 1 completed. Files generated.\n";
}