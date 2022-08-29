#include "ass2.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

void parseIntArgs(int argNum, int i, char *argv[])
{
    int tArray[argNum];
    bool badConversion = false;
    for (int j = 1; j < argNum + 1; j++)
    {
        if (strcmp(to_string(atoi(argv[i + j])).c_str(), argv[i + j]) == 0)
        {
            tArray[j - 1] = atoi(argv[i + j]);
            // cout << j-1 << " a\n";
        }
        else
        {
            cout << "b\n";
            badConversion = true;
        }
    }
    if (badConversion)
    {
        cout << "c\n";
        cout << "bad conversion\n";
    }
    if (!badConversion)
    {
        for (int j = 0; j < argNum ; j++)
        {
            cout << tArray[j] << "\n";
        }
        }
    }

    int main(int argc, char *argv[])
    {
        // cout << "hello: " << argv[argc-1];
        for (int i = 1; i < argc; i++)
        {
            if (strcmp(argv[i], "-t") == 0)
            {
                parseIntArgs(4, i, argv);
            }
            if (strcmp(argv[i], "-s") == 0)
            {
                cout << argv[i] << " is found\n";
                parseIntArgs(2, i, argv);
            }
            if (strcmp(argv[i], "-w") == 0)
            {
                cout << argv[i] << " is found\n";
            }
        }
    }

    // Remember to do error checking when parsing
    //     your command line

    // CLI program called buffer
    // params are

    // default constructor too:
    // sets up deconstructor (empty arg list, not void), frees up resources when obj out of scope.
    // FrameSequence::~FrameSequence();
    // raw mem allocation for each frame.
    // iterates through vec and free up allocated mem. (activated automatically)

    // output has appropriate file numbering

    // cli
    // extractor <inputPGMfile> [options]
    //-t <int> <int> <int> <int> # x1 y1 x2 y2 (begin & end origin pixel coords,
    // for frame trajectory)
    // -s <int> <int> # <width> <height> (size of small frame in
    // pixels)
    // -w <string> <string> # write frames with <operation> <name>

    // For the - w flag, the parameter<operation> = none | invert | reverse | revinvert,
    // where none : no modification of data, invert : each pixel value v become 255 - v,
    // reverse : 2 reverse output(write frames out from last to first),
    //  revinvert : reverse and invert out - put.
    // The parameter<name> = name of sequence base e.g.sequence - 0000.pgm, sequence - 0001.pgm etc
    // will be generated with<name> set to ‘sequence’.
    // NOTE : -t and -s are specified once, but you can have one or more - w operations specifed,
    // each of which outputs a different frame sequence.

    // ./extractor myLargeImage.pgm - t 0 10 5000 5000 - s 640 480 - w invert invseq - w none sequence2
    // You must format the output string for the frame file name to have enough leading 0’s
    // to ensure you can hold all your frames (up to 4 digits should be fine e.g. someting like
    // “%04d”). There are string format commands to manage this with C++ streams and
    // stringstreams.

    // provide a README file explaining what each file submitted does and
    //     how it fits into the program as a whole.The README file should not explain any
    //         theory that you have used.The README be used by the tutors if they encounter
    //             any problems
