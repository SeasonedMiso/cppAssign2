#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>
#include "FrameSequence.hpp"
using namespace std;

// Constructor -> frameLoop -> createFrame

void FrameSequence::createFrame()
{
    // make frame and store in ram I guess?

    return;
}

using namespace std;

void FrameSequence::frameLoop(inputArgs inputArgs)
{
    // // ios::binary::
    // ifstream fin(inputArgs.filePath, ios::binary);
    // file.read(reinterpret_cast<char *>(data), sizeof data);
    // int row = 0, col = 0, numrows = 0, numcols = 0;
    // ifstream *pInFile = new ifstream;
    string myText;
    ifstream MyFile(inputArgs.filePath, ios::binary);
    int i;
    string version;
    string comment = "";

    int height;
    int width;
    int range;

    getline(MyFile, version);
    getline(MyFile, myText);
    while (myText.compare("#") == 1)
    {
        comment += myText;
        comment += "\n";
        getline(MyFile, myText);
    }
    stringstream widthHeight(myText);
    widthHeight >> width;
    widthHeight >> height;
    // cout << width << height;
    getline(MyFile, myText);
    stringstream rangeSS(myText);
    rangeSS >> range;
    u_char pixel = 212;
    // unsigned char pixel = ' ';
    // vector<vector<u_char>> grid;
    vector<vector<u_char>> grid;
    for (int y = 0; y < height; y++)
    {
        grid.push_back({});
        for (int x = 0; x < width; x++)
        {
            MyFile.read(reinterpret_cast<char *>(pixel), 1);
            grid[y].push_back(pixel);
        }
    }
    // for (int y = 0; y < height; y++)
    // {
    //     for (int x = 0; x < width; x++)
    //     {
    //         cout << grid[y][x];
    //     }
    // }

    // file.read(reinterpret_cast<char *>(data), sizeof data);
    // reading in the data as block
    // of unsigned char data of width * height bytes in size, and this must be read into a
    // unsigned char buffer, not int buffer;

    // vector<unsigned char> raster(width * height);
    // MyFile.read(raster.data(), width * height);

    // while (!MyFile.eof())
    // for (int i = 0; i < 10; i++)
    // {
    //     // memset(array, 0, 8);
    //     // MyFile.read(array, 8 - 1);
    //     // cout << "Next byte data chunk: "
    //     //      << array << endl;
    //     MyFile.read(array, 0);
    //     cout << "Next byte data chunk: "
    //          << array << "\n";
    // }
    MyFile.close();
}
// file.read(reinterpret_cast<char *>(data), sizeof data);

// Two common issues with reading a binary PGM :
//  (1) not opening the file in binary mode(ios::binary) and
//  (2) not consuming extra white space from the header(read using << as regular text I / O)
//  remember to add in the "ws" manipulator after reading in the "255"(max image value)to suck up
//   the last \n etc in input buffer befor ebinary block starts.If you don't, your image will have
//    (at least) a weird sheared/warped apppearance. Also, as a sanity check, after reading the
//    image, write it out again immediately to test - when you view this in Gimp or any image
//    viewer the image should look identical to the input image.

// in the past this issue was caused mainly by(1) not reading in the data as block
// of unsigned char data of width * height bytes in size, and this must be read into a
// unsigned char buffer, not int buffer;
// (2) issuing the binary read() before *all *text header i
// nformation(including the newline / white space after the 255) had been consumed.T
// he entire text header needs to be read(using getline() and << and ws, as appropriate)
// before the single read() is issued.Writing the file back out usually won't cause issued
// (as long as the text header is written with >> and then a single write() of the buffer content
// is issued.

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
        // where none : no modification of data,
        // invert : each pixel value v become 255 - v,
        // reverse : 2 reverse output(write frames out from last to first),
        // revinvert : reverse and invert out - put.
        inputArgs.w[j].name = wResultVecArray[j][1];
        // The parameter<name> = name of sequence base e.g.sequence - 0000.pgm, sequence - 0001.pgm etc
        // will be generated with<name> set to ‘sequence’.
    }
    // read_pgm_image(inputArgs.filePath);
    frameLoop(inputArgs);
}
void FrameSequence::printTest(inputArgs inArg)
{
    cout
        << "inPath: " << inArg.filePath << "\n";
    cout
        << "width: " << inArg.width << "\n";
    cout << "height: " << inArg.height << "\n";
    cout << "x1: " << inArg.x1 << "\n";
    cout << "x2: " << inArg.x2 << "\n";
    cout << "y1: " << inArg.y1 << "\n";
    cout << "y2: " << inArg.y2 << "\n";
    for (int j = 0; j < inArg.w.size(); j++)
    {
        cout << j << " name: " << inArg.w[j].name << "\n";
        cout << j << " operation: " << inArg.w[j].operation << "\n";
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

// PGM images are greyscale — meaning they have no colour, and use only one value to
// encode an intensity that ranges from (black = 0) through to (white=255). Each value is
// thus stored as an ‘unsigned char’. The images we will provide are ‘raw’ PGM i.e. binary
// files. However, they have a text header, so you usually open the file as binary (ios::binary),
// but use the >> and << operators to read/write the header information. Getline() is very
// useful for reading and discarding comment lines. The header is followed by a block of
// bytes, which represent the image intensities. You can use the read() and write() methods
// to manipulate this data. Look at the function prototypes to see what arguments they
// expect (www.cplusplus.com can help here if you have no C++ reference). The PGM
// images you will receive will have the format:
// P5

// #comment line(there can be more than 1 of these comment lines)
// #the string P5 will always be the first item in the file.
// width height
// 255
// binary_data_block

// where width and height are integers representing the number of columns and rows making
// up the image matrix. There is a newline after each line — use “ws” to process this correctly.
// After reading 255 (and using the ws manipulator) you will be at the start of the binary
// data (width*height unsigned chars) which you can read in using read(). If you write out
// a PGM image you needn’t include any comments, although it
// is good practice to indicate what application generated the image. You can open the
// output image as a binary file, write out the text header using the usual text operator <<
// and then use write() to output the binary data (in one statment!) before closing the file.
// Have a look at https://en.wikipedia.org/wiki/Netpbm for more information on the
// image format (and it’s history).

// Remember that image data(being a 2D array of unsigned char) is indexed from[0][0] and that this is the top left hand corner of the image.Generally we process image data
//                                                                                       line by line,
//     starting from the top.This is in fact how the binary image data is stored
//         in the PGM format — so you can read
//         / write the entire image with one read() / write() statement !This is very convenient.We will provide some PGM images.You can view the effects of your image operations using an image viewer like Gimp on Ubuntu.

// You always move in 1 pixels steps through the input image (unless your tackle the
// mastery work section and use an acceleration function). The frame origin is the top
// left corner of the frame. Remember that images are indexed with (0,0) being the
// top left screen corner, x increasing left to right and y increasing down the screen —
// exactly like a matrix/array (which is why we use them for images of course).

// ensure code like FrameSequence myVideoFrames;
// is valid and will compile

// — create an instance of the class on the stack.To set class
//     variables,
//     use setter methods e.g.myVideoFrames.setFrameSize(width, height);
// and so on