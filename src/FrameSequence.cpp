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

// deal with 1st pixel of each row

void FrameSequence::makeFrames(int *tResultArr, int *sResultArr, vector<vector<string>> wResultVecArray, char *inFilename)
{
    inputArgs.filePath = inFilename;
    inputArgs.width = sResultArr[0];
    inputArgs.height = sResultArr[1];
    inputArgs.x1 = tResultArr[0];
    inputArgs.y1 = tResultArr[1];
    inputArgs.x2 = tResultArr[2];
    inputArgs.y2 = tResultArr[3];
    bool backwards = false;

    // && inputArgs.y1 > inputArgs.y2
    if (inputArgs.x1 > inputArgs.x2 && inputArgs.y1 > inputArgs.y2)
    {
        backwards = true;
        int tempX = inputArgs.x2;
        int tempY = inputArgs.y2;
        inputArgs.x2 = inputArgs.x1;
        inputArgs.y2 = inputArgs.y1;
        inputArgs.x1 = tempX;
        inputArgs.x1 = tempY;
    }
    // cout << inputArgs.x2;
    for (int j = 0; j < wResultVecArray.size(); j++)
    {
        wArgs tempW;
        inputArgs.w.push_back(tempW);
        inputArgs.w[j].operation = wResultVecArray[j][0];
        inputArgs.w[j].name = wResultVecArray[j][1];
    }

    pgm = (PGMImage *)malloc(sizeof(PGMImage));
    if (openPGM(pgm, inputArgs.filePath))
    {
        if (inputArgs.w.size() == 0)
        {
            defaultSequence(pgm, (char *)"./out/default.pgm");
        }
        else
        {
            for (int j = 0; j < inputArgs.w.size(); j++)
            {
                if (strcmp(inputArgs.w[j].operation.c_str(), "none") == 0)
                {
                    string path = "./out/" + inputArgs.w[j].name;

                    if (backwards)
                    {
                        reversePGM(pgm, (char *)path.c_str());
                    }
                    else
                    {
                    defaultSequence(pgm, (char *)path.c_str());
                    }
                    cout << "written normal frames" << endl;
                }
                if (strcmp(inputArgs.w[j].operation.c_str(), "invert") == 0)
                {
                    string path = "./out/" + inputArgs.w[j].name;
                    PGMImage *invertedPGM = invertPGM(pgm);
                    if (backwards)
                    {
                        reversePGM(invertedPGM, (char *)path.c_str());
                    }
                    else
                    {
                        defaultSequence(invertedPGM, (char *)path.c_str());
                    }
                    closePGM(invertedPGM);
                    cout
                        << "written inverted frames" << endl;
                }
                if (strcmp(inputArgs.w[j].operation.c_str(), "reverse") == 0)
                {
                    string path = "./out/" + inputArgs.w[j].name;
                    if (backwards)
                    {
                        defaultSequence(pgm, (char *)path.c_str());
                    }
                    else
                    {
                        reversePGM(pgm, (char *)path.c_str());
                    }
                    reversePGM(pgm, (char *)path.c_str());
                    cout
                        << "written reverse frames" << endl;
                }
                if (strcmp(inputArgs.w[j].operation.c_str(), "revinvert") == 0)
                {
                    string path = "./out/" + inputArgs.w[j].name;
                    PGMImage *invertedPGM = invertPGM(pgm);

                    if (backwards)
                    {
                        defaultSequence(invertedPGM, (char *)path.c_str());
                    }
                    else
                    {
                        reversePGM(invertedPGM, (char *)path.c_str());
                    }
                    closePGM(invertedPGM);
                    cout
                        << "written revinerted frames" << endl;
                }
            }
        }
        writePGM(pgm, "./out/testOut.pgm");
        closePGM(pgm);
    }
}
FrameSequence::FrameSequence()
{
    inputArgs.width = 0;
    inputArgs.height = 0;
    inputArgs.x1 = 0;
    inputArgs.y1 = 0;
    inputArgs.x2 = 0;
    inputArgs.y2 = 0;
    imageSequence = {};
}
FrameSequence::~FrameSequence()
{
    delete (pgm);
}
void FrameSequence::closePGM(PGMImage *pgm)
{
    // deallocate image;
    for (int i = 0; i < pgm->height; i++)
    {
        free(pgm->data[i]);
    }
    free(pgm->data);
    return;
}
bool FrameSequence::writePGM(PGMImage *pgm,
                             const char *filename)
{
    ofstream myfile(filename, ios::binary);
    myfile.write("P5\n", 3);
    myfile.write(to_string(pgm->width).c_str(), to_string(pgm->width).length());
    myfile.write(" ", 1);
    myfile.write(to_string(pgm->height).c_str(), to_string(pgm->height).length());
    myfile.write("\n255\n\n", 6);
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

    if (inputArgs.x2 + inputArgs.width > pgm->width || inputArgs.y2 + inputArgs.height > pgm->height)
    {
        fprintf(stderr,
                "end coordinates outside of scope\n");
        exit(1);
    }
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
void FrameSequence::defaultSequence(PGMImage *pgm, char *outName)
{
    int startY = inputArgs.y1;
    int endY = inputArgs.y1 + inputArgs.height;
    int startX = inputArgs.x1;
    int endX = inputArgs.x1 + inputArgs.width;
    for (int f = 0; f < inputArgs.x2 - inputArgs.x1; f++)
    {
        PGMImage *newPgm = (PGMImage *)malloc(sizeof(PGMImage));
        newPgm->height = inputArgs.height;
        newPgm->width = inputArgs.width;
        newPgm->data = (unsigned char **)malloc(newPgm->height * sizeof(unsigned char *));
        for (int y = startY; y < endY; y++)
        {
            newPgm->data[y - startY] = (unsigned char *)malloc(newPgm->width + 1 * sizeof(unsigned char));
            for (int x = startX; x < endX; x++)
            {
                newPgm->data[y - startY][x - startX] = pgm->data[y][x];
            }
        }
        string outNameTemp = (string)outName;
        stringstream ss;
        ss << setw(4) << setfill('0') << f;
        string fileNo = ss.str();
        if (outNameTemp.find('.') == std::string::npos)
        {
            outNameTemp = outNameTemp.substr(0, outNameTemp.find_last_of("."));
        }
        string outFrameName = outNameTemp + "-" + fileNo + ".pgm ";
        writePGM(newPgm, outFrameName.c_str());
        imageSequence.push_back(pgm->data);
        // for some reason first pixel on each line is wrong?

        for (int i = 0; i < inputArgs.y2 - inputArgs.y1; i++)
        {
            free(newPgm->data[i]);
        }
        free(newPgm->data);
        free(newPgm);
        startX++;
        startY++;
        endX++;
        endY++;
    }
}

PGMImage *FrameSequence::invertPGM(PGMImage *pgm)
{
    PGMImage *newPgm = (PGMImage *)malloc(sizeof(PGMImage));
    newPgm->height = pgm->height;
    newPgm->width = pgm->width;
    newPgm->data = (unsigned char **)malloc(newPgm->height * sizeof(unsigned char *));
    for (int y = 0; y < pgm->height; y++)
    {
        newPgm->data[y] = (unsigned char *)malloc(newPgm->width + 1 * sizeof(unsigned char));
        for (int x = 0; x < pgm->width; x++)
        {
            newPgm->data[y][x] = (u_char)(255 - (int)pgm->data[y][x]);
        }
    }
    return newPgm;
}
void FrameSequence::reversePGM(PGMImage *pgm, char *outName)
{
    int startY = inputArgs.y2;
    int endY = inputArgs.y2 + inputArgs.height;
    int startX = inputArgs.x2;
    int endX = inputArgs.x2 + inputArgs.width;
    for (int f = 0; f < inputArgs.x2 - inputArgs.x1; f++)
    {
        PGMImage *newPgm = (PGMImage *)malloc(sizeof(PGMImage));
        newPgm->height = inputArgs.height;
        newPgm->width = inputArgs.width;
        newPgm->data = (unsigned char **)malloc(newPgm->height * sizeof(unsigned char *));
        for (int y = startY; y < endY; y++)
        {
            newPgm->data[y - startY] = (unsigned char *)malloc(newPgm->width + 1 * sizeof(unsigned char));
            for (int x = startX; x < endX; x++)
            {
                newPgm->data[y - startY][x - startX] = pgm->data[y][x];
            }
        }
        string outNameTemp = (string)outName;
        stringstream ss;
        ss << setw(4) << setfill('0') << f;
        string fileNo = ss.str();
        if (outNameTemp.find('.') == std::string::npos)
        {
            outNameTemp = outNameTemp.substr(0, outNameTemp.find_last_of("."));
        }
        string outFrameName = outNameTemp + "-" + fileNo + ".pgm ";
        writePGM(newPgm, outFrameName.c_str());
        imageSequence.push_back(pgm->data);
        for (int i = 0; i < inputArgs.y2 - inputArgs.y1; i++)
        {
            free(newPgm->data[i]);
        }
        free(newPgm->data);
        free(newPgm);
        startX--;
        startY--;
        endX--;
        endY--;
    }
}