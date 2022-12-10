#include 

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
