#include "file_controller.h"

void IsFileOpen(fstream &file, string path) {
	if (!file.is_open()) {
		string filename = path.substr(path.rfind("\\") + 1);
		cout << "ERROR:: Cannot open file: " << filename << endl;
		exit(-1);
	}
}

bool IsDirExist(string path)
{
	struct stat info;

	if (stat(path.c_str(), &info) != 0) return false;
	if (info.st_mode & S_IFDIR) return true;
	return false;
}

void CreateDir(string path)
{
	if (IsDirExist(path)) return;

	string command = "mkdir " + path;
	system(command.c_str());
}

int SplitFile(string path) {
	fstream inFile;
	inFile.open(path, ios_base::in | ios_base::binary);
	IsFileOpen(inFile, path);

	string header;
	string line;
    int count = 0;
    int countFile = 0;

	getline(inFile, header);

    string folderPath = "..\\output";
	CreateDir(folderPath);
    
    string filePath = folderPath + "\\file" + to_string(countFile) + ".csv";
    fstream outFile;
    outFile.open(filePath, ios_base::out | ios_base::binary);
    IsFileOpen(outFile, filePath);
    cout << "Split to file: file" + to_string(countFile) + ".csv" << "\r";
    while (getline(inFile, line))
    {
        if (count == SIZE)
        {
            countFile++;
            outFile.close();
            filePath = folderPath + "\\file" + to_string(countFile) + ".csv";
            cout << "Split to file: file" + to_string(countFile) + ".csv" << "\r";
            outFile.open(filePath, ios_base::out | ios_base::binary);
            IsFileOpen(outFile, filePath);
            count = 0;
        }
        outFile << line << endl;
        count++;
    }
    outFile.close();
    inFile.close();
    cout << "\nSplit done!" << endl;
    return ++countFile;
}

vector<Review> ReadCSV(string path)
{
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

Review PopFirst(vector<Review>& R)
{
    Review review = R.front();
    if (R.size() == 1)
        R.pop_back();
    else
        R.erase(R.begin());
    return review;
}

void DeleteFile(string path)
{
    string cmd = "del " + path;
    system(cmd.c_str());
}

string GetHeader(string path)
{
    fstream file;
    file.open(path, ios_base::in | ios_base::binary);
    string header;
    getline(file, header);
    file.close();
    return header;
}

void AddHeader(string path) {
    string header = GetHeader("..\\Books_rating.csv");
    fstream inFile;
    inFile.open(path, ios_base::in | ios_base::binary);
    IsFileOpen(inFile, path);
    fstream outFile;
    outFile.open("..\\temp.csv", ios_base::out | ios_base::binary);
    IsFileOpen(outFile, "..\\temp.csv");
    string line;
    outFile << header << endl;
    while (getline(inFile, line)) {
        outFile << line;
    }
    outFile.close();
    inFile.close();
    DeleteFile(path);
    string cmd = "move ..\\temp.csv ..\\sorted_books_rating.csv";
    system(cmd.c_str());
}