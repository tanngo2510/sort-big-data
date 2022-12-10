#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <sys/stat.h>

#define PATH_CSV_TEST "test.csv"
#define PATH_CSV " Books_rating.csv"
#define SIZE 10000

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
    if (!isDirExist("output"))
    {
        string cmd = "mkdir  output";
        system(cmd.c_str());
    }
    string fileName = "output\\file" + to_string(fileCount) + ".csv";
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
            fileName = "output\\file" + to_string(fileCount) + ".csv";
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
    cout << countFile <<"\n";

    return ++countFile;
}

void Merge(vector<Review> &review, int left, int right)
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

void MergeSort(vector<Review> &review, int left, int right)
{
    if (left >= right)
        return;
    int middle = (left + right) / 2;
    MergeSort(review, left, middle);
    MergeSort(review, middle + 1, right);
    Merge(review, left, right);
}

int SortFile(int count)
{
    if (!isDirExist("sorted"))
    {
        string cmd = "mkdir sorted";
        system(cmd.c_str());
    }
    for (int f = 1; f <= count; f++)
    {
        cout << " Sorting file " << f << "\r";
        vector<Review> review;
        fstream InFile;
        InFile.open("output\\file" + to_string(f) + ".csv", ios_base::in | ios_base::binary);
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
        OutFile.open("sorted\\file" + to_string(f) + ".csv", ios_base::out | ios_base::binary);
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
    // string cmd = "del output";
    // system(cmd.c_str());
    return count++;
}
vector<Review> read_csv(string path)
{
    // read file.csv and return a vector of Review obj
    vector<Review> R;
    string line;
    fstream inFile;
    inFile.open(path, ios::in | ios::binary);
    while (getline(inFile, line))
    {
        R.push_back(Review(line));
    }
    inFile.close();
    return R;
}
Review pop_first(vector<Review> &R)
{
    Review review = R.front();
    if (R.size() == 1)
    {
        R.pop_back();
    }
    else
        R.erase(R.begin());
    return review;
}
void deleteFile(string path)
{
    string cmd = "del " + path;
    system(cmd.c_str());
}
string MergeSortedFile(string folderPath, string path1, string path2)
{
    // Merge 2 file.csv and return a string "fname.csv"
    string sortedPath =folderPath + "output.csv";
    vector<Review> R1 = read_csv(folderPath + path1);
    vector<Review> R2 = read_csv(folderPath + path2);
    deleteFile(folderPath + path1);
    deleteFile(folderPath + path2);
    ofstream ofs(sortedPath);
    while (!R1.empty() && !R2.empty())
    {
        if (R1.front().GetId().compare(R2.front().GetId()) <= 0)
        {
            ofs << pop_first(R1).GetLine();
        }
        else
            ofs << pop_first(R2).GetLine();
    }
    if (R1.empty() && !R2.empty())
    {
        for (int i = 0; i < R2.size(); i++)
        {
            ofs << R2[i].GetLine();
        }
    }
    if (R2.empty() && !R1.empty())
    {
        for (int i = 0; i < R1.size(); i++)
        {
            ofs << R1[i].GetLine();
        }
    }
    ofs.close();
    return sortedPath;
}
int count =0;
void MergeSortedFile(string path1, string path2)
{
    MergeSortedFile(".\\sorted\\", path1, path2);
}
void MergeAll()
{
    int count =SortFile(SplitFile(PATH_CSV_TEST));
    for (int i = 1; i <=count +1; i++)
    {
        MergeSortedFile("output.csv","file"+to_string(i)+".csv");
    }
}

int main()
{
    MergeAll();
    return 0;
}