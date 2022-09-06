#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "FrameSequence.hpp"
using namespace std;

FrameSequence::FrameSequence(int *tResultArr, int *sResultArr, vector<vector<string>> wResultVecArray, char *inFilename)
{
    inputArgs inputArgs;
    inputArgs.filePath = inFilename;
    inputArgs.width = sResultArr[0];
    inputArgs.height = sResultArr[1];
    inputArgs.x1 = tResultArr[0];
    inputArgs.y1 = tResultArr[1];
    inputArgs.x2 = tResultArr[2];
    inputArgs.y2 = tResultArr[3];
    for (int j = 0; j < wResultVecArray.size(); j++)
    {
        wArgs tempW;
        inputArgs.w.push_back(tempW);
        inputArgs.w[j].operation = wResultVecArray[j][0];
        inputArgs.w[j].name = wResultVecArray[j][1];
    }

    PGMImage *pgm = (PGMImage *)malloc(sizeof(PGMImage));
    // const char *ipfile;
    if (openPGM(pgm, inputArgs.filePath))
    {
        writePGM(pgm, "./out/outName.pgm");
        // printImageDetails(pgm, inputArgs.filePath);
        // cout << pgm->data[0];
    }
}
FrameSequence::FrameSequence()
{
    inputArgs inputArgs;
    inputArgs.width = 0;
    inputArgs.height = 0;
    inputArgs.x1 = 0;
    inputArgs.y1 = 0;
    inputArgs.x2 = 0;
    inputArgs.y2 = 0;
}
FrameSequence::~FrameSequence()
{
    // deallocate each frame;
    cout << "\n Destructor executed";
}

bool FrameSequence::writePGM(PGMImage *pgm,
                             const char *filename)
{
    ofstream myfile(filename, ios::binary);
    myfile.write("P5\n", 3);
    myfile.write(to_string(pgm->width).c_str(), 2);
    myfile.write(" ", 1);
    myfile.write(to_string(pgm->height).c_str(), 2);
    myfile.write("\n255\n\n", 6);
    cout << pgm->width << endl;
    cout << pgm->height << endl;
    for (int i = 0;
         i < pgm->height; i++)
    {
        myfile.write((char *)pgm->data[i], (pgm->width));
    }
    myfile.close();
    return false;
}

void FrameSequence::commentParse(FILE *filePointer)
{
    int ch;
    char line[100];
    // Ignore any blank lines
    while ((ch = fgetc(filePointer)) != EOF && isspace(ch))
        ;
    if (ch == '#')
    {
        fgets(line, sizeof(line), filePointer);
        commentParse(filePointer);
    }
    else
        fseek(filePointer, -1, SEEK_CUR);
}
// Function to open the input a PGM
// file and process it
bool FrameSequence::openPGM(PGMImage *pgm,
                            const char *filename)
{
    FILE *pgmFile = fopen(filename, "rb");
    // Check for file
    if (pgmFile == NULL)
    {
        printf("File not found\n");
        return false;
    }
    commentParse(pgmFile);
    // Parse header
    fscanf(pgmFile, "%s",
           pgm->pgmType);
    commentParse(pgmFile);
    fscanf(pgmFile, "%d %d",
           &(pgm->width),
           &(pgm->height));
    commentParse(pgmFile);
    fscanf(pgmFile, "%d", &(pgm->maxValue));
    commentParse(pgmFile);

    // Allocating memory
    pgm->data = (unsigned char **)malloc(pgm->height * sizeof(unsigned char *));
    // Storing data
    if (pgm->pgmType[1] == '5')
    {
        fgetc(pgmFile);
        for (int i = 0;
             i < pgm->height; i++)
        {
            pgm->data[i] = (unsigned char *)malloc(pgm->width * sizeof(unsigned char));
            if (pgm->data[i] == NULL)
            {
                fprintf(stderr,
                        "malloc failed\n");
                exit(1);
            }
            fread(pgm->data[i],
                  sizeof(unsigned char),
                  pgm->width, pgmFile);
        }
    }
    fclose(pgmFile);
    return true;
}

// Function to print the file details
void FrameSequence::printImageDetails(PGMImage *pgm,
                                      const char *filename)
{
    FILE *pgmfile = fopen(filename, "rb");

    // Retrieving the file extension
    const char *ext = strrchr(filename, '.');

    if (!ext)
        printf("No extension found"
               "in file %s",
               filename);
    else
        printf("File format"
               "    : %s\n",
               ext + 1);

    printf("PGM File type  : %s\n",
           pgm->pgmType);

    // Print type of PGM file, in ascii
    // and binary format
    if (!strcmp(pgm->pgmType, "P2"))
        printf("PGM File Format:"
               "ASCII\n");
    else if (!strcmp(pgm->pgmType,
                     "P5"))
        printf("PGM File Format:"
               " Binary\n");

    printf("Width of img   : %d px\n",
           pgm->width);
    printf("Height of img  : %d px\n",
           pgm->height);
    printf("Max Gray value : %d\n",
           pgm->maxValue);

    // close file
    fclose(pgmfile);
}
