#pragma once
#include<iostream>
#include <vector>
#include <fstream>
#include <sys/stat.h>
#include "review.h"

constexpr auto SIZE = 10000;

using namespace std;

void IsFileOpen(fstream &file, string path);

bool IsDirExist(string path);

void CreateDir(string path);

int SplitFile(string path);

vector<Review> ReadCSV(string path);

Review PopFirst(vector<Review>& R);

void DeleteFile(string path);

string GetHeader(string path);

void AddHeader(string path);