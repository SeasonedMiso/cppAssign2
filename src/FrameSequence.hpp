#ifndef FrameSequence_H_
#define FrameSequence_H_
#include <string>
#include <vector>
using namespace std;

typedef struct PGMImage
{
    char pgmType[3];
    unsigned char **data;
    unsigned int width;
    unsigned int height;
    unsigned int maxValue;
} PGMImage;
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
    char *filePath;
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
    void makeFrames(int *tResultArr, int *sResultArr, vector<vector<string>> wResultVecArray, char *inFilename);
    ~FrameSequence();
    void commentParse(FILE *filepointer);
    bool openPGM(PGMImage *pgm,
                 const char *filename);
    void printImageDetails(PGMImage *pgm,
                           const char *filename);
    bool writePGM(PGMImage *pgm,
                  const char *filename);
    void closePGM(PGMImage *pgm);
    void defaultSequence(PGMImage *pgm, char *outName);
    PGMImage *invertPGM(PGMImage *pgm);
    void reversePGM(PGMImage *pgm, char *outName);

private:
    vector<unsigned char **> imageSequence;
    PGMImage *pgm;
    inputArgs inputArgs;
};

#endif