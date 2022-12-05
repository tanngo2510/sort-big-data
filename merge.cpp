#include "merge.h"

using namespace std;

vector<string> MergeUsingArrayIndices(vector<string> & LHS,
int START, int MID, int MIDPLUSONE, int END)
{

    vector<string> ToReturn;
    int i = 0;  // LHS index
    int j = MIDPLUSONE;  // RHS index

    while ((i <= MID) && (j <= END))
    {
        if (LHS[i] < LHS[j])
        {
            ToReturn.push_back(LHS[i]);
            ++i;
        }
        else
        {
            ToReturn.push_back(LHS[j]);
            ++j;
        }
    }

    while (i <= MID)
    {
        ToReturn.push_back(LHS[i]);
        ++i;
    }

    while (j <= END)
    {
        ToReturn.push_back(LHS[j]);
        ++j;
    }
    for (int k = 0; k < ToReturn.size(); ++k)
    {
        LHS[k] = ToReturn[k];
    }
    return ToReturn;

}

void MergeSort(vector<string> & VECTOR, int START, int END)
{

if (END > START)
{
    int MID = (START + END) / 2;
    MergeSort(VECTOR, START, MID);
    MergeSort(VECTOR, MID + 1, END);
    MergeUsingArrayIndices(VECTOR, START, MID, (MID+1), END);
}
}

void Merge(std::vector<string> & VECTOR)
{

MergeSort(VECTOR, 0, VECTOR.size()-1);
}