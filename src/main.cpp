#include "FrameSequence.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>

// make
// ./out/extractor ./resources/Examples/sloan_image.pgm -t 0 10 5000 5000 -s 640 480 -w invert invseq -w none sequence2

using namespace std;

bool fileExists(char *fileName)
{
    ifstream infile(fileName);
    return infile.good();
}
void badArg()
{
    cout << "error: user provided bad arguement";
    exit(1);
}
void badIn()
{
    cout << "error: bad input file";
    exit(1);
}
bool parseIntArgs(int argNum, int i, char *argv[], int *resArray)
{
    bool badConversion = false;
    for (int j = 1; j < argNum + 1; j++)
    {
        if (strcmp(to_string(atoi(argv[i + j])).c_str(), argv[i + j]) == 0)
        {
            resArray[j - 1] = atoi(argv[i + j]);
        }
        else
        {
            badConversion = true;
        }
    }
    if (!badConversion)
    {
        for (int j = 0; j < argNum; j++)
        {
            return true;
        }
    }
    return false;
}
int main(int argc, char *argv[])
{
    // string temp = argv[1];
    // string inFilename = (temp.find(".pgm")) != string::npos ? temp : "";
    char *inFilename = argv[1];
    // if (inFilename == "" || !fileExists(inFilename))
    // {
    //     badIn();
    // }
    int argsRead = 2;
    int wTotal = 0;
    int wCounter = 0;
    int tResultArr[4];
    int sResultArr[2];
    for (int i = 0; i < 4; i++)
    {
        tResultArr[i] = 0;
    }
    for (int i = 0; i < 2; i++)
    {
        sResultArr[i] = 0;
    }
    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-w") == 0)
        {
            wTotal++;
        }
    }
    vector<vector<string>> wResultVecArray;
    for (int i = 0; i < wTotal; i++)
    {
        wResultVecArray.push_back({"", ""});
    }
    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-t") == 0)
        {
            argsRead += 5;
            if (argc < argsRead)
            {
                badArg();
            }
            if (parseIntArgs(4, i, argv, tResultArr))
            {
                i += 4;
            }
            else
            {
                badArg();
            }
            if (tResultArr[2] - tResultArr[0] != tResultArr[3] - tResultArr[1])
            {
                cout << "inconsistent coords" << endl;
                badArg();
            }
            // check that x2 and y2 dist to x1 y1 is the same
            // starting origin(0, 10) and final origin(5000, 5000)??
            // how do we do this if its not the same both ways?
        }
        if (strcmp(argv[i], "-s") == 0)
        {
            argsRead += 3;
            if (argc < argsRead)
            {
                badArg();
            }
            if (parseIntArgs(2, i, argv, sResultArr))
            {
                i += 2;
            }
            else
            {
                badArg();
            }
        }
        if (strcmp(argv[i], "-w") == 0)
        {
            argsRead += 3;
            if (argc < argsRead)
            {
                badArg();
            }
            if ((strcmp(argv[i + 1], "none") && strcmp(argv[i + 1], "invert") && strcmp(argv[i + 1], "reverse") && strcmp(argv[i + 1], "revinvert")))
            {
                badArg();
            }
            for (int j = 0; j < 2; j++)
            {
                wResultVecArray[wCounter][j] = argv[i + j + 1];
            }
            wCounter++;
        }
    }
    FrameSequence *a = new FrameSequence;
    a->makeFrames(tResultArr, sResultArr, wResultVecArray, inFilename);
    delete (a);
}