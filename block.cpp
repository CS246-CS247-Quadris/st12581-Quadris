#include "block.h"

using namespace std;

Block::~Block(){
}

void Block::clean() {
    for (int i = 0; i < 4; i++){
        bd[y[i]][x[i]]->currBlock = NULL;
    }
}
void Block::reset() {
    for (int i = 0; i < 4; i++){
        bd[y[i]][x[i]]->currBlock = this;
    }
}

char Block::getType(){
    return type;
}

int Block::getLevel(){
    return level;
}

void Block::move(char oper) {
    clean();
    switch (oper) {
        case 'L':
            left();
            break;
        case 'R':
            right();
            break;
        case 'D':
            down();
            break;
        case 'P':
            drop();
            break;
        case 'T':
            rotate('T');
            break;
        case 'C':
            rotate('C');
            break;
        default:
            break;
    }
    reset();
}

bool Block::left() {
    for (int i = 0; i < 4; i++){
        if (x[i] == 0 || bd[y[i]][x[i]-1]->currBlock != NULL)
            return false;
    }
    for (int i = 0; i < 4; i++){
        x[i]--;
    }
    return true;
}

bool Block::right() {
    for (int i = 0; i < 4; i++){
        if (x[i] == width-1|| bd[y[i]][x[i]+1]->currBlock != NULL)
            return false;
    }
    for (int i = 0; i < 4; i++){
        x[i]++;
    }
    return true;
}

bool Block::down() {
    for (int i = 0; i < 4; i++){
        if (y[i] == 0|| bd[y[i]-1][x[i]]->currBlock != NULL)
            return false;
    }
    for (int i = 0; i < 4; i++){
        y[i]--;
    }
    return true;
}

void Block::drop() {
    while (true) {
        if (!this->down())
            break;
    }
}

