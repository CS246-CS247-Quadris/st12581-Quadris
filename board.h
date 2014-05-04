#ifndef _BOARD_H_
#define _BOARD_H_

#include "PRNG.h"
#include "cell.h"
#include "block.h"
#include "window-v2.h"
#include <string>
#include <sstream>

using namespace std;
const int screenW=800, screenH=850;
const int blockW=40,blockH=40;


class Board{
    Cell ***theBoard;
    Block *newBlock;
    Xwindow *mywindow;
    char nextBlock;
    int score, hiScore;
    int level;
    void checkRows();
    bool text;
    
public:
    Board();
    ~Board();
    void increLevel();
    void decreLevel();
    int createBlock(char type);
    void move(char type);
    void print();
    void reset();
    void setNext(char type);
    void setText();
    void setWindow();
    void draw();
};

char generateNextBlock(int level,PRNG &randNum);
string n_to_s(int n);

#endif