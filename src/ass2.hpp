#ifndef ass2_H_
#define ass2_H_
#include <string>
#include <vector>
using namespace std;

class ass2
{
public:
    ass2();
    // ass2(int *tResultArr, int *sResultArr, vector<string[2]> wResultVecArray);
    ass2(int *tResultArr, int *sResultArr, vector<vector<string>> wResultVecArray);

    // ass2(int *tResultArr, int *sResultArr, string *wResultArray);

private:
    vector<unsigned char **>
        imageSequence;
    // each element is a point to dynam allocated 2D image frame.
    // must be able to acces each pixel of each frame i, using imageSequence[i][y][x]
    // need class destructor
    // image in and out are PGM files
    // after frame extraction, delete pgmIn from mem.
    // consider using a buffer
};

#endif