#include <iostream>
#include <iomanip>
#include <cstdlib>
#include "board.h"
#include "block.h"
#include "blockType.h"


Board::Board(){
    score=0;
    level=0;
    hiScore=0;
    nextBlock=' ';
    text=false;
    theBoard = new Cell**[height];
    
    for (int i = 0; i < height; i++) {//set new cell
        theBoard[i] = new Cell*[width];
        for (int j = 0; j < width; j++) {
            theBoard[i][j] = new Cell(50+j*(blockW+2),screenH-(i+1)*(blockH+2)-44,blockH,blockW,mywindow);//const 
        }
    }
}

Board::~Board(){
    for(int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            theBoard[i][j]->notifyRemoving();
            delete theBoard[i][j];
        }
        delete [] theBoard[i];
    }
    delete [] theBoard;
    if(!text){
        delete mywindow;
    }
}

void Board::reset(){//reset variables, delete and reset new cell
    score=0;
    level=0;
    nextBlock=' ';
    
    for(int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            theBoard[i][j]->notifyRemoving();
            delete theBoard[i][j];
        }
    }
    
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            theBoard[i][j] = new Cell(50+j*(blockW+2),screenH-(i+1)*(blockH+2)-44,blockH,blockW,mywindow,false);
        }
    }
}

void Board::print(){//print the board
    cout<<endl<<"Level:"<<right<<setw(7)<<level<<endl;
    cout<<"Score:"<<setw(7)<<score<<endl;
    cout<<"Hi Score:"<<setw(4)<<hiScore<<endl;
    cout<<"----------"<<endl;
    
    if(!text){//UI score
        mywindow->fillRectangle(500, 50, 200, 200,Xwindow::White);
    
        //print level graphically
        string LEVEL= "Level:";
        LEVEL = LEVEL + "       " + n_to_s(level);
        mywindow->drawString(550, 100, LEVEL, Xwindow::Black);
    
        //print score graphically
        string SCORE = "Score:";
        SCORE = SCORE + "       " + n_to_s(score);
        mywindow->drawString(550, 120, SCORE, Xwindow::Black);
    
        //print Hi Score graphically
        string HISCORE = "Hi Score:";
        HISCORE = HISCORE + "    " + n_to_s(hiScore);
        mywindow->drawString(550, 140, HISCORE, Xwindow::Black);
    }
    
    
    for (int i = height-1; i >= 0; i--) {//print cell
        for (int j = 0; j < width; j++) {
            theBoard[i][j]->print(text);
        }
        cout << endl;
    }
    
    cout<<"----------"<<endl<<"Next:"<<endl;
    
    
    int OX = 600;  //orignal x-coord of next block
    int OY = 200;   //orignal y-coord of next block
    if(!text){
        mywindow->drawString(550, 200, "Next:", Xwindow::Black);
    }
    
    
    switch (nextBlock) {//print next block
        case 'I':
            cout<<"IIII"<<endl;
            if(!text){
                mywindow->fillRectangle(OX, OY, 40, 10, Xwindow::Orange);
            }
            break;
        case 'J':
            cout<<"J"<<endl<<"JJJ"<<endl;
            if(!text){
                mywindow->fillRectangle(OX, OY, 10, 10, Xwindow::Blue);
                mywindow->fillRectangle(OX, OY+10, 30, 10, Xwindow::Blue);
            }
            break;
        case 'L':
            cout<<"  L"<<endl<<"LLL"<<endl;
            if(!text){
                mywindow->fillRectangle(OX+20, OY, 10, 10, Xwindow::Red);
                mywindow->fillRectangle(OX, OY+10, 30, 10, Xwindow::Red);
            }
            break;
        case 'O':
            cout<<"OO"<<endl<<"OO"<<endl;
            if(!text){
                mywindow->fillRectangle(OX, OY, 20, 10, Xwindow::Cyan);
                mywindow->fillRectangle(OX, OY+10, 20, 10, Xwindow::Cyan);
            }
            break;
        case 'S':
            cout<<" SS"<<endl<<"SS"<<endl;
            if(!text){
                mywindow->fillRectangle(OX, OY, 20, 10, Xwindow::Magenta);
                mywindow->fillRectangle(OX-10, OY+10, 20, 10, Xwindow::Magenta);
            }
            break;
        case 'Z':
            cout<<"ZZ"<<endl<<" ZZ"<<endl;
            if(!text){
                mywindow->fillRectangle(OX, OY, 20, 10, Xwindow::Yellow);
                mywindow->fillRectangle(OX+10, OY+10, 20, 10, Xwindow::Yellow);
            }
            break;
        case 'T':
            cout<<"TTT"<<endl<<" T "<<endl;
            if(!text){
                mywindow->fillRectangle(OX, OY, 30, 10, Xwindow::Brown);
                mywindow->fillRectangle(OX+10, OY+10, 10, 10, Xwindow::Brown);
            }
            break;
        default:
            break;
    }
}

int Board::createBlock(char type) {//check game over
    if (type == 'I') {
        if (theBoard[height-4][0]->currBlock==NULL&&theBoard[height-4][1]->currBlock==NULL&&theBoard[height-4][2]->currBlock==NULL&&theBoard[height-4][3]->currBlock==NULL){
            newBlock = new IBlock(this->theBoard, level);
        }
        else{
            return 1;//restart
        }
    } 
    else if(type=='J'){
        if (theBoard[height-4][0]->currBlock==NULL&&theBoard[height-5][0]->currBlock==NULL&&theBoard[height-5][1]->currBlock==NULL&&theBoard[height-5][2]->currBlock==NULL){
            newBlock = new JBlock(this->theBoard, level);
        }
        else{
            return 1;
        }
    }
    else if(type=='L'){
        if (theBoard[height-4][2]->currBlock==NULL&&theBoard[height-5][0]->currBlock==NULL&&theBoard[height-5][1]->currBlock==NULL&&theBoard[height-5][2]->currBlock==NULL){
            newBlock = new LBlock(this->theBoard, level);
        }
        else{
            return 1;
        }
    }
    else if(type=='S'){
        if (theBoard[height-4][1]->currBlock==NULL&&theBoard[height-4][2]->currBlock==NULL&&theBoard[height-5][0]->currBlock==NULL&&theBoard[height-5][1]->currBlock==NULL){
            newBlock = new SBlock(this->theBoard, level);
        }
        else{
            return 1;
        }
    }
    else if(type=='Z'){
        if (theBoard[height-4][0]->currBlock==NULL&&theBoard[height-4][1]->currBlock==NULL&&theBoard[height-5][1]->currBlock==NULL&&theBoard[height-5][2]->currBlock==NULL){
            newBlock = new ZBlock(this->theBoard, level);
        }
        else{
            return 1;
        }
    }
    else if(type=='T'){
        if (theBoard[height-4][0]->currBlock==NULL&&theBoard[height-4][1]->currBlock==NULL&&theBoard[height-4][2]->currBlock==NULL&&theBoard[height-5][1]->currBlock==NULL){
            newBlock = new TBlock(this->theBoard, level);
        }
        else{
            return 1;
        }
    }
    else if(type=='O'){
        if (theBoard[height-4][0]->currBlock==NULL&&theBoard[height-4][1]->currBlock==NULL&&theBoard[height-5][0]->currBlock==NULL&&theBoard[height-5][1]->currBlock==NULL){
            newBlock = new OBlock(this->theBoard, level);
        }
        else{
            return 1;
        }
    }
    return 0;
}

void Board::move(char type) {
    newBlock->move(type);
    if(type=='P'){
        checkRows();
    }
}

void Board::checkRows() {
    int line=0;
    bool check=true;
    for (int i = 0; i < height; i++) {
        for(int j=0;j<width;j++){
            if(theBoard[i][j]->currBlock==NULL){
                check=false;
                break;
            }
        }
        if(check){
            for(int m=i;m<height;m++){
                for(int j=0;j<width;j++){
                    if(m==i){
                        int blockLevel=theBoard[m][j]->notifyRemoving();
                        if(blockLevel!=-1){
                            score+=(blockLevel+1)*(blockLevel+1);
                        }
                    }
                    if(m==height-1 || theBoard[m+1][j]->currBlock==NULL){
                        theBoard[m][j]->currBlock=NULL;
                    }
                    else{
                        theBoard[m][j]->currBlock=theBoard[m+1][j]->currBlock;
                    }
                }
            }
            line++;
            i--;
        }
        check=true;
    }
    if(line>0){
        this->score+=(line+level)*(line+level); 
    }
    
    if(hiScore<score){
        hiScore=score;
    }
    
}

void Board::increLevel(){
    level++;
}

void Board::decreLevel(){
    level--;
}

void Board::setNext(char type){
    nextBlock=type;
}

char generateNextBlock(int level,PRNG &randNum){
    if(level==1){
        int num=randNum.operator()(11);
        switch (num) {
            case 0:
                return 'S';
            case 1:
                return 'Z';
            case 2: case 3:
                return 'I';
            case 4: case 5:
                return 'J';
            case 6: case 7:
                return 'L';
            case 8: case 9:
                return 'O';
            case 10: case 11:
                return 'T';
            default:
                break;
        }
    }
    else if(level==2){
        int num=randNum.operator()(6);
        switch (num) {
            case 0:
                return 'S';
            case 1:
                return 'Z';
            case 2:
                return 'I';
            case 3:
                return 'J';
            case 4:
                return 'L';
            case 5:
                return 'O';
            case 6:
                return 'T';
            default:
                break;
        }
    }
    else{
        int num=randNum.operator()(8);
        switch (num) {
            case 0: case 1:
                return 'S';
            case 2: case 3:
                return 'Z';
            case 4:
                return 'I';
            case 5:
                return 'J';
            case 6:
                return 'L';
            case 7:
                return 'O';
            case 8:
                return 'T';
            default:
                break;
        }
    }
    return 'N';
}

void Board::setText(){
    text=true;
}

void Board::setWindow(){
    mywindow = new Xwindow(screenW,screenH);
}

void Board::draw(){
    mywindow->fillRectangle(48, 48, 424, 760,Xwindow::Black);//change to variables
    mywindow->fillRectangle(50, 50, 420, 756,Xwindow::White);
}

string n_to_s(int n) { 
    string s2;
    stringstream ss;
    ss<<n;
    s2 = ss.str();
    return s2;
} 
