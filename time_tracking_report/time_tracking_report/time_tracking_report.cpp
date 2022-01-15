#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <algorithm>
using namespace std;

int main()
{
    string fname;
    cout << "Enter file name: ";
    cin >> fname;
    cout << endl;

    fstream filein(fname, ios::in);
    vector <string> row;
    vector<vector<string>>data;
    string line, word;
    if (filein.is_open())
    {
        int j = 0;
        while (getline(filein, line))
        {  
            if (j != 0)
            {
                row.clear();
                stringstream s(line);
                int i = 0;
                while (getline(s, word, ';'))
                {
                    if (i == 0 || i == 6 || i == 7)
                    {
                        row.push_back(word);
                    }
                    i++;
                }
                data.push_back(row);
            }
            j++;
        }
    }
    else
        cout << "Couldn't open the file!";
    
    row.clear();
    row.push_back("Name");
    row.push_back("Month");
    row.push_back("Total Hours");

    for (int i = 0; i < data.size(); i++)
    {
        string month = data[i][1].substr(data[i][1].find_first_of('-')+1, data[i][1].find_last_of('-') - data[i][1].find_first_of('-')-1);
        string yyyy = data[i][1].substr(0, data[i][1].find_first_of('-'));
        string name = data[i][0];
        data[i].erase(data[i].begin());
        data[i].erase(data[i].begin());
        switch (stoi(month))
        {
        case 1:
            data[i].insert(data[i].begin(), name + "&January " + yyyy);
            break;
        case 2:
            data[i].insert(data[i].begin(), name + "&February " + yyyy);
            break;
        case 3:
            data[i].insert(data[i].begin(), name + "&March " + yyyy);;
            break;
        case 4:
            data[i].insert(data[i].begin(), name + "&April " + yyyy);
            break;
        case 5:
            data[i].insert(data[i].begin(), name + "&May " + yyyy);
            break;
        case 6:
            data[i].insert(data[i].begin(), name + "&June " + yyyy);
            break;
        case 7:
            data[i].insert(data[i].begin(), name + "&July " + yyyy);
            break;
        case 8:
            data[i].insert(data[i].begin(), name + "&August " + yyyy); 
            break;
        case 9:
            data[i].insert(data[i].begin(), name + "&September " + yyyy);
            break;
        case 10:
            data[i].insert(data[i].begin(), name + "&October " + yyyy);
            break;
        case 11:
            data[i].insert(data[i].begin(), name + "&November " + yyyy);   
            break;
        case 12:
            data[i].insert(data[i].begin(), name + "&December " + yyyy);   
            break;
        default:
            break;
        }
    }
    std::sort(data.begin(), data.end());
    for (int i = 0; i < data.size(); i++)
    {
        data[i].insert(data[i].begin() + 1, data[i][0].substr(data[i][0].find_first_of('&')+1));
        data[i][0] = data[i][0].substr(0, data[i][0].find_first_of('&'));
    }

    for (int i = 0; i < data.size()-1; i++)
    {        
        if (data[i][0]==data[i+1][0]&&data[i][1]==data[i+1][1])
        {
            int totalhours = stoi(data[i][2]) + stoi(data[i + 1][2]);
            data[i].pop_back();
            data[i].push_back(to_string(totalhours));
            data.erase(data.begin() + i + 1);
            i--;
        }
    }
    data.insert(data.begin(), row);

    fstream fout("result.csv", ios::out);
    for (int i = 0; i < data.size(); i++)
    {
        for (int j = 0; j < row.size(); j++)
        {
            cout << data[i][j] << "; ";
            fout << data[i][j] << "; ";
        }
        fout << endl;
        cout << endl;
    }
}