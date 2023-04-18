#include "importfiles.hpp"
#include "utils.hpp"

using namespace std;

vector<vector<string>> importFile(string filename)
{
    vector<vector<string>> content;
    vector<string> row;
    string line, word;

    fstream file(filename, ios::in);
    if (file.is_open())
    {
        while (getline(file, line))
        {
            row.clear();

            stringstream str(line);

            while (getline(str, word, ','))
            {
                removeEscapeCharacters(word);
                row.push_back(word);
            }
            content.push_back(row);
        }
    }
    else
        cout << "Could not open the file\n";

    return content;
}

vector<double> getValue(string filename, int column)
{
    vector<double> content;
    vector<string> row;
    string line, word;

    fstream file(filename, ios::in);
    if (file.is_open())
    {
        while (getline(file, line))
        {
            row.clear();

            stringstream str(line);

            while (getline(str, word, ','))
            {
                removeEscapeCharacters(word);
                row.push_back(word);
            }
            if (row[column] == "AVERAGE")
            {
                content.push_back(1);
            }
            else if (row[column] == "LOW")
            {
                content.push_back(0);
            }
            else if (row[column] == "HIGH")
            {
                content.push_back(2);
            }
            else if (row[column] == "MEDIUM")
            {
                content.push_back(1);
            }
            else if (row[column] == "BAD")
            {
                content.push_back(0);
            }
            else if (row[column] == "GOOD")
            {
                content.push_back(2);
            }
            else if (row[column] == "A")
            {
                content.push_back(5);
            }
            else if (row[column] == "B")
            {
                content.push_back(4);
            }
            else if (row[column] == "C")
            {
                content.push_back(3);
            }
            else if (row[column] == "D")
            {
                content.push_back(2);
            }
            else if (row[column] == "E")
            {
                content.push_back(1);
            }
            else if (row[column] == "F")
            {
                content.push_back(0);
            }
            else
            {
                content.push_back(stod(row[column]));
            }
        }
    }
    else
        cout << "Could not open the file\n";
    return content;
}

vector<pair<string, string>> getLinkValues(string filename)
{
    vector<pair<string, string>> content;
    vector<string> row;
    string line, word;

    fstream file(filename, ios::in);
    if (file.is_open())
    {
        while (getline(file, line))
        {
            row.clear();

            stringstream str(line);

            while (getline(str, word, ','))
                removeEscapeCharacters(word);
            row.push_back(word);
            pair<string, string> pair = {row[0], row[1]};
            content.push_back(pair);
        }
    }
    else
        cout << "Could not open the file\n";
    return content;
}