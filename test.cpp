#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

void printVector(vector<string>&v)
{
    for (int i=0;i<v.size();i++)
    {
        cout<<v[i]<<"\n";
    }
    
}
int main()
{
    string fname="test.csv";
    vector<vector<string>> content;
    vector<string> row;
    string line, word;
    
    fstream file (fname, ios::in);
    if(file.is_open())
    {
    while(getline(file, line))
    {
    row.clear();
    
    stringstream str(line);
    
    while(getline(str, word, ','))
    row.push_back(word);
    content.push_back(row);
    }
    }
    else
    cout<<"Could not open the file\n";
    ofstream ofs("test.txt");
    // for(int i=0;i<content.size();i++)
    // {
    // for(int j=0;j<content[i].size();j++)
    // {
    //     ofs << content[i][j]<<" ";
    // }
    // ofs <<"\n";
    // }
    if (content[152][0]<content[12][0])
    {
        cout<<"true";
    }
    
    
    
    return 0;
}