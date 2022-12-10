#pragma once
#include <string>
#include <sstream>

using namespace std;

class Review
{
private:
	string data;
	string id;
public:
	Review(string data);
	string GetId();
	string GetData();
};


