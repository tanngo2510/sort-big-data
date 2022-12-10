#pragma once
#include <vector>
#include <iostream>
#include "review.h"

void Merge(vector<Review>& review, int left, int right);

void MergeSort(vector<Review>& review, int left, int right);

void SortFile(int count);

string MergeSortedFile(string folderPath, string path1, string path2);

void MergeSortedFile(string path1, string path2);