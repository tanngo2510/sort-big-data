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
    string line;
    string id;
    // string title;
    // string price;
    // string userId;
    // string profileName;
    // string reviewHelpfulness;
    // string reviewScore;
    // string reviewTime;
    // string reviewSummary;
    // string reviewText;

public:
    Review(string text)
    {
        this->line = text;
        stringstream ss(text);
        string token;
        vector<string> tokens;
        while (getline(ss, token, ','))
        {
            tokens.push_back(token);
        }
        this->id = tokens[0];
        // this->title = tokens[1];
        // this->price = tokens[2];
        // this->userId = tokens[3];
        // this->profileName = tokens[4];
        // this->reviewHelpfulness = tokens[5];
        // this->reviewScore = tokens[6];
        // this->reviewTime = tokens[7];
        // this->reviewSummary = tokens[8];
        // this->reviewText = tokens[9];
    }
    string GetId()
    {
        return id;
    }
    string GetLine()
    {
        return this->line;
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

int SplitFile(string path)
{
    int countFile = 0;
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
    int fileCount = 1;
    if (!isDirExist("..\\output"))
    {
        string cmd = "mkdir ..\\output";
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
            countFile++;
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
    return countFile;
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

void SortFile(int count)
{
    if (!isDirExist("..\\sorted"))
    {
        string cmd = "mkdir ..\\sorted";
        system(cmd.c_str());
    }
    for (int f = 1; f <= count; f++)
    {
        cout << " Sorting file " << f << "\r";
        vector<Review> review;
        fstream InFile;
        InFile.open("..\\output\\file" + to_string(f) + ".csv", ios_base::in | ios_base::binary);
        if (!InFile.is_open())
        {
            cout << "Error opening InFile" << endl;
            exit(1);
        }
        string line;
        while (getline(InFile, line))
        {
            review.push_back(Review(line));
        }
        InFile.close();
        MergeSort(review, 0, review.size() - 1);
        fstream OutFile;
        OutFile.open("..\\sorted\\file" + to_string(f) + ".csv", ios_base::out | ios_base::binary);
        if (!OutFile.is_open())
        {
            cout << "Error opening OutFile" << endl;
            exit(1);
        }
        for (int i = 0; i < review.size(); i++)
        {
            OutFile << review.at(i).GetLine() << endl;
        }
        OutFile.close();
    }
    string cmd = "del ..\\output";
    system(cmd.c_str());
}

// class MergeClass
// {
// private:
//     string filename;
//     Review *review;

// public:
//     MergeClass(string filename)
//     {
//         this->filename = filename;
//         fstream file;
//         file.open(filename, ios_base::in | ios_base::binary);
//         if (!file.is_open())
//         {
//             cout << "Error opening file" << endl;
//             exit(1);
//         }
//         string line;
//         getline(file, line);
//         this->review = new Review(line);
//     }
//     string getId()
//     {
//         return review->GetId();
//     }
// };

// void combine(int count){
//     vector<MergeClass> m;
//     for (int i = 1; i <= count; i++)
//     {
//         m.push_back(MergeClass("..\\sorted\\file" + to_string(i) + ".csv"));
//     }
//     MergeClass min = m.front();

// }

int main()
{
    int count = SplitFile(PATH_CSV_TEST);
    cout << "Number of file: " << count << endl;
    SortFile(count);
    return 0;
}
