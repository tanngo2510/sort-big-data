#include "review.h"
#include <iostream>

Review::Review(string data) {
	this->data = data;
	stringstream ss(data);
	getline(ss, this->id, ',');
}

string Review::GetId() {
	return this->id;
}

string Review::GetData() {
	return this->data;
}