#include "cell.h"

using namespace std;

Cell::Cell(int x,int y, int h,int w,Xwindow *xw,bool white){
    this->x=x;
    this->y=y;
    this->h=h;
    this->w=w;
    this->xw=xw;
    currBlock = NULL;
    this->white=white;
}

int Cell::notifyRemoving() {//call it when a cell is deleted
    int level=-1;
    if (currBlock != NULL) {
        currBlock->CellCount--;
        if (currBlock->CellCount == 0) {//if a whole block is deleted, delete currBlock
            level=currBlock->getLevel();
            delete currBlock;
            currBlock = NULL;
        }
    }
    return level;
}

void Cell::print(bool text){//print cell
    if (currBlock == NULL){
        cout << " ";
        if(!text&&!getWhite()){
            xw->fillRectangle(x, y, w+1, h+1,Xwindow::White);
            setWhite();
        }
    }
    else{
        cout << currBlock->getType();
        if(!text){
            switch (currBlock->getType()) {
                case 'I':
                    xw->fillRectangle(x, y, w+1, h+1,Xwindow::Black);
                    xw->fillRectangle(x, y, w, h,Xwindow::Orange);
                    break;
                case 'J':
                    xw->fillRectangle(x, y, w+1, h+1,Xwindow::Black);
                    xw->fillRectangle(x, y, w, h,Xwindow::Blue);
                    break;
                case 'L':
                    xw->fillRectangle(x, y, w+1, h+1,Xwindow::Black);
                    xw->fillRectangle(x, y, w, h,Xwindow::Red);
                    break;
                case 'S':
                    xw->fillRectangle(x, y, w+1, h+1,Xwindow::Black);
                xw->fillRectangle(x, y, w, h,Xwindow::Magenta);
                    break;
                case 'Z':
                    xw->fillRectangle(x, y, w+1, h+1,Xwindow::Black);
                    xw->fillRectangle(x, y, w, h,Xwindow::Yellow);
                    break;
                case 'T':
                    xw->fillRectangle(x, y, w+1, h+1,Xwindow::Black);
                    xw->fillRectangle(x, y, w, h,Xwindow::Brown);
                    break;
                case 'O':
                    xw->fillRectangle(x, y, w+1, h+1,Xwindow::Black);
                    xw->fillRectangle(x, y, w, h,Xwindow::Cyan);
                    break;
                default:
                    break;
            }
            setColor();
        }
        
    }
    
}

void Cell::setWhite(){//set the cell to white
    white=true;
}
void Cell::setColor(){
    white=false;
}

bool Cell::getWhite(){
    return white;
}

