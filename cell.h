#ifndef _CELL_H_
#define _CELL_H_

#include <iostream>
#include "block.h"
#include "window-v2.h"

class Block;

class Cell {
    int x,y,h,w;
    Xwindow *xw;
    bool white;
public:
    Cell(int x,int y, int h,int w,Xwindow *xw,bool white=true);
    Block* currBlock;
    
    int notifyRemoving();
    void print(bool text);
    void setWhite();
    void setColor();
    bool getWhite();
};

#endif