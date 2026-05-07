#include <bits/stdc++.h>
using namespace std;

int main()
{
    ifstream mnt("mnt.txt");
    ifstream mdt("mdt.txt");
    ifstream intermediate("intermediate.txt");

    ofstream aptab("aptab.txt");
    ofstream expanded("expanded.txt");

    map<string,int> MNT;
    vector<string> MDT;

    string line;

    while(getline(mnt,line))
    {
        string name;
        int index;

        stringstream ss(line);
        ss>>name>>index;

        MNT[name]=index;
    }

    while(getline(mdt,line))
        MDT.push_back(line);

    while(getline(intermediate,line))
    {
        stringstream ss(line);

        string word,param;
        ss>>word;

        if(MNT.find(word)!=MNT.end())
        {
            int pos=1;

            while(ss>>param)
            {
                aptab<<"#"<<pos<<" "<<param<<endl;
                pos++;
            }

            int index=MNT[word]-1;

            while(MDT[index]!="MEND")
            {
                expanded<<MDT[index]<<endl;
                index++;
            }
        }

        else
        {
            expanded<<line<<endl;
        }
    }

    cout<<"PASS 2 completed. Expanded code generated.\n";
}