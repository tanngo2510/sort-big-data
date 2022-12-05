#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
using namespace std;


void printVector(vector<string> &v)
{
    for (int i = 0; i < v.size(); i++)
    {
        cout << v[i] << "\n";
    }
}


int main()
{
    ifstream file("test.csv",ios::binary);
    string line;
    vector<string> v;
    while (getline(file, line))
    {
        v.push_back(line);
    }
    sort(v.begin(), v.end());
    ofstream file2("test2.txt");
    for (int i = 0; i < v.size(); i++)
    {
        file2 << v[i] << "\n";
    }
    file.close();
    file2.close();
    return 0;
}
