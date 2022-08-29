#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include "ass1.hpp"

using namespace std;

typedef struct
{
    string tagName;
    int tagNum;
    string text;
} TagStruct;

ass1::ass1()
{
    vector<TagStruct> tagStructVec;
    ifstream t("text/simple.txt");
    stringstream buffer;
    buffer << t.rdbuf();
    string s = buffer.str();

    // Stores address of
    // a character of str
    int itty = 0;
    for (int i = 0; i < 2; i++)
    {
        size_t foundStart = s.find("<", itty);
        size_t foundEnd = s.find(">", itty);

        string currentTagName = s.substr(foundStart + 1, foundEnd - foundStart - 1);
        string closeTag = "</" + currentTagName + ">";
        cout << currentTagName + ":" + closeTag << "\n";
        itty = s.find(closeTag, itty) + closeTag.length();

        cout << "---sItty---"
             << "\n"
             << s.substr(itty, s.length()) << "\n"
             << "--eItty----"
             << "\n";
        if (tagStructVec.size() == 0)
        {
            string tagText = s.substr(foundEnd + 1, s.find(closeTag) - foundEnd - 1);
            TagStruct ts = {.tagName = currentTagName, .text = tagText, .tagNum = 1};
            tagStructVec.push_back(ts);
        }
        else
        {
            for (int j = 0; j < tagStructVec.size(); j++)
            {
                if (tagStructVec[j].tagName == currentTagName)
                {
                    tagStructVec[j].tagNum++;
                    tagStructVec[j].text += ":" + s.substr(foundEnd + 1, s.find(closeTag) - foundEnd - 1);
                    break;
                }
                else if (j == tagStructVec.size() - 1)
                {
                    string tagText = s.substr(foundEnd + 1, s.find(closeTag) - foundEnd - 1);
                    TagStruct ts = {.tagName = currentTagName, .text = tagText, .tagNum = 1};
                    tagStructVec.push_back(ts);
                }
            }
        }
    }

    for (TagStruct ts : tagStructVec)
    {
        cout << ts.tagName << "\n";
        cout << ts.tagNum << "\n";
        cout << ts.text << "\n";
        cout << "//////"
             << "\n";
    }
}


