#ifndef _BLOCK_H_
#define _BLOCK_H_
#include "cell.h"

const int width = 10, height = 18;

class Cell;

class Block{
protected:
    char type;
    int level;
    Cell ***bd;
    
    int x[4];
    int y[4];
    int status;
    void clean();
    void reset();
    
    bool left();
    bool right();
    bool down();
    void drop();
public:
    int CellCount;
    int getLevel();
    char getType();
    void move(char oper);
    
    virtual bool rotate(char type) = 0;
    virtual ~Block();
    
};

#endif