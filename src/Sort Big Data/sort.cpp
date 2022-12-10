#include "sort.h"
#include "file_controller.h"

void Merge(vector<Review>& review, int left, int right){
    int middle = (left + right) / 2;

    int numberListOne = middle - left + 1;
    int numberListTwo = right - middle;

    vector<Review> leftList;
    vector<Review> rightList;

    for (int i = 0; i < numberListOne; i++){
        leftList.push_back(review.at(static_cast<std::vector<Review, std::allocator<Review>>::size_type>(left) + i));
    }
    for (int i = 0; i < numberListTwo; i++)
    {
        rightList.push_back(review.at(static_cast<std::vector<Review, std::allocator<Review>>::size_type>(middle) + 1 + i));
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

void MergeSort(vector<Review>& review, int left, int right){
	if (left >= right) return;

	int middle = (left + right) / 2;

	MergeSort(review, left, middle);
	MergeSort(review, middle + 1, right);
	Merge(review, left, right);
}

void SortFile(int count)
{
    CreateDir("..\\sorted");
    for (int i = 0; i < count; i++)
    {
        cout << "Sorting file: file" << i << ".csv" << "\r";
        string filePath = "..\\output\\file" + to_string(i) + ".csv";
        string line;
        vector<Review> review;
        fstream inFile;

        inFile.open(filePath, ios_base::in | ios_base::binary);
        IsFileOpen(inFile, filePath);

        while (getline(inFile, line))
            review.push_back(Review(line));

        inFile.close();

        MergeSort(review, 0, review.size() - 1);
        
        fstream outFile;
        filePath = "..\\sorted\\file" + to_string(i) + ".csv";
        outFile.open(filePath, ios_base::out | ios_base::binary);
        IsFileOpen(outFile, filePath);
        
        for (int j = 0; j < review.size(); j++)
            outFile << review.at(j).GetData() << endl;

        outFile.close();
    }

    string cmd = "rmdir /s /q ..\\output";
    system(cmd.c_str());
    cout << "\nSort done!" << endl;
}

string MergeSortedFile(string folderPath, string path1, string path2)
{
    // Merge 2 file.csv and return a string "fname.csv"
    string sortedPath = folderPath + "sorted_books_rating.csv";
    vector<Review> R1 = ReadCSV(folderPath + path1);
    vector<Review> R2 = ReadCSV(folderPath + path2);
    DeleteFile(folderPath + path1);
    DeleteFile(folderPath + path2);
    fstream ofs;
    ofs.open(sortedPath,ios_base::out | ios_base::binary);
    IsFileOpen(ofs, sortedPath);
    while (!R1.empty() && !R2.empty())
    {
        if (R1.front().GetId().compare(R2.front().GetId()) <= 0)
        {
            ofs << PopFirst(R1).GetData();
        }
        else
            ofs << PopFirst(R2).GetData();
    }
    if (R1.empty() && !R2.empty())
    {
        for (int i = 0; i < R2.size(); i++)
        {
            ofs << R2.at(i).GetData();
        }
    }
    if (R2.empty() && !R1.empty())
    {
        for (int i = 0; i < R1.size(); i++)
        {
            ofs << R1.at(i).GetData();
        }
    }
    ofs.close();
    return sortedPath;
}

void MergeSortedFile(string path1, string path2)
{
    cout << "Sort file: " << path1 << " and file: " << path2 << "\r";
    MergeSortedFile("..\\sorted\\", path1, path2);
}