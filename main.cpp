#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

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
    Review()
    {
        id = "";
        title = "";
        price = "";
        userId = "";
        profileName = "";
        reviewHelpfulness = "";
        reviewScore = "";
        reviewTime = "";
        reviewSummary = "";
        reviewText = "";
    }
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
    string GetTitle()
    {
        return title;
    }
    string GetPrice()
    {
        return price;
    }
    string GetUserId()
    {
        return userId;
    }
    string GetProfileName()
    {
        return profileName;
    }
    string GetReviewHelpfulness()
    {
        return reviewHelpfulness;
    }
    string GetReviewScore()
    {
        return reviewScore;
    }
    string GetReviewTime()
    {
        return reviewTime;
    }
    string GetReviewSummary()
    {
        return reviewSummary;
    }
    string GetReviewText()
    {
        return reviewText;
    }
};

int main()
{

    return 0;
}