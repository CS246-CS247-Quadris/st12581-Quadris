#ifndef _BLOCKTYPE_H_
#define _BLOCKTYPE_H_
#include "block.h"

class IBlock: public Block {
public:
    IBlock(Cell ***bd, int level);
    bool rotate(char type);
};


class JBlock: public Block {
public:
    JBlock(Cell ***bd, int level);
    bool rotate(char type);
};



class LBlock: public Block {
public:
    LBlock(Cell ***bd, int level);
    bool rotate(char type);
};


class SBlock: public Block {
public:
    SBlock(Cell ***bd, int level);
    bool rotate(char type);
};



class ZBlock: public Block {
public:
    ZBlock(Cell ***bd, int level);
    bool rotate(char type);
};



class TBlock: public Block {
public:
    TBlock(Cell ***bd, int level);
    bool rotate(char type);
};


class OBlock: public Block {
public:
    OBlock(Cell ***bd, int level);
    bool rotate(char type);
};

#endif