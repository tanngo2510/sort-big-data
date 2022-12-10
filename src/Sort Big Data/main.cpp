#include <iostream>
#include "review.h"
#include "sort.h"
#include "file_controller.h"

constexpr auto PATH_CSV = "..\\Books_rating.csv";
constexpr auto PATH_CSV_TEST = "..\\test.csv";

/*
	EXIT CODE:
	0: normal
	-1: cannot open file
*/

int main() {
	string path = PATH_CSV;
	string _continue;
	string filename = path.substr(path.rfind("\\") + 1);
	cout << "File `"<< filename << "` must same folder with folder `Sort Big Data`" << endl;
	cout << "Get any key to continue...";
	
	getline(cin, _continue);
	int count = SplitFile(path);
	SortFile(count);
	fstream outFile;
	outFile.open("..\\sorted\\sorted_books_rating.csv", ios_base::out | ios_base::binary);
	outFile.close();
	for (int i = 0; i < count; i++) {
		MergeSortedFile("sorted_books_rating.csv", "file" + to_string(i) + ".csv");
	}
	cout << endl;
	string cmd = "move ..\\sorted\\sorted_books_rating.csv ..\\sorted_books_rating.csv";
	system(cmd.c_str());
	AddHeader("..\\sorted_books_rating.csv");
	cmd = "rmdir /s /q ..\\sorted";
	system(cmd.c_str());
	cout << "\nDone!" << endl;
	
	return 0;
}