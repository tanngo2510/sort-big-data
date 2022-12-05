#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <sys/stat.h>

#define PATH_CSV_TEST "..\\test.csv"
#define PATH_CSV "..\\Books_rating.csv"
#define SIZE 1000

using namespace std;

class Review
{
private:
    string id;
    string title;
    string price;
    string userId;
    string profileName;
    string reviewHelpfulness;
    string reviewScore;
    string reviewTime;
    string reviewSummary;
    string reviewText;

public:
    Review(string text)
    {
        stringstream ss(text);
        string token;
        vector<string> tokens;
        while (getline(ss, token, ','))
        {
            tokens.push_back(token);
        }
        this->id = tokens[0];
        this->title = tokens[1];
        this->price = tokens[2];
        this->userId = tokens[3];
        this->profileName = tokens[4];
        this->reviewHelpfulness = tokens[5];
        this->reviewScore = tokens[6];
        this->reviewTime = tokens[7];
        this->reviewSummary = tokens[8];
        this->reviewText = tokens[9];
    }
    string GetId()
    {
        return id;
    }
    string GetData()
    {
        string str = id + "," + title + "," + price + "," + userId + "," + profileName + "," + reviewHelpfulness + "," + reviewScore + "," + reviewTime + "," + reviewSummary + "," + reviewText;
        return str;
    }
};

bool isDirExist(string path)
{
    struct stat info;
    if (stat(path.c_str(), &info) != 0)
        return false;
    else if (info.st_mode & S_IFDIR)
        return true;
    else
        return false;
}

void SplitFile(string path)
{
    fstream InFile;
    InFile.open(path, ios_base::in | ios_base::binary);
    if (!InFile.is_open())
    {
        cout << "Error opening InFile" << endl;
        exit(1);
    }
    string header;
    string line;
    int count = 0;
    int fileCount = 0;
    if (!isDirExist("..\\output"))
    {
        string cmd = "mkdir --force ..\\output";
        system(cmd.c_str());
    }
    string fileName = "..\\output\\file" + to_string(fileCount) + ".csv";
    fstream OutFile;
    OutFile.open(fileName, ios_base::out | ios_base::binary);
    if (!OutFile.is_open())
    {
        cout << "Error opening OutFile" << endl;
        exit(1);
    }
    getline(InFile, header);
    while (getline(InFile, line))
    {
        if (count == SIZE)
        {
            OutFile.close();
            fileCount++;
            fileName = "..\\output\\file" + to_string(fileCount) + ".csv";
            OutFile.open(fileName, ios_base::out | ios_base::binary);
            if (!OutFile.is_open())
            {
                cout << "Error opening OutFile" << endl;
                exit(1);
            }
            count = 0;
        }
        OutFile << line << endl;
        count++;
    }
    OutFile.close();
    InFile.close();
}

void Merge(vector<Review> review, int left, int right)
{
    int middle = (left + right) / 2;

    int numberListOne = middle - left + 1;
    int numberListTwo = right - middle;

    vector<Review> leftList;
    vector<Review> rightList;

    for (int i = 0; i < numberListOne; i++)
    {
        leftList.push_back(review.at(left + i));
    }
    for (int i = 0; i < numberListTwo; i++)
    {
        rightList.push_back(review.at(middle + 1 + i));
    }

    int indexLeft = 0;
    int indexRight = 0;
    int indexMerge = left;

    while (indexLeft < numberListOne && indexRight < numberListTwo)
    {
        if (leftList.at(indexLeft).GetId().compare(rightList.at(indexRight).GetId()) <= 0)
        {
            review.at(indexMerge) = leftList.at(indexLeft);
            indexLeft++;
        }
        else
        {
            review.at(indexMerge) = rightList.at(indexRight);
            indexRight++;
        }
        indexMerge++;
    }

    while (indexLeft < numberListOne)
    {
        review.at(indexMerge) = leftList.at(indexLeft);
        indexLeft++;
        indexMerge++;
    }

    while (indexRight < numberListTwo)
    {
        review.at(indexMerge) = rightList.at(indexRight);
        indexRight++;
        indexMerge++;
    }
}

void MergeSort(vector<Review> review, int left, int right)
{
    if (left >= right)
        return;
    int middle = (left + right) / 2;
    MergeSort(review, left, middle);
    MergeSort(review, middle + 1, right);
    Merge(review, left, right);
}

int main()
{
    SplitFile(PATH_CSV_TEST);
    cout << "Split file success" << endl;
    vector<Review> review;
    fstream InFile;
    InFile.open("..\\output\\file0.csv", ios_base::in | ios_base::binary);
    if (!InFile.is_open())
    {
        cout << "Error opening InFile" << endl;
        exit(1);
    }
    cout << "Open file0.csv success" << endl;
    string line;
    while (getline(InFile, line))
    {
        review.push_back(Review(line));
    }
    InFile.close();
    cout << "Read file0.csv success" << endl;
    cout << "Review size: " << review.size() << endl;
    MergeSort(review, 0, review.size() - 1);
    cout << "Merge sort success" << endl;
    fstream OutFile;
    OutFile.open("..\\sorted\\file0.csv", ios_base::out | ios_base::binary);
    if (!OutFile.is_open())
    {
        cout << "Error opening OutFile" << endl;
        exit(1);
    }
    cout << "Open file0.csv success" << endl;
    for (int i = 0; i < review.size(); i++)
    {
        OutFile << review.at(i).GetData() << endl;
    }
    OutFile.close();
    cout << "Write file0.csv success" << endl;
    return 0;
}