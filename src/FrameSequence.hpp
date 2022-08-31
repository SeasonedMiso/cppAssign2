#ifndef FrameSequence_H_
#define FrameSequence_H_
#include <string>
#include <vector>
using namespace std;

typedef struct
{
    string operation;
    string name;
} wArgs;
typedef struct
{
    vector<vector<int>> coordinate;
} frame;
typedef struct
{
    string filePath;
    int x1;
    int x2;
    int y1;
    int y2;
    int width;
    int height;
    vector<wArgs> w;
} inputArgs;

class FrameSequence
{
public:
    FrameSequence();
    FrameSequence(int *tResultArr, int *sResultArr, vector<vector<string>> wResultVecArray, string inFilename);
    ~FrameSequence();
    void printTest(inputArgs inArg);
    void createFrame();
    void frameLoop(inputArgs inputArgs);

private:
    vector<unsigned char **> imageSequence;
    // each element is a point to dynam allocated 2D image frame.
    // must be able to acces each pixel of each frame i, using imageSequence[i][y][x]
    // need class destructor
    // image in and out are PGM files
    // after frame extraction, delete pgmIn from mem.
    // consider using a buffer
};

#endif